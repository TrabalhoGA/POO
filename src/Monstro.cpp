#include "../include/Monstro.h"

using namespace std;

Monstro::Monstro(string n, int e, int h, int r) : nome(n), energia(e), habilidade(h), resistencia(r)
{
	//ctor
}

Monstro::~Monstro()
{
	//dtor
}

void Monstro::setNome(string n)
{
	nome = n;
}

string Monstro::getNome()
{
	return nome;
}

void Monstro::setEnergia(int e)
{
	energia = e;
}

int Monstro::getEnergia()
{
	return energia;
}

void Monstro::setHabilidade(int h)
{
	habilidade = h;
}

int Monstro::getHabilidade()
{
	return habilidade;
}

void Monstro::setResistencia(int r)
{
	resistencia = r;
}

int Monstro::getResistencia()
{
	return resistencia;
}