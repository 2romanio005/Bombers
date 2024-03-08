#pragma once
#include "Items.h"

void Item::Break(std::pair<int, int> map_cord)
{
	map[map_cord.first][map_cord.second].set(new Fire(NowTime + time_Fire), 'F');
}


void Void::Draw(HDC hdc, std::pair<float, float> place)
{
	StretchBlt(hdc, place.first, place.second, size_cell, size_cell, I_Void, 0, 0, size_bmp_image, size_bmp_image, SRCCOPY);

	//SelectObject(hdc, C_Void);
	//Rectangle(hdc, place.first, place.second, place.first + size_cell, place.second + size_cell);
}


void Barrier::Draw(HDC hdc, std::pair<float, float> place)
{              
	StretchBlt(hdc, place.first, place.second, size_cell, size_cell, I_Barrier, 0, 0, size_bmp_image, size_bmp_image, SRCCOPY);

	//SelectObject(hdc, C_Barrier);
	//Rectangle(hdc, place.first, place.second, place.first + size_cell, place.second + size_cell);
}

void Barrier::Break(std::pair<int, int> map_cord)
{
	int r = rand() % 100;
	char type = 'H';
	if (r < chance_effect) {
		switch (rand() % 9) {
		case 0:
			type = 'L';
			break;
		case 1:
			type = 'Q';
			break;
		case 2:
			type = 'S';
			break;
		case 3:
			type = 'F';
			break;
		case 4:
			type = 'I';
			break;
		case 5:
			type = 'A';
			break;
		case 6:
			type = 'R';
			break;
		case 7: case 8:
			type = 'H';
			break;
		}
		map[map_cord.first][map_cord.second].set(new Effect(type), 'E');
	}
	r -= chance_effect;

	if (r >= 0 && r < chence_improve) {
		switch (rand() % 3) {
		case 0:
			type = 'S';
			break;
		case 1:
			type = 'B';
			break;
		case 2:
			type = 'R';
			break;
		}
		map[map_cord.first][map_cord.second].set(new Improve(type), 'I');
	}
	r -= chence_improve;

	if(r >= 0) {
		map[map_cord.first][map_cord.second].set(new Void, 'V');
	}
}


void Wall::Draw(HDC hdc, std::pair<float, float> place)
{
	StretchBlt(hdc, place.first, place.second, size_cell, size_cell, I_Wall, 0, 0, size_bmp_image, size_bmp_image, SRCCOPY);

	//SelectObject(hdc, C_Wall);
	//Rectangle(hdc, place.first, place.second, place.first + size_cell, place.second + size_cell);
}


Fire::Fire(int timeout)
{
	this->timeout = timeout;
}

void Fire::Draw(HDC hdc, std::pair<float, float> place)
{
	StretchBlt(hdc, place.first, place.second, size_cell, size_cell, I_Fire, 0, 0, size_bmp_image, size_bmp_image, SRCCOPY);

	this->check_timout(place);
	//SelectObject(hdc, C_Fire);
	//Rectangle(hdc, place.first, place.second, place.first + size_cell, place.second + size_cell);
}

void Fire::Break(std::pair<int, int> map_cord)
{
	map[map_cord.first][map_cord.second].set(new Void, 'V');
}

void Fire::set_timeout(int timeout)
{
	this->timeout = timeout;
}

void Fire::check_timout(std::pair<float, float> place)
{
	if (NowTime >= this->timeout) {
		map[int(place.first / size_cell + 1)][int(place.second / size_cell + 1)].set(new Void, 'V');
	}
}


Effect::Effect(char type_effect)
{
	this->type_effect = type_effect;
}

void Effect::Draw(HDC hdc, std::pair<float, float> place)
{
	switch (this->type_effect)
	{
	case 'H':
		StretchBlt(hdc, place.first, place.second, size_cell, size_cell, I_Effect_shild, 0, 0, size_bmp_image, size_bmp_image, SRCCOPY);
		break;
	default:
		StretchBlt(hdc, place.first, place.second, size_cell, size_cell, I_Effect, 0, 0, size_bmp_image, size_bmp_image, SRCCOPY);
		break;
	}
}

