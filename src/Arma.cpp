#include "../include/Arma.h"

using namespace std;

Arma::Arma(string n, string d, int a, int r, int b) : Equipamento()
{
	setNome(n);
	setDescricao(d);
	setHabilidadeMinimaNecessaria(a);
	setResistenciaMinimaNecessaria(r);
	buff_habilidade = b;
}

Arma::~Arma()
{
	//dtor
}

void Arma::setBuffHabilidade(int b)
{
	buff_habilidade = b;
}

int Arma::getBuffHabilidade()
{
	return buff_habilidade;
}

void Arma::evoluir_equipamento(int b)
{
	buff_habilidade += b;
}