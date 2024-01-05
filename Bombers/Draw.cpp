#pragma once
#include "Definitions.h"

void play(HDC hdc);
void menu(HDC hdc);

//DWORD WINAPI Draw(LPVOID lpparametr, HWND hWnd) {
void Draw(HWND hWnd){
	HDC hdc;        //создаЄм контекст устройства
	PAINTSTRUCT ps; //создаЄм экземпл€р структуры графического вывода

	//if (flag_play == 0){
	//InvalidateRect(hWnd, NULL, false);
	//}

	hdc = BeginPaint(hWnd, &ps);

	if (flag_play) { // игра
		play(hdc);
		//InvalidateRect(hWnd, NULL, false);
	}
	else {           // меню
		menu(hdc);
		//SelectObject(hdc, CreateSolidBrush(RGB(255, 0, 0)));
		//Rectangle(hdc, 100, 100, 200, 200);
	}

	EndPaint(hWnd, &ps);
	//	InvalidateRect(hWnd, NULL, false);


	//ExitThread(0);
	//return 0;
}


void play(HDC hdc) {

	for (int i = 1; i < size_map_x; i++)
	{
		for (int j = 1; j < size_map_y; j++)
		{
			(*(map[i][j].get_keep())).Draw(hdcMem, {(i - 1) * size_cell, (j - 1) * size_cell});
		}
	}

	(*player1).Draw(hdcMem);
	(*player2).Draw(hdcMem);

	BitBlt(hdc, map_cord_x, map_cord_y, size_cell * (size_map_x - 1), size_cell * (size_map_y - 1), hdcMem, 0, 0, SRCCOPY);
}


void menu(HDC hdc){
	// на будущее
}

