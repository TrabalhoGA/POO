#pragma once
#ifndef ARMA_H
#define ARMA_H

#include "Equipamento.h"

using namespace std;

class Arma : public Equipamento
{
public:
	Arma(string n, string d, int a, int r, int b);
	virtual ~Arma();

	void setBuffHabilidade(int b);
	int getBuffHabilidade();

	void evoluir_equipamento(int buff) override;
protected:

private:
	int buff_habilidade;
};

#endif // ARMA_H