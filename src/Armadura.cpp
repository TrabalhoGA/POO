#include "../include/Armadura.h"

using namespace std;

Armadura::Armadura(string n, string d, int h, int r, int b) : Equipamento()
{
	setNome(n);
	setDescricao(d);
	setHabilidadeMinimaNecessaria(h);
	setResistenciaMinimaNecessaria(r);
	buff_resistencia = b;
}

Armadura::~Armadura()
{
	//dtor
}

void Armadura::setBuffResistencia(int b)
{
	buff_resistencia = b;
}

int Armadura::getBuffResistencia()
{
	return buff_resistencia;
}

void Armadura::evoluir_equipamento(int b)
{
	buff_resistencia += b;
}