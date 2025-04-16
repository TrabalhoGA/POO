#pragma once
#ifndef ITEM_H
#define ITEM_H

#include <iostream>

using namespace std;

class Item {
public:
	Item();
	virtual ~Item();

	void setNome(string n);
	string getNome();

	void setDescricao(string d);
	string getDescricao();

	void setMagiaMinimaNecessaria(int m);
	int getMagiaMinimaNecessaria();

	virtual void exibir_atributos() = 0;

protected:
	string nome;
	string descricao;
	int magia_minima_necessaria;
private:

};

#endif // ITEM_H