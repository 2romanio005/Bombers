#pragma once
#include "Definitions.h"
class Player;

class Item {
public:
	Item() {}

	~Item() {
		int a = 0;
	}

	void virtual Draw(HDC hdc, std::pair<float, float> place) {}

	void virtual Break(std::pair<int, int> map_cord);
};

class Void : public Item
{
public:
	Void() {}

	void Draw(HDC hdc, std::pair<float, float> place);
};

class Barrier : public Item
{
public:
	Barrier() {}

	void Draw(HDC hdc, std::pair<float, float> place);

	void Break(std::pair<int, int> map_cord);
};

class Wall : public Item
{
public:
	Wall() {}

	void Draw(HDC hdc, std::pair<float, float> place);

	void Break(std::pair<int, int> map_cord) {}
};

class Fire : public Item
{
public:
	Fire(int timeout);

	void Draw(HDC hdc, std::pair<float, float> place);

	void Break(std::pair<int, int> map_cord);

	void set_timeout(int timeout);
private:
	int timeout;

	void check_timout(std::pair<float, float> place);
};

class Effect : public Item
{
public:
	Effect(char type_effect);
	void Draw(HDC hdc, std::pair<float, float> place);

	void Break(std::pair<int, int> map_cord);

	char get_type_effect();
private:
	char type_effect;
};

class Improve : public Item
{
public:
	Improve(char type_improve);

	void Draw(HDC hdc, std::pair<float, float> place);

	void Break(std::pair<int, int> map_cord);

	void Use(Player* player);
private:
	char type_improve;
};

class Bomb : public Item
{
public:
	Bomb(Player* creater, std::pair<int, int> map_cord, int timeout, int radius);

	//~Bomb();

	void Draw(HDC hdc, std::pair<float, float> place);

	void Detonation();
	//friend bool operator< (const Bomb& one, const Bomb& two);

private:
	std::pair<int, int> map_cord;
	int radius;
	int timeout;

	bool IBroken = 0;  // нужно, чтобы когда бомбы взрываются, они не вошли в бесконечный цикл
	Player* creater = nullptr;
	//int init(int x) { return x; }
};







