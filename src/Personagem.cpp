#include "../include/Personagem.h"
#include <algorithm>

using namespace std;

// Inicialização da instância estática
Personagem* Personagem::instance = nullptr;

Personagem::Personagem()
{
    max_energia = 0;
    energia_atual = 0;
    habilidade = 0;
    resistencia = 0;
    magia = 0;
    sorte = 0;
    moedas_de_ouro = 0;
    armadura = nullptr;
    arma = nullptr;
    provisoes = nullptr;
    reliquias_magicas = nullptr;
}

Personagem::~Personagem()
{
    if (provisoes) delete provisoes;
    if (reliquias_magicas) delete reliquias_magicas;
}

// Implementação do método Singleton para obter a instância
Personagem* Personagem::getInstance()
{
    if (instance == nullptr) {
        instance = new Personagem();
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

#include <ctime>
void Personagem::carregarAtributosAleatoriamente()
{
    // Inicializa o gerador de números aleatórios
    srand(static_cast<unsigned int>(time(0)));
    // O Personagem possui 12 pontos para distribuir entre os atributos
    int pontos_disponiveis = 12;
    int atributos[3] = {0, 0, 0}; // Habilidade, Energia, Sorte
    int i = 0;
    while (pontos_disponiveis > 0) {
        int pontos = rand() % (pontos_disponiveis + 1);
        atributos[i] += pontos;
        pontos_disponiveis -= pontos;
        i = (i + 1) % 3; // Rotaciona entre os atributos
    }
    habilidade = atributos[0];
    max_energia = atributos[1];
    energia_atual = atributos[1];
    sorte = atributos[2];
    cout << "Atributos do personagem carregados aleatoriamente:" << endl;
    cout << "Habilidade: " << habilidade << endl;
    cout << "Energia: " << max_energia << endl;
    cout << "Sorte: " << sorte << endl;
    cout << "Pressione ENTER para continuar..." << endl;
    cin.get();
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
    if(getArmadura() != nullptr) {
        setResistencia(getResistencia() - getArmadura()->getBuffResistencia());
        delete getArmadura();
    }
    this->armadura = armadura;
    setResistencia(getResistencia() + armadura->getBuffResistencia());
}

Armadura* Personagem::getArmadura()
{
    return armadura;
}

void Personagem::equiparArma(Arma* arma)
{
    if(getArma() != nullptr) {
        setHabilidade(getHabilidade() - getArma()->getBuffHabilidade());
        delete getArma();
    }
    this->arma = arma;
    setHabilidade(getHabilidade() + arma->getBuffHabilidade());
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

void Personagem::usarProvisao(Provisao* provisao)
{
    if (!provisoes) return;
    auto it = find(provisoes->begin(), provisoes->end(), provisao);
    if (it != provisoes->end()) {
        energia_atual += provisao->getBonusEnergia();
        if (energia_atual > max_energia) energia_atual = max_energia;
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
    setMagia(getMagia() + reliquia->getBuffMagia());
    setSorte(getSorte() + reliquia->getBuffSorte());
    setResistencia(getResistencia() + reliquia->getBuffResistencia());
    setHabilidade(getHabilidade() + reliquia->getBuffHabilidade());
    setMaxEnergia(getMaxEnergia() + reliquia->getBuffEnergia());
}

void Personagem::removerReliquiaMagica(ReliquiaMagica* reliquia)
{
    if (!reliquias_magicas) return;
    auto it = find(reliquias_magicas->begin(), reliquias_magicas->end(), reliquia);
    if (it != reliquias_magicas->end()) {
        reliquias_magicas->erase(it);

		// Atualiza os atributos do personagem
		setMagia(getMagia() - reliquia->getBuffMagia());
		setSorte(getSorte() - reliquia->getBuffSorte());
		setResistencia(getResistencia() - reliquia->getBuffResistencia());
		setHabilidade(getHabilidade() - reliquia->getBuffHabilidade());
		setMaxEnergia(getMaxEnergia() - reliquia->getBuffEnergia());
    }
}

vector<ReliquiaMagica*> Personagem::getReliquiasMagicas()
{
    if (!reliquias_magicas) return vector<ReliquiaMagica*>();
    return *reliquias_magicas;
}