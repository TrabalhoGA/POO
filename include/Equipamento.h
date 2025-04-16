#pragma once
#ifndef EQUIPAMENTO_H
#define EQUIPAMENTO_H

#include <iostream>

using namespace std;

class Equipamento
{
public:
	Equipamento();
	virtual ~Equipamento();

	void setNome(string n);
	string getNome();

	void setDescricao(string d);
	string getDescricao();

	void setHabilidadeMinimaNecessaria(int h);
	int getHabilidadeMinimaNecessaria();

	void setResistenciaMinimaNecessaria(int r);
	int getResistenciaMinimaNecessaria();

	virtual void evoluir_equipamento(int buff) = 0;

protected:
	string nome;
	string descricao;
	int habilidade_minima_necessaria;
	int resistencia_minima_necessaria;
private:

};

#endif // EQUIPAMENTO_H