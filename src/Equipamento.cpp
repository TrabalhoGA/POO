#include "../include/Equipamento.h"

using namespace std;

Equipamento::Equipamento()
{
	//ctor
}

Equipamento::~Equipamento()
{
	//dtor
}

void Equipamento::setNome(string n)
{
	nome = n;
}

string Equipamento::getNome()
{
	return nome;
}

void Equipamento::setDescricao(string d)
{
	descricao = d;
}

string Equipamento::getDescricao()
{
	return descricao;
}

void Equipamento::setHabilidadeMinimaNecessaria(int h)
{
	habilidade_minima_necessaria = h;
}

int Equipamento::getHabilidadeMinimaNecessaria()
{
	return habilidade_minima_necessaria;
}

void Equipamento::setResistenciaMinimaNecessaria(int r)
{
	resistencia_minima_necessaria = r;
}

int Equipamento::getResistenciaMinimaNecessaria()
{
	return resistencia_minima_necessaria;
}