void Effect::Break(std::pair<int, int> map_cord)
{
	map[map_cord.first][map_cord.second].set(new Void, 'V');
}

char Effect::get_type_effect()
{
	return this->type_effect;
}


Improve::Improve(char type_improve)
{
	this->type_improve = type_improve;
}

void Improve::Draw(HDC hdc, std::pair<float, float> place)
{
	switch (this->type_improve) {
	case 'S':
		StretchBlt(hdc, place.first, place.second, size_cell, size_cell, I_Improve_speed, 0, 0, size_bmp_image, size_bmp_image, SRCCOPY);
		break;
	case 'B':
		StretchBlt(hdc, place.first, place.second, size_cell, size_cell, I_Improve_max_bomb, 0, 0, size_bmp_image, size_bmp_image, SRCCOPY);
		break;
	case 'R':
		StretchBlt(hdc, place.first, place.second, size_cell, size_cell, I_Improve_radius_bomb, 0, 0, size_bmp_image, size_bmp_image, SRCCOPY);
		break;
	default:
		StretchBlt(hdc, place.first, place.second, size_cell, size_cell, I_Improve, 0, 0, size_bmp_image, size_bmp_image, SRCCOPY);
		break;
	}
}

void Improve::Break(std::pair<int, int> map_cord)
{
	map[map_cord.first][map_cord.second].set(new Void, 'V');
}

void Improve::Use(Player* player)
{
	switch (this->type_improve) {
	case 'S':
		(*player).improve_speed(improve_step_speed);
		break;
	case 'B':
		(*player).improve_free_bomb(1);
		break;
	case 'R':
		(*player).improve_radius_bomb(1);
		break;
	}
}


Bomb::Bomb(Player* creater, std::pair<int, int> map_cord, int timeout, int radius){
	this->creater = creater;

	this->map_cord = map_cord;
	this->timeout = timeout;
	this->radius = radius;
}

//Bomb::~Bomb()
//{
//	this->creater = nullptr;
//}

void Bomb::Draw(HDC hdc, std::pair<float, float> place)
{
	StretchBlt(hdc, place.first, place.second, size_cell, size_cell, I_Bomb, 0, 0, size_bmp_image, size_bmp_image, SRCCOPY);

	//SelectObject(hdc, C_Bomb);
	//Rectangle(hdc, place.first, place.second, place.first + size_cell, place.second + size_cell);
}

void Bomb::Detonation()
{
	if (this->IBroken) return;

	bool (*CellDetonation)(int x, int y) = [](int x, int y) {
		char type = map[x][y].get_type();
		if (type == 'W') { return true; }

		if (type == 'R' || type == 'E' || type == 'I') {
			
			//(*broken).push({ x, y });
			(*(map[x][y].get_keep())).Break({x, y});
			return true;
		}
		
		if (type == 'F') {
			(*(Fire*)(map[x][y].get_keep())).set_timeout(NowTime + time_Fire);
		}else if (type == 'B') {
			(*(Bomb*)(map[x][y].get_keep())).Detonation();
		}
		else {
			map[x][y].set(new Fire(NowTime + time_Fire), 'F');
		}

		return false;
	};

	IBroken = 1;

	for (int i = this->map_cord.first + 1; i <= this->map_cord.first + this->radius; i++)   { if (CellDetonation(i, this->map_cord.second)) break; }     // вправо
	for (int i = this->map_cord.first - 1; i >= this->map_cord.first - this->radius; i--)   { if (CellDetonation(i, this->map_cord.second)) break; }	  // влево
	for (int i = this->map_cord.second - 1; i >= this->map_cord.second - this->radius; i--) { if (CellDetonation(this->map_cord.first, i)) break;  }     // вверх
	for (int i = this->map_cord.second + 1; i <= this->map_cord.second + this->radius; i++) { if (CellDetonation(this->map_cord.first, i)) break;  }     // вниз

	(*creater).improve_free_bomb(1);
	ActiveBomb.erase({ this->timeout, this });
	map[this->map_cord.first][this->map_cord.second].set(new Fire(NowTime + time_Fire), 'F');
	
}

//bool operator<(const Bomb& one, const Bomb& two)
//{
//	return one.timeout < two.timeout;
//}

