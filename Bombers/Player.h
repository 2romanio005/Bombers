#pragma once
#include "Definitions.h"



class Player
{
public:
	Player(HBRUSH color);

	~Player();

	void Reset(std::pair<float, float> cord, float speed, int max_bombs, int radius_bomb, int time_bomb);

	void Muve();

	void MuveCommand(char type_command);

	void Draw(HDC hdc);

	void set_bomb();

	void clear_stack();

	//std::pair<float, float> get_cord();

	//char get_effect();

	bool get_life();

	void improve_speed(float step);
	void improve_free_bomb(int step);
	void improve_radius_bomb(int step);

private:
	std::deque<std::pair<float, float>> stack;

	std::pair<float, float> cord;   // x, y
	std::pair<int, int> map_cord;   // x, y
	float speed = 0;
	int free_bomb = 0, radius_bomb = 0, time_bomb = 0;
	
	char effect = 'N';
	int timeout_Effect = 0;

	bool life = 0;
	HBRUSH color;

	HBRUSH green = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH red = CreateSolidBrush(RGB(255, 0, 0));

	void check_effect();
	void check_improve();
	void check_life();
};

/*
*
N - ничего
R - долгие бомбы
L - быстрые бомбы
S - медленно
F - быстро
I - инверсия
A - автоматические бомбы
H - щит

*/
