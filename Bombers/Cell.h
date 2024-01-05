#pragma once
#include "Definitions.h"

class Void;
class Item;

class Cell
{
public:
	Cell();

	~Cell();

	char get_type();
	Item* get_keep();

	void set(Item* keep, char type);

private:
	char type;
	Item* keep;
};

/*
* 
' ' - сначала
V - пустота
R - барьер
W - стена
F - огонь
E - эффекты
B - бомбы
I - улучшать

*/

/*
*
N - ничего
L - долгие бомбы   long
Q - быстрые бомбы  quick
S - медленно
F - быстро
I - инверсия
A - автоматические бомбы
H - щит
R - радиус бомб = 1

*/

/*

S - скорость
B - количство бомб
R - радиус бомб

*/

