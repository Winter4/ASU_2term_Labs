#include "stdafx.h"
#include "stdlib.h"
#include "stdio.h"
#include <iostream>
#include <windows.h>
#include <conio.h>

HDC hDC; // ���������� �������
HWND hWnd; // ���������� ����
RECT Rect; // RECT - ���������, �������� ���������� �������������� (������)

void task()
{
	int xc1 = 700, xc2 = 850, yc1 = 150, yc2 = 300, dcx = -7, xt1 = 200, xt2 = 400, yt1 = 600, y, dtx = 8;
	int rc = 200, gc = 100, bc = 0, rt = 0, gt = 50, bt = 100, drgb = 50; 

	// ���������� = ���� + ������;
	// ���� - ����������, ��� �����; ������: c - circle - ����; t - triangle - ����������.

	// x, y - ����������; dx - ���������� (���������) ����;
	// r, g, b - ���� RGB; drgb - ��������� �����.

	while (true)
	{
		HBRUSH cBrush = CreateSolidBrush(RGB(255, 255, 255)); // ������� �����
		SelectObject(hDC, cBrush); // ������� �����

		Rectangle(hDC, 0, 0, 1400, 800); // �������� �����

		if (xc1 <= 0 || xc2 >= 1400) { // �������� ������ �������� �����
			dcx *= (-1);

			rc += drgb; // ��������� ����� ����� ��� ������� �������
			rc %= 255;

			gc += drgb;
			gc %= 255;

			bc += drgb;
			bc %= 255;
		}

		xc1 += dcx; // �������� �����
		xc2 += dcx;

		HBRUSH hBrush = CreateSolidBrush(RGB(rc, gc, bc)); // ������� �������
		SelectObject(hDC, hBrush);

		Ellipse(hDC, xc1, yc1, xc2, yc2); // ���������� ����



		if (xt1 <= 0 || xt2 >= 1400) { // �������� ������ �������� ������������
			dtx *= (-1);

			rt += drgb; // ��������� ����� ������������ ��� �������
			rt %= 255;

			gt += drgb;
			gt %= 255;

			bt += drgb;
			bt %= 255;
		}

		y = 0;    // ��������� ���������� ��� ������� ������������
		xt1 += dtx; // �������� ������������
		xt2 += dtx;


		HPEN tPen = CreatePen(PS_SOLID, 1, RGB(rt, gt, bt)); // ������� �������
		SelectObject(hDC, tPen);

		while ((xt2 - xt1) / 2 - y >= 0) {       // ���������� �����������
			MoveToEx(hDC, xt1 + y, yt1 + y, NULL);
			LineTo(hDC, xt2 - y, yt1 + y);
			y++;
		}

		Sleep(30); // ��������� ��������, 30 - 30 ����������, ���� ������������ ����� ������ :D
	}
}

int main()
{
	hWnd = GetConsoleWindow();
	if (!hWnd) {
		printf("�� ������� �������� hWnd �������!");
		getch();
		return -1;
	}

	hDC = GetDC(hWnd);
	if (!hDC) {
		printf("�� ������� �������� �������� ����������!");
		getch();
		return -2;
	}

	GetClientRect(hWnd, &Rect);
	MoveWindow(hWnd, 0, 0, 1150, 650, true);

	task();

	ReleaseDC(hWnd, hDC);
}