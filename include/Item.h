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

protected:
	string nome;
	string descricao;
	int magia_minima_necessaria;
private:

};

#endif // ITEM_H