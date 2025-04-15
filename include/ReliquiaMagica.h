#pragma once
#ifndef RELIQUIAMAGICA_H
#define RELIQUIAMAGICA_H

#include "Item.h"

using namespace std;

class ReliquiaMagica : public Item {
public:
	ReliquiaMagica(string n, string d, int m);
	virtual ~ReliquiaMagica();

	void setBuffEnergia(int e);
	int getBuffEnergia();

	void setBuffHabilidade(int h);
	int getBuffHabilidade();

	void setBuffResistencia(int r);
	int getBuffResistencia();

	void setBuffMagia(int m);
	int getBuffMagia();

	void setBuffSorte(int s);
	int getBuffSorte();

	void exibir_buffs();

protected:

private:
	int buff_energia;
	int buff_habilidade;
	int buff_resistencia;
	int buff_magia;
	int buff_sorte;
};

#endif // RELIQUIAMAGICA_H