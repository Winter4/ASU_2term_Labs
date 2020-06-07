#include "stdafx.h"
#include "stdlib.h"
#include "stdio.h"
#include <iostream>
#include <windows.h>
#include <conio.h>

HDC hDC; // дескриптор дисплей
HWND hWnd; // дескриптор окна
RECT Rect; // RECT - структура, хран€ща€ координата пр€моугольника (любого)

void task()
{
	int xc1 = 700, xc2 = 850, yc1 = 150, yc2 = 300, dcx = -7, xt1 = 200, xt2 = 400, yt1 = 600, y, dtx = 8;
	int rc = 200, gc = 100, bc = 0, rt = 0, gt = 50, bt = 100, drgb = 50; 

	// переменна€ = роль + фигура;
	// роль - координата, код цвета; фигура: c - circle - круг; t - triangle - окружность.

	// x, y - координаты; dx - приращение (изменение) икса;
	// r, g, b - цвет RGB; drgb - изменение цвета.

	while (true)
	{
		HBRUSH cBrush = CreateSolidBrush(RGB(255, 255, 255)); // создали кисть
		SelectObject(hDC, cBrush); // выбрали кисть

		Rectangle(hDC, 0, 0, 1400, 800); // очистили экран

		if (xc1 <= 0 || xc2 >= 1400) { // проверка границ плавани€ круга
			dcx *= (-1);

			rc += drgb; // изменение цвета круга при касании границы
			rc %= 255;

			gc += drgb;
			gc %= 255;

			bc += drgb;
			bc %= 255;
		}

		xc1 += dcx; // движение круга
		xc2 += dcx;

		HBRUSH hBrush = CreateSolidBrush(RGB(rc, gc, bc)); // создали выбрали
		SelectObject(hDC, hBrush);

		Ellipse(hDC, xc1, yc1, xc2, yc2); // нарисовали круг



		if (xt1 <= 0 || xt2 >= 1400) { // проверка границ плавани€ треугольника
			dtx *= (-1);

			rt += drgb; // изменение цвета треугольника при касании
			rt %= 255;

			gt += drgb;
			gt %= 255;

			bt += drgb;
			bt %= 255;
		}

		y = 0;    // служебна€ координата дл€ рисовки треугольника
		xt1 += dtx; // движение треугольника
		xt2 += dtx;


		HPEN tPen = CreatePen(PS_SOLID, 1, RGB(rt, gt, bt)); // создали выбрали
		SelectObject(hDC, tPen);

		while ((xt2 - xt1) / 2 - y >= 0) {       // нарисовали треугольник
			MoveToEx(hDC, xt1 + y, yt1 + y, NULL);
			LineTo(hDC, xt2 - y, yt1 + y);
			y++;
		}

		Sleep(30); // служебна€ задержка, 30 - 30 милисекунд, если закомментить будет весело :D
	}
}

int main()
{
	hWnd = GetConsoleWindow();
	if (!hWnd) {
		printf("Ќе удалось получить hWnd консоли!");
		getch();
		return -1;
	}

	hDC = GetDC(hWnd);
	if (!hDC) {
		printf("Ќе удалось получить контекст устройства!");
		getch();
		return -2;
	}

	GetClientRect(hWnd, &Rect);
	MoveWindow(hWnd, 0, 0, 1150, 650, true);

	task();

	ReleaseDC(hWnd, hDC);
}