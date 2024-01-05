#pragma once
#include "Definitions.h"


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//HANDLE DrawThread;
//bool volatile FlagDrawThread = 1;

//HDC I_Player;
//HDC I_Player_dead;

HDC I_Void;
HDC I_Barrier;
HDC I_Wall;
HDC I_Fire;

HDC I_Effect;
//HDC I_Effect_slow_bomb;
//HDC I_Effect_fast_bomb;
//HDC I_Effect_slow;
//HDC I_Effect_fast;
//HDC I_Effect_inversion;
//HDC I_Effect_automatic_bomb;
HDC I_Effect_shild;

HDC I_Improve;
HDC I_Improve_speed;
HDC I_Improve_max_bomb;
HDC I_Improve_radius_bomb;

HDC I_Bomb;

//HBRUSH C_Void;
//HBRUSH C_Barrier;
//HBRUSH C_Wall;
//HBRUSH C_Fire;
//HBRUSH C_Effect;
//HBRUSH C_Bomb;

HWND ButtonPlay;
HWND StaticDrawTimer;
HWND StaticDrawScorePlayer1;
HWND StaticDrawScorePlayer2;

HDC hdcMem;
HBITMAP hbmMem;
HANDLE hOld;

bool flag_play = 0;
Cell** map;
int NowTime;

const int shot_in_sec = 1000 / TimerDraw;

Player* player1 = nullptr;
Player* player2 = nullptr;

std::multiset<std::pair<int, Bomb*>> ActiveBomb;





