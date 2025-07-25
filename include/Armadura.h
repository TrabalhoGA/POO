#pragma once
#ifndef ARMADURA_H
#define ARMADURA_H

#include "Equipamento.h"

using namespace std;

class Armadura : public Equipamento
{
public:
	Armadura(string n, string d, int h, int r, int b);
	virtual ~Armadura();

	void setBuffResistencia(int b);
	int getBuffResistencia();

	void evoluir_equipamento(int buff) override;
protected:

private:
	int buff_resistencia;
};

#endif // ARMADURA_H
