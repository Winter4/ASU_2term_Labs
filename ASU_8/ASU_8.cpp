#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "locale.h"
#include <math.h>

void scale_n_axis(int dotX[15], int dotY[15], int recX[4], int recY[4], int dn, int rn, float* mx, float* my) // находим масштаб и рисуем оси
{
    int x_max = 0, y_max = 0;

    for (int i = 0; i < dn; i++) { // суть нахождения масштаба в том, чтобы 
        if (x_max < abs(dotX[i])) // найти максимально удалённую от начала с. координат точку (её модуль по сути)
            x_max = dotX[i];

        if (y_max < abs(dotY[i]))
            y_max = dotY[i]; // в этом форе ищем таковую среди точек которые точки
    }                           

    for (int i = 0; i < rn; i++) { // а в этом среди точек-вершин прямоугольника
        if (x_max < abs(recX[i]))
            x_max = recX[i];

        if (y_max < abs(recY[i]))
            y_max = recY[i];
    } // нашли самый большой модуль

    *my = 480 / (2 * y_max); // и поделить рабочее пространство на удовенное значение масштаба
    *mx = 640 / (2 * x_max); // почему именно так - хз, но это так работает)

    HWND hwnd = GetConsoleWindow(); // тут начинаем рисовать оси
    HDC hdc = GetDC(GetConsoleWindow());

    HPEN Pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255)); // сделали белую ручку
    SelectObject(hdc, Pen);

    MoveToEx(hdc, 320, 0, NULL); // рисуем от сверху вниз Oy
    LineTo(hdc, 320, 480);

    MoveToEx(hdc, 0, 240, NULL); // рисуем слева направо Ox
    LineTo(hdc, 640, 240);
}

void draw(int recX[4], int recY[4], int dotX[15], int dotY[15], int n, float mx, float my) // рисуем точки и прямоугольник
{
    for (int i = 0; i < 4; i++) { // это сортировка (пузырёек вроде)
        for (int j = 0; j < 3; j++) { // в общем смысле решения задачи она не нужна

            if (recX[j] > dotX[j + 1]) { // но у Лёни алгоритм определиния точка внутри\снаружи прямоугольника завязана на этом
                float tmp = recX[j]; // а я не стал переделывать
                recX[j] = recX[j + 1]; // хотя, повторюсь, можно сделать без сортировки, 
                recX[j + 1] = tmp; // и это будет даже логичнее, но это немного дольше и объемнее
            }

            if (recY[j] > recY[j + 1]) {
                float tmp = recY[j];
                recY[j] = recY[j + 1];
                recY[j + 1] = tmp;
            }
        }
    }  // конец сортировки

    HWND hwnd = GetConsoleWindow();
    HDC hdc = GetDC(GetConsoleWindow());

    HPEN Pen1 = CreatePen(PS_SOLID, 1, RGB(255, 0, 0)); // ручечка для точек снаружи
    HPEN Pen2 = CreatePen(PS_SOLID, 1, RGB(0, 255, 0)); // для точек внутри
    HPEN Pen3 = CreatePen(PS_SOLID, 1, RGB(0, 255, 255)); // бирюзовая для пярмоугольника
    HBRUSH br1 = CreateSolidBrush(RGB(255, 0, 0)); // для тчк снаружи
    HBRUSH br2 = CreateSolidBrush(RGB(0, 255, 0)); // для тчк внутри

    SelectObject(hdc, Pen3); // рисуем прямоугольник
    MoveToEx(hdc, recX[0] * mx + 320, recY[0] * my + 240, NULL); // это выглядит так ебано, потому что
    LineTo(hdc, recX[3] * mx + 320, recY[0] * my + 240); // вершины прямоугольника тоже отсортировались
    LineTo(hdc, recX[3] * mx + 320, recY[3] * my + 240);
    LineTo(hdc, recX[0] * mx + 320, recY[3] * my + 240);
    LineTo(hdc, recX[0] * mx + 320, recY[0] * my + 240); 

    for (int i = 0; i < n; i++) { // если условие для нахождения точки внутри выполняется, то рисуется зеленым
        if (dotX[i] > recX[0] && dotX[i] < recX[3] && dotY[i] > recY[0] && dotY[i] < recY[3]) {
            SelectObject(hdc, Pen2);
            SelectObject(hdc, br2);

            Ellipse(hdc, dotX[i] * mx + 320 - 2, dotY[i] * my + 240 - 2, dotX[i] * mx + 320 + 2, dotY[i] * my + 240 + 2);
        }
        else { // а если нет, то красным
            SelectObject(hdc, Pen1);
            SelectObject(hdc, br1);
            Ellipse(hdc, dotX[i] * mx + 320 - 2, dotY[i] * my + 240 - 2, dotX[i] * mx + 320 + 2, dotY[i] * my + 240 + 2);
        }
    }
}

void main()
{
    setlocale(LC_ALL, "russian");

    const int rn = 4, dn = 15; // r - rectangle, d - dots
    int recX[4] = { 10, 10, 20, 20 }, recY[4] = { 10, 15, 15, 10 };
    int dotX[15] = { 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22 }; // шоб меньше ебли было,
    int dotY[15] = { 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21 }; // инициализируем это всё

    printf("Вершины прямоугольника: \n"); // выводим
    for (int i = 0; i < 4; i++)
        printf(" %d  (%d, %d)\n", i + 1, recX[i], recY[i]);

    printf("\nТочки: \n");
    for (int i = 0; i < 15; i++)
        printf(" %d (%d, %d)\n", i + 1, dotX[i], dotY[i]);

    system("pause");
    system("cls");

    float mx, my;

    scale_n_axis(dotX, dotY, recX, recY, dn, rn, &mx, &my); // бахаем-с
    draw(recX, recY, dotX, dotY, dn, mx, my);

    _getch();
}
