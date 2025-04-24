#include "../include/Monstro.h"

using namespace std;

// Inicialização do atributo estático
Monstro* Monstro::instance = nullptr;

// Construtor privado
Monstro::Monstro(string n, int e, int h, int r) : nome(n), energia(e), habilidade(h), resistencia(r)
{
	//ctor
}

Monstro::~Monstro()
{
	//dtor
}

// Método para obter a instância única
Monstro* Monstro::getInstance(string n, int e, int h, int r)
{
	if (instance == nullptr) {
		instance = new Monstro(n, e, h, r);
	} else if (!n.empty()) {
		// Se já existe uma instância mas novos dados foram fornecidos,
		// atualiza os atributos da instância existente
		instance->setNome(n);
		instance->setEnergia(e);
		instance->setHabilidade(h);
		instance->setResistencia(r);
	}
	return instance;
}

// Método para liberar a instância
void Monstro::releaseInstance()
{
	if (instance != nullptr) {
		delete instance;
		instance = nullptr;
	}
}

void Monstro::setNome(string n)
{
	nome = n;
}

string Monstro::getNome()
{
	return nome;
}

void Monstro::setEnergia(int e)
{
	energia = e;
}

int Monstro::getEnergia()
{
	return energia;
}

void Monstro::setHabilidade(int h)
{
	habilidade = h;
}

int Monstro::getHabilidade()
{
	return habilidade;
}

void Monstro::setResistencia(int r)
{
	resistencia = r;
}

int Monstro::getResistencia()
{
	return resistencia;
}