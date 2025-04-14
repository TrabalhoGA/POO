#pragma once
#include "Item.h"
class Provisao :
    public Item
{
public:
	Provisao(string n, string d, int m, int b);
	virtual ~Provisao();

	void setBonusEnergia(int b);
	int getBonusEnergia();

protected:

private:
	int bonus_energia;
};

