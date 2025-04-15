#pragma once
#ifndef MONSTRO_H
#define MONSTRO_H

#include <iostream>

using namespace std;

class Monstro
{
public:
	Monstro(string n, int e, int h, int r);
	virtual ~Monstro();

	void setNome(string n);
	string getNome();

	void setEnergia(int e);
	int getEnergia();

	void setHabilidade(int h);
	int getHabilidade();

	void setResistencia(int r);
	int getResistencia();

protected:

private:
	string nome;
	int energia;
	int habilidade;
	int resistencia;
};

#endif // MONSTRO_H