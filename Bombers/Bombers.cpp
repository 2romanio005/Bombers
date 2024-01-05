#pragma once
#include "Definitions.h"




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wcex = { 0 };

	//wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	HBRUSH Background = CreateSolidBrush(RGB(170, 0, 196));
	wcex.hbrBackground = Background;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hInstance = hInstance;
	//hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.lpszClassName = L"Bombers";
	wcex.lpfnWndProc = WndProc;
	//wcex.cbSize = sizeof(WNDCLASSEX);
	//wcex.style = CS_HREDRAW | CS_VREDRAW;
	//wcex.cbClsExtra = 0;
	//wcex.cbWndExtra = 0;
	//wcex.lpszMenuName = NULL;
	//wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassW(&wcex))	{ return -1; }

	CreateWindow(L"Bombers", L"Bombers", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), NULL, NULL, NULL, NULL);
	
	

	// Main message loop:
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	DeleteObject(Background);
	return 0;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)  // обработка событий
{
	switch (message)
	{
	case WM_COMMAND:
		switch (wParam) {
		case IndexButtonClick:
			StartPlay();
			break;
		}

	case WM_TIMER:
		switch (wParam) {
		case IndexTimerDraw:
			if (flag_play) {
				CheckFin();
				UpdatePlayInfo(hWnd);
				OneStep();
				if (flag_play) {
					RECT update{ map_cord_x, map_cord_y, map_cord_x + size_cell * (size_map_x - 1),  map_cord_y + size_cell * (size_map_y - 1) };
					InvalidateRect(hWnd, &update, false);
				}
			}
			break;
		}
		break;

	case WM_PAINT:
		Draw(hWnd);
		break;
		
	//case WM_CHAR:    // символы
	//	switch (wParam) {
	//	case 'w':
	//	case 'W':
	//	case 1094:
	//	case 1062:
	//		(*player2).MuveCommand('U');
	//		break;
	//	case 's':
	//	case 'S':
	//	case 1099:
	//	case 1067:
	//		(*player2).MuveCommand('D');
	//		break;
	//	case 'a':
	//	case 'A':
	//	case 1092:
	//	case 1060:
	//		(*player2).MuveCommand('L');
	//		break;
	//	case 'd':
	//	case 'D':
	//	case 1074:
	//	case 1042:
	//		(*player2).MuveCommand('R');
	//		break;
	//	case ' ':
	//		(*player2).set_bomb();
	//		break;

	case WM_KEYDOWN:    //http://www.cyberguru.ru/programming/win32/win32-keyboard.html?showall=
	{
		switch (wParam) {
		case VK_UP:
			(*player1).MuveCommand('U');
			break;
		case VK_DOWN:
			(*player1).MuveCommand('D');
			break;
		case VK_LEFT:
			(*player1).MuveCommand('L');
			break;
		case VK_RIGHT:
			(*player1).MuveCommand('R');
			break;
		case 13:      // enter
			(*player1).set_bomb();
			break;
		case 220:     // '\'
			(*player1).clear_stack();
			break;
		case 'W':
			(*player2).MuveCommand('U');
			break;
		case 'S':
			(*player2).MuveCommand('D');
			break;
		case 'A':
			(*player2).MuveCommand('L');
			break;
		case 'D':
			(*player2).MuveCommand('R');
			break;
		case ' ':
			(*player2).set_bomb();
			break;
		case 'C':
			(*player2).clear_stack();
			break;
		}

		break;
	}

	case WM_CREATE:
		BuildWidget(hWnd);
		BuildGameObject();
		BuildDrawEffecter(hWnd);

		SetTimer(hWnd, IndexTimerDraw, TimerDraw, NULL);
		break;
	case WM_DESTROY:
		Exit(hWnd);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}





void StartPlay() {
	ShowWindow(ButtonPlay, SW_HIDE);
	ShowWindow(StaticDrawTimer, SW_SHOW);
	ShowWindow(StaticDrawScorePlayer1, SW_SHOW);
	ShowWindow(StaticDrawScorePlayer2, SW_SHOW);
	flag_play = !flag_play;

	ActiveBomb.clear();

	for (int i = 1; i < size_map_x; i++)
	{
		for (int j = 1; j < size_map_y; j++)
		{
			if (rand() % 100 < chance_barrier){
				map[i][j].set(new Barrier(), 'R');
			}
			else {
				map[i][j].set(new Void(), 'V');
			}
		}
	}

	for (int i = 2; i < size_map_x; i += 2)
	{
		for (int j = 2; j < size_map_y; j += 2)
		{
			map[i][j].set(new Wall(), 'W');
		}
	}


	int x, y;
	auto free_start = [&x, &y]() {
		map[x][y].set(new Void, 'V');

		bool UD = rand() % 2;
		bool LR = rand() % 2;
		
		if (map[x][y - 1].get_type() == 'V' && map[x][y + 1].get_type() != 'V') { UD = 1; }
		if (map[x][y + 1].get_type() == 'V' && map[x][y - 1].get_type() != 'V') { UD = 0; }

		if (map[x - 1][y].get_type() == 'V' && map[x + 1][y].get_type() != 'V') { LR = 1; }
		if (map[x + 1][y].get_type() == 'V' && map[x - 1][y].get_type() != 'V') { LR = 0; }
		
		int CUD = 0, CLR = 0;
		while(map[x][y + (UD ? -1 : 1)].get_type() == 'W' && CUD != 2)
		{
			UD = !UD;
			CUD++;
		}
		while (map[x + (LR ? -1 : 1)][y].get_type() == 'W' && CLR != 2)
		{
			LR = !LR;
			CLR++;
		}

		if (CUD == 2) {
			x += LR ? -1 : 1;
			map[x][y].set(new Void, 'V');
			y += UD ? -1 : 1;;
			if (map[x][y].get_type() == 'W') {
				y -= UD ? -2 : 2;
			}
			map[x][y].set(new Void, 'V');
		}
		else if (CLR == 2){
			y += UD ? -1 : 1;
			map[x][y].set(new Void, 'V');
			x += LR ? -1 : 1;
			if (map[x][y].get_type() == 'W') {
				x -= LR ? -2 : 2;
			}
			map[x][y].set(new Void, 'V');
		}
		else {
			map[x + (LR ? -1 : 1)][y].set(new Void, 'V');
			map[x][y + (UD ? -1 : 1)].set(new Void, 'V');
		}
	};

	x = 2; y = 2;
	while (map[x][y].get_type() == 'W') {
		x = (rand() % 5 + 7);
		y = (rand() % 7 + 1);
	}
	(*player1).Reset({ 100 * x - 50, 100 * y - 50}, start_speed, start_max_bomb, start_radius_bomb, start_time_bomb);
	free_start();

	x = 2; y = 2;
	while (map[x][y].get_type() == 'W') {
		x = (rand() % 5 + 1);
		y = (rand() % 7 + 1);
	}
	(*player2).Reset({ 100 * x - 50, 100 * y - 50}, start_speed, start_max_bomb, start_radius_bomb, start_time_bomb);
	free_start();

	NowTime = 0;
}

void OneStep() {
	NowTime++;

	while (ActiveBomb.size() != 0 && (*(ActiveBomb.begin())).first <= NowTime) {
		(*((*(ActiveBomb.begin())).second)).Detonation();
	}

	(*player1).Muve();
	(*player2).Muve();


	if (NowTime / shot_in_sec == TimePlay) {
		for (int i = 1; i < size_map_x; i++)
		{
			for (int j = 1; j < size_map_y; j++)
			{
				char type = map[i][j].get_type();
				if (type == 'V' || type == 'I' || type == 'E' || type == 'B') {
					map[i][j].set(new Fire(NowTime + time_Fire), 'F');
				}
			}
		}
	}
}

void UpdatePlayInfo(HWND hWnd)
{
	if (NowTime % shot_in_sec == 0) {
		int s = TimePlay - NowTime / shot_in_sec;
		int m = s / 60;
		s %= 60;
		SetWindowTextA(StaticDrawTimer, LPCSTR((std::to_string(m) + std::string(s < 10 ? ":0" : ":") + std::to_string(s)).c_str()));
	}
}

void CheckFin() {
	int life = (*player1).get_life() + (*player2).get_life();   // можно записывать в разныебиты

	if (life <= 1) {
		FinPlay();
	}
}

void FinPlay() {
	flag_play = 0;
	ShowWindow(ButtonPlay, SW_SHOW);

	void (*increase_score)(const HWND & widget) = [](const HWND& widget) {
		char count[3];
		GetWindowTextA(widget, count, 3);
		SetWindowTextA(widget, std::to_string(atoi(count) + 1).c_str());
	};

	if ((*player1).get_life()) {
		increase_score(StaticDrawScorePlayer1);
	}
	if ((*player2).get_life()) {
		increase_score(StaticDrawScorePlayer2);
	}



//	ShowWindow(StaticDrawTimer, SW_HIDE);

	//int life = (*player1).get_life() + (*player2).get_life();   // можно записывать в разныебиты

}





void BuildWidget(HWND hWnd) {
	ButtonPlay = CreateWindowA("BUTTON", "Play", WS_VISIBLE | WS_CHILD | ES_CENTER, GetSystemMetrics(SM_CXSCREEN) / 2 - 100, GetSystemMetrics(SM_CYSCREEN) / 2 - 50, 200, 100, hWnd, HMENU(IndexButtonClick), NULL, NULL);
	StaticDrawTimer = CreateWindowA("STATIC", "0:00", WS_CHILD | ES_CENTER, GetSystemMetrics(SM_CXSCREEN) / 2 - 25, map_cord_y - 20, 50, 16, hWnd, NULL, NULL, NULL);
	
	StaticDrawScorePlayer1 = CreateWindowA("STATIC", "0", WS_CHILD | ES_CENTER, map_cord_x + (size_map_x - 1) * size_cell, map_cord_y - 16, 48, 16, hWnd, NULL, NULL, NULL);
	StaticDrawScorePlayer2 = CreateWindowA("STATIC", "0", WS_CHILD | ES_CENTER, map_cord_x  - 48, map_cord_y - 16, 48, 16, hWnd, NULL, NULL, NULL);

}

void BuildGameObject() {
	srand(time(0));

	map = new Cell * [size_map_x + 1];
	for (int i = 0; i < size_map_x + 1; i++)
	{
		map[i] = new Cell[size_map_y + 1];
	}
	for (int i = 1; i < size_map_x; i++)
	{
		map[i][0].set(new Wall, 'W');
		map[i][size_map_y].set(new Wall, 'W');
	}
	for (int i = 0; i < size_map_y + 1; i++)
	{
		map[0][i].set(new Wall, 'W');
		map[size_map_x][i].set(new Wall, 'W');
	}


	//C_Void = CreateSolidBrush(RGB(0, 255, 0));
	//C_Barrier = CreateSolidBrush(RGB(255, 106, 0));
	//C_Wall = CreateSolidBrush(RGB(127, 127, 127));       // 130, 114, 103
	//C_Fire = CreateSolidBrush(RGB(255, 0, 0));
	//C_Effect = CreateSolidBrush(RGB(221, 0, 255));
	//C_Bomb = CreateSolidBrush(RGB(0, 0, 0));

	player1 = new Player(CreateSolidBrush(RGB(255, 255, 0)));  // стрелочки
	player2 = new Player(CreateSolidBrush(RGB(0, 255, 161)));  // wasd

//	(*player1).set_cord({100 * (rand() % 5 + 6) - 50, 100 * (rand() % 3 + 4) - 50});

}

void BuildDrawEffecter(HWND hWnd) {
	HDC hdc;        //создаЄм контекст устройства
	PAINTSTRUCT ps; //создаЄм экземпл€р структуры графического вывода

	hdc = BeginPaint(hWnd, &ps);
	hdcMem = CreateCompatibleDC(hdc);
	//hbmMem = CreateCompatibleBitmap(hdc, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	hbmMem = CreateCompatibleBitmap(hdc, size_cell * size_map_x, size_cell * size_map_y);
	hOld = SelectObject(hdcMem, hbmMem);


	void (*ReadI)(HDC & I_, std::string way) = [](HDC& I_, std::string way) {
		I_ = CreateCompatibleDC(hdcMem);
		HANDLE tmp = LoadImageA(NULL, way.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		SelectObject(I_, tmp);
		DeleteObject(tmp);
	};

	//ReadI(I_Player, "images\\I_Player.bmp");
	//ReadI(I_Player_dead,  "images\\I_Player_dead.bmp");

	ReadI(I_Void, "images\\I_Void.bmp");
	ReadI(I_Barrier, "images\\I_Barrier.bmp");
	ReadI(I_Wall, "images\\I_Wall.bmp");
	ReadI(I_Fire, "images\\I_Fire.bmp");

	ReadI(I_Effect, "images\\I_Effect.bmp");
	//ReadI(I_Effect_slow_bomb,  "images\\I_Effect_slow_bomb.bmp");
	//ReadI(I_Effect_fast_bomb,  "images\\I_Effect_fast_bomb.bmp");
	//ReadI(I_Effect_slow,  "images\\I_Effect_slow.bmp");
	//ReadI(I_Effect_fast,  "images\\I_Effect_fast.bmp");
	//ReadI(I_Effect_inversion,  "images\\I_Effect_inversion.bmp");
	//ReadI(I_Effect_automatic_bomb,  "images\\I_Effect_automatic_bomb.bmp");
	ReadI(I_Effect_shild, "images\\I_Effect_shild.bmp");

	ReadI(I_Improve, "images\\I_Improve.bmp");
	ReadI(I_Improve_speed, "images\\I_Improve_speed.bmp");
	ReadI(I_Improve_max_bomb, "images\\I_Improve_max_bomb.bmp");
	ReadI(I_Improve_radius_bomb, "images\\I_Improve_radius_bomb.bmp");

	ReadI(I_Bomb, "images\\I_Bomb.bmp");


	EndPaint(hWnd, &ps);
}

void Exit(HWND hWnd) {
	KillTimer(hWnd, IndexTimerDraw);

	SelectObject(hdcMem, GetStockObject(NULL_BRUSH));
	delete player1;
	delete player2;

	SelectObject(hdcMem, hOld);
	DeleteObject(hbmMem);
	DeleteDC(hdcMem);


	//DeleteDC(I_Player);
	//DeleteDC(I_Player_dead);

	DeleteDC(I_Void);
	DeleteDC(I_Barrier);
	DeleteDC(I_Wall);
	DeleteDC(I_Fire);

	DeleteDC(I_Effect);
	//DeleteDC(I_Effect_slow_bomb);
	//DeleteDC(I_Effect_fast_bomb);
	//DeleteDC(I_Effect_slow);
	//DeleteDC(I_Effect_fast);
	//DeleteDC(I_Effect_inversion);
	//DeleteDC(I_Effect_automatic_bomb);
	DeleteDC(I_Effect_shild);

	DeleteDC(I_Improve);
	DeleteDC(I_Improve_speed);
	DeleteDC(I_Improve_max_bomb);
	DeleteDC(I_Improve_radius_bomb);

	DeleteDC(I_Bomb);


	ActiveBomb.clear();
	for (int i = 0; i < size_map_x + 1; i++)
	{
		delete[] map[i];
	}
	delete[] map;

	PostQuitMessage(0);
}






















