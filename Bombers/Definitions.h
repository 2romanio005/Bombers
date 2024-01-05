#pragma once
//#include <iostream>

#include <windows.h>
#include <stdlib.h>
#include <string>
#include <tchar.h>

#include <algorithm>
#include <ctime>
#include <deque>
#include <stack>
#include <set>

#include "resource.h"



#define IndexButtonClick 1
#define IndexTimerDraw 2
#define TimerDraw 25

#define TimePlay 90 //sec  

#define map_cord_x 250
#define map_cord_y 60
#define size_map_x 12  // - 1
#define size_map_y 8   // - 1
#define size_cell 100

#define chance_barrier 60 // %
#define chance_effect  25 // %
#define chence_improve 55 // %

#define start_max_bomb 1

#define start_radius_bomb 2

#define min_speed 4.0
#define start_speed 7.0
#define max_speed 15.0
#define improve_step_speed 1.0

#define min_time_bomb 70       // * TimerDraw милисек
#define start_time_bomb 120
#define max_time_bomb 240

#define time_Fire 20

#define time_Effect 300


#define size_bmp_image 16


class Cell;


class Player;

class Item;
class Void;
class barrier;
class wall;
class Fire;

class Effect;
//class Effect_slow_bomb;
//class Effect_fast_bomb;
//class Effect_Slow;
//class Effect_fast;
//class Effect_inversion;
//class Effect_avtomatic_bombs;
//class Effect_shild;

class Improve;
//class Improve_speed;
//class Improve_max_bomb;
//class Improve_radius_bomb;

class Bomb;


//extern HDC I_Player;
//extern HDC I_Player_dead;

extern HDC I_Void;
extern HDC I_Barrier;
extern HDC I_Wall;
extern HDC I_Fire;

extern HDC I_Effect;
//extern HDC I_Effect_slow_bomb;
//extern HDC I_Effect_fast_bomb;
//extern HDC I_Effect_slow;
//extern HDC I_Effect_fast;
//extern HDC I_Effect_inversion;
//extern HDC I_Effect_automatic_bomb;
extern HDC I_Effect_shild;

extern HDC I_Improve;
extern HDC I_Improve_speed;
extern HDC I_Improve_max_bomb;
extern HDC I_Improve_radius_bomb;

extern HDC I_Bomb;


extern LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//DWORD WINAPI Draw(LPVOID lpparametr);
void StartPlay();
void OneStep();
void UpdatePlayInfo(HWND hWnd);
//void MuveCommand(Player* my, char type_command);
void CheckFin();
void FinPlay();
void Draw(HWND hWnd);

void BuildGameObject();
void BuildWidget(HWND hWnd);
void BuildDrawEffecter(HWND hWnd);
void Exit(HWND hWnd);


extern HWND ButtonPlay;
extern HWND StaticDrawTimer;
extern HWND StaticDrawScorePlayer1;
extern HWND StaticDrawScorePlayer2;

extern HDC hdcMem;
extern HBITMAP hbmMem;
extern HANDLE hOld;

//extern HANDLE DrawThread;
//extern volatile bool FlagDrawThread;

//extern HDC Test;



//extern HBRUSH C_Void;
//extern HBRUSH C_Barrier;
//extern HBRUSH C_Bomb;
//extern HBRUSH C_Wall;
//extern HBRUSH C_Fire;
//extern HBRUSH C_Effect;


extern bool flag_play;
extern Cell** map;
extern int NowTime;

extern const int shot_in_sec;

extern Player* player1;
extern Player* player2;

extern std::multiset<std::pair<int, Bomb*>> ActiveBomb;




