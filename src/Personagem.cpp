#include "../include/Personagem.h"
#include <algorithm>

using namespace std;

// Inicialização da instância estática
Personagem* Personagem::instance = nullptr;

Personagem::Personagem(int e, int h, int r, int m, int s)
    : max_energia(e), energia_atual(e), habilidade(h), resistencia(r), magia(m), sorte(s), moedas_de_ouro(0), armadura(nullptr), arma(nullptr), provisoes(nullptr), reliquias_magicas(nullptr)
{
    //ctor
}

Personagem::~Personagem()
{
    if (provisoes) delete provisoes;
    if (reliquias_magicas) delete reliquias_magicas;
}

// Implementação do método Singleton para obter a instância
Personagem* Personagem::getInstance(int e, int h, int r, int m, int s)
{
    if (instance == nullptr) {
        instance = new Personagem(e, h, r, m, s);
    }
    return instance;
}

// Método para resetar a instância
void Personagem::resetInstance()
{
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
    }
}

// Método para liberar a instância
void Personagem::releaseInstance()
{
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
    }
}

void Personagem::setMaxEnergia(int e)
{
    max_energia = e;
}

int Personagem::getMaxEnergia()
{
    return max_energia;
}

void Personagem::setEnergiaAtual(int e)
{
    energia_atual = e;
}

int Personagem::getEnergiaAtual()
{
    return energia_atual;
}

void Personagem::setHabilidade(int h)
{
    habilidade = h;
}

int Personagem::getHabilidade()
{
    return habilidade;
}

void Personagem::setResistencia(int r)
{
    resistencia = r;
}

int Personagem::getResistencia()
{
    return resistencia;
}

void Personagem::setMagia(int m)
{
    magia = m;
}

int Personagem::getMagia()
{
    return magia;
}

void Personagem::setSorte(int s)
{
    sorte = s;
}

int Personagem::getSorte()
{
    return sorte;
}

void Personagem::setMoedasDeOuro(int m)
{
    moedas_de_ouro = m;
}

int Personagem::getMoedasDeOuro()
{
    return moedas_de_ouro;
}

void Personagem::equiparArmadura(Armadura* armadura)
{
    this->armadura = armadura;
}

Armadura* Personagem::getArmadura()
{
    return armadura;
}

void Personagem::equiparArma(Arma* arma)
{
    this->arma = arma;
}

Arma* Personagem::getArma()
{
    return arma;
}

void Personagem::adicionarProvisao(Provisao* provisao)
{
    if (!provisoes) provisoes = new vector<Provisao*>();
    provisoes->push_back(provisao);
}

void Personagem::removerProvisao(Provisao* provisao)
{
    if (!provisoes) return;
    auto it = find(provisoes->begin(), provisoes->end(), provisao);
    if (it != provisoes->end()) {
        provisoes->erase(it);
    }
}

vector<Provisao*> Personagem::getProvisoes()
{
    if (!provisoes) return vector<Provisao*>();
    return *provisoes;
}

void Personagem::adicionarReliquiaMagica(ReliquiaMagica* reliquia)
{
    if (!reliquias_magicas) reliquias_magicas = new vector<ReliquiaMagica*>();
    reliquias_magicas->push_back(reliquia);
}

void Personagem::removerReliquiaMagica(ReliquiaMagica* reliquia)
{
    if (!reliquias_magicas) return;
    auto it = find(reliquias_magicas->begin(), reliquias_magicas->end(), reliquia);
    if (it != reliquias_magicas->end()) {
        reliquias_magicas->erase(it);
    }
}

vector<ReliquiaMagica*> Personagem::getReliquiasMagicas()
{
    if (!reliquias_magicas) return vector<ReliquiaMagica*>();
    return *reliquias_magicas;
}