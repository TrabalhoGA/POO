#pragma once
#ifndef MONSTRO_H
#define MONSTRO_H

#include <iostream>

using namespace std;

class Monstro
{
private:
	static Monstro* instance;
	string nome;
	int energia;
	int habilidade;
	int resistencia;
	
	// Construtor privado para impedir instanciação direta
	Monstro(string n, int e, int h, int r);

public:
	virtual ~Monstro();
	
	// Método para obter a instância única
	static Monstro* getInstance(string n = "", int e = 0, int h = 0, int r = 0);
	
	// Método para liberar a instância
	static void releaseInstance();

	void setNome(string n);
	string getNome();

	void setEnergia(int e);
	int getEnergia();

	void setHabilidade(int h);
	int getHabilidade();

	void setResistencia(int r);
	int getResistencia();
};

#endif // MONSTRO_H