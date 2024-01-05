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
' ' - �������
V - �������
R - ������
W - �����
F - �����
E - �������
B - �����
I - ��������

*/

/*
*
N - ������
L - ������ �����   long
Q - ������� �����  quick
S - ��������
F - ������
I - ��������
A - �������������� �����
H - ���
R - ������ ���� = 1

*/

/*

S - ��������
B - ��������� ����
R - ������ ����

*/

