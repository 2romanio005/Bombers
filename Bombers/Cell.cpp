#pragma once
#include "Cell.h"

Cell::Cell()
{
	keep = nullptr;
	type = ' ';
}

Cell::~Cell()
{
	set(nullptr, ' ');
}

char Cell::get_type()
{
	return this->type;
}

Item* Cell::get_keep()
{
	return this->keep;
}

void Cell::set(Item* keep, char type)
{
	if (this->type != type) {
		if (this->keep != nullptr) {
			delete (this->keep);
		}
		this->keep = keep;
		this->type = type;
	}
	else {
		delete keep;
		keep = nullptr;
	}
}
