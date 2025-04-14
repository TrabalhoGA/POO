#include "../include/Provisao.h"

using namespace std;

Provisao::Provisao(string n, string d, int m, int b) : Item()
{
	setNome(n);
	setDescricao(d);
	setMagiaMinimaNecessaria(m);
	bonus_energia = b;
}

Provisao::~Provisao()
{
	//dtor
}

void Provisao::setBonusEnergia(int b)
{
	bonus_energia = b;
}

int Provisao::getBonusEnergia()
{
	return bonus_energia;
}