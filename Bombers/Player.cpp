#pragma once
#include "Player.h"


Player::Player(HBRUSH color)
{
	this->color = color;
}

Player::~Player()
{
	DeleteObject(this->color);
	DeleteObject(this->green);
	DeleteObject(this->red);
}


void Player::Reset(std::pair<float, float> cord, float speed, int free_bomb, int radius_bomb, int time_bomb)
{
	this->cord = cord;
	this->map_cord.first = round(cord.first / size_cell);
	this->map_cord.second = round(cord.second / size_cell);

	this->speed = speed;
	this->free_bomb = free_bomb;
	this->radius_bomb = radius_bomb;
	this->time_bomb = time_bomb;
	this->effect = 'N';

	this->life = 1;

	this->stack.clear();
}

void Player::Muve()
{
	if (!life) return;
	if (!stack.empty()) {
		std::pair<float, float>& next = this->stack.front();

		float* wrong;
		float  norm;
		if (cord.first == next.first) {  // идём по y
			wrong = &(cord.second);
			norm = next.second;
		}
		else {							// идём по x
			wrong = &(cord.first);      
			norm = next.first;
		}
		float step;
		switch (this->effect)
		{
		case 'S':
			step = min_speed + this->speed - start_speed;
			break;
		case 'F':
			step = max_speed + this->speed - start_speed;
			break;
		default:
			step = this->speed;
			break;
		}
		



		if (abs(norm - *wrong) <= step) {
			*wrong = norm;
			stack.pop_front();
			if (this->stack.size() != 0 &&  map[int((stack.front().first) / size_cell + 1)][int((stack.front().second) / size_cell + 1)].get_type() == 'B') {
				this->stack.clear();
				return;
			}
		}
		else {
			if (norm > *wrong) {
				*wrong += step;
			}
			else {
				*wrong -= step;
			}
		}
		map_cord.first = (cord.first) / size_cell + 1;
		map_cord.second = (cord.second) / size_cell + 1;


		//map_cord.first = (cord.first + size_cell / 2) / size_cell;
		//map_cord.second = (cord.second + size_cell / 2) / size_cell;
	}

	this->check_effect();
	this->check_improve();
	this->check_life();

}

void Player::MuveCommand(char type_command)
{
	std::pair<float, float> next;

	if (this->stack.size() == 0) {
		next = this->cord;
	}
	else {
		next = (this->stack).back();
	}

	int effect_size_cell = (this->effect == 'I' ? -size_cell : size_cell); // чтобы размернуть при инверисии
	switch (type_command) {
	case 'U':
		next.second -= effect_size_cell;
		break;
	case 'D':
		next.second += effect_size_cell;
		break;
	case 'L':
		next.first -= effect_size_cell;
		break;
	case 'R':
		next.first += effect_size_cell;
	}


	char cell = map[int((next.first + size_cell / 2) / size_cell)][int((next.second + size_cell / 2) / size_cell)].get_type();
	if (cell == 'V' || cell == 'E' || cell == 'I' || cell == 'F') {
		if (this->stack.size() == 1) {
			bool (*compare)(float l, float m, float r) = [](float l, float m, float r) {
				return ((l < m) && (m < r));
			};

			if (compare(this->stack.back().first, this->cord.first, this->cord.first) || compare(next.first, this->cord.first, this->stack.back().first) ||
				compare(this->stack.back().second, this->cord.second, this->cord.second) || compare(next.second, this->cord.second, this->stack.back().second))
			{
				this->stack.pop_back();
			}
			this->stack.push_back(next);
		}
		else if (this->stack.size() > 1) {
			if (next == this->stack[this->stack.size() - 2]) {
				this->stack.pop_back();
			}
			else {
				this->stack.push_back(next);
			}
		}
		else {
			this->stack.push_back(next);
		}
	}
}

void Player::Draw(HDC hdc)
{
	float r;
	if (this->life) {
		r = 0.35 * size_cell;
		if (this->effect != 'N') {
			if (this->effect == 'H') {
				SelectObject(hdc, this->green);
			}
			else {
				SelectObject(hdc, this->red);
			}
			RoundRect(hdc, this->cord.first - r, this->cord.second - r, this->cord.first + r, this->cord.second + r, r * 2, r * 2);

			r = (0.35 - 0.07 * (0.3 + float(timeout_Effect - NowTime) / time_Effect)) * size_cell;
		}
		//StretchBlt(hdc, this->cord.first, this->cord.second, size_cell, size_cell, I_Player, 0, 0, size_bmp_image, size_bmp_image, SRCCOPY);
	}
	else {
		r = 0.2 * size_cell;
		//StretchBlt(hdc, this->cord.first, this->cord.second, size_cell / 2, size_cell / 2, I_Player_dead, 0, 0, size_bmp_image, size_bmp_image, SRCCOPY);
	}
	SelectObject(hdc, this->color);
	RoundRect(hdc, this->cord.first - r, this->cord.second - r, this->cord.first + r, this->cord.second + r, r * 2, r * 2);
}

void Player::set_bomb() {
	if (!life) return;
	if (free_bomb > 0) {
		Cell* cell = &map[map_cord.first][map_cord.second];
		if ((*cell).get_type() == 'V') {
			int time;
			switch (this->effect)
			{
			case 'Q':
				time = min_time_bomb;
				break;
			case 'L':
				time = max_time_bomb;
				break;
			default:
				time = this->time_bomb;
				break;
			}
			time += NowTime;

			(*cell).set(new Bomb(this, this->map_cord, time, (this->effect == 'R') ? 1 : this->radius_bomb), 'B');
			this->free_bomb--;
			ActiveBomb.insert({time, (Bomb*)((*cell).get_keep())});
		}
	}

}

void Player::clear_stack()
{
	while (this->stack.size() > 1) {
		this->stack.pop_back();
	}
}

//std::pair<float, float> Player::get_cord()
//{
//	return cord;
//}

//char Player::get_effect()
//{
//	return this->effect;
//}

bool Player::get_life()
{
	return life;
}

void Player::improve_speed(float step)
{
	this->speed += step;
}

void Player::improve_free_bomb(int step)
{
	this->free_bomb += step;
}

void Player::improve_radius_bomb(int step)
{
	this->radius_bomb += step;
}

void Player::check_effect()
{
	Cell* cell = &(map[map_cord.first][map_cord.second]);
	if ((*cell).get_type() == 'E') {
		this->effect = (*((Effect*)((*cell).get_keep()))).get_type_effect();
		this->timeout_Effect = NowTime + time_Effect;
		(*(Effect*)(*cell).get_keep()).Break(this->map_cord);
	}

	if (this->effect == 'A') {
		this->set_bomb();
	} 

	if (this->effect != 'N' && NowTime >= this->timeout_Effect) {
		this->effect = 'N';
	}
	
}

void Player::check_improve()
{
	Cell* cell = &(map[map_cord.first][map_cord.second]);
	if ((*cell).get_type() == 'I') {
		(*(Improve*)(*cell).get_keep()).Use(this);
		(*(Improve*)(*cell).get_keep()).Break(this->map_cord);
	}
}

void Player::check_life() {
	if (this->effect != 'H' && map[map_cord.first][map_cord.second].get_type() == 'F') {
		life = 0;
	}
}




