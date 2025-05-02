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
    moedas_de_ouro = 50; // O jogador começa com 50 moedas de ouro
    armadura = nullptr;
    arma = nullptr;
    
    // Alocação dinâmica dos vetores
    provisoes = new vector<Provisao*>();
    reliquias_magicas = new vector<ReliquiaMagica*>();
    equipamentos = new vector<Equipamento*>(); 
}

Personagem::~Personagem()
{
    if (provisoes) {
        // Liberar cada provisão individualmente
        for (Provisao* p : *provisoes) {
            delete p;
        }
        provisoes->clear();
        delete provisoes;
        provisoes = nullptr;
    }
    
    if (reliquias_magicas) {
        // Liberar cada relíquia individualmente
        for (ReliquiaMagica* r : *reliquias_magicas) {
            delete r;
        }
        reliquias_magicas->clear();
        delete reliquias_magicas;
        reliquias_magicas = nullptr;
    }
    
    // Liberar arma e armadura se existirem
    if (arma) {
        delete arma;
        arma = nullptr;
    }
    
    if (armadura) {
        delete armadura;
        armadura = nullptr;
    }

    if (equipamentos) {
        // Liberar cada equipamento individualmente
        for (Equipamento* e : *equipamentos) {
            delete e;
        }
        equipamentos->clear();
        delete equipamentos;
        equipamentos = nullptr;
    }
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
    habilidade = atributos[0] + 6;
    max_energia = atributos[1] + 12;
    energia_atual = atributos[1] + 12;
    sorte = atributos[2] + 6;
    cout << "Atributos do personagem carregados aleatoriamente:" << endl;
    cout << "Habilidade: " << atributos[0] << endl;
    cout << "Energia: " << atributos[1] << endl;
    cout << "Sorte: " << atributos[2] << endl;
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

void Personagem::equiparArmadura(Armadura* novaArmadura)
{
    if (!novaArmadura) return; // Proteção contra ponteiro nulo

    if (this->armadura != nullptr) {
        // Guarda o buff da armadura atual
        int buffAtual = this->armadura->getBuffResistencia();
        
        // Remove o buff da armadura atual
        setResistencia(getResistencia() - buffAtual);
        
        // Guarda uma referência temporária para a armadura atual
        Armadura* armaduraAntiga = this->armadura;
        
        // Atualiza o ponteiro para a nova armadura
        this->armadura = novaArmadura;
        
        // Adiciona a armadura antiga ao inventário (sem manipular a nova armadura)
        if (equipamentos == nullptr) {
            equipamentos = new vector<Equipamento*>();
        }
        equipamentos->push_back(armaduraAntiga);
    } else {
        // Não tinha armadura equipada, simplesmente equipa a nova
        this->armadura = novaArmadura;
    }
    
    // Adiciona o buff da nova armadura
    if (this->armadura != nullptr) {
        setResistencia(getResistencia() + this->armadura->getBuffResistencia());
    }
}

Armadura* Personagem::getArmadura()
{
    return armadura;
}

void Personagem::equiparArma(Arma* novaArma)
{
    if (!novaArma) return; // Proteção contra ponteiro nulo

    if (this->arma != nullptr) {
        // Guarda o buff da arma atual
        int buffAtual = this->arma->getBuffHabilidade();
        
        // Remove o buff da arma atual
        setHabilidade(getHabilidade() - buffAtual);
        
        // Guarda uma referência temporária para a arma atual
        Arma* armaAntiga = this->arma;
        
        // Atualiza o ponteiro para a nova arma
        this->arma = novaArma;
        
        // Adiciona a arma antiga ao inventário (sem manipular a nova arma)
        if (equipamentos == nullptr) {
            equipamentos = new vector<Equipamento*>();
        }
        equipamentos->push_back(armaAntiga);
    } else {
        // Não tinha arma equipada, simplesmente equipa a nova
        this->arma = novaArma;
    }
    
    // Adiciona o buff da nova arma
    if (this->arma != nullptr) {
        setHabilidade(getHabilidade() + this->arma->getBuffHabilidade());
    }
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
    if (!provisoes) {
        // Se o vetor ainda não foi alocado, alocar agora
        provisoes = new vector<Provisao*>();
    }
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
    if (!reliquias_magicas) {
        // Se o vetor ainda não foi alocado, alocar agora
        reliquias_magicas = new vector<ReliquiaMagica*>();
    }
    return *reliquias_magicas;
}

void Personagem::adicionarEquipamento(Equipamento* equipamento)
{
    if (!equipamentos) equipamentos = new vector<Equipamento*>();
    equipamentos->push_back(equipamento);
}

void Personagem::removerEquipamento(Equipamento* equipamento)
{
    if (!equipamentos) return;
    auto it = find(equipamentos->begin(), equipamentos->end(), equipamento);
    if (it != equipamentos->end()) {
        equipamentos->erase(it);
    }
}

vector<Equipamento*> Personagem::getEquipamentos()
{
    if (!equipamentos) {
        // Se o vetor ainda não foi alocado, alocar agora
        equipamentos = new vector<Equipamento*>();
    }
    return *equipamentos;
}

void Personagem::equiparEquipamento(int index)
{
    if (!equipamentos || index < 0 || index >= equipamentos->size()) {
        return;
    }

    // Guarda uma cópia do ponteiro do equipamento selecionado
    Equipamento* equipamento = equipamentos->at(index);
    
    // Remove o equipamento do vetor antes de tentar equipá-lo
    // Isso evita problemas se o mesmo objeto for referenciado em lugares diferentes
    equipamentos->erase(equipamentos->begin() + index);

    // Dynamic cast para verificar se o equipamento é uma armadura ou arma
    Armadura* armadura = dynamic_cast<Armadura*>(equipamento);
    if (armadura) {
        equiparArmadura(armadura);
        return;
    }
    
    Arma* arma = dynamic_cast<Arma*>(equipamento);
    if (arma) {
        equiparArma(arma);
        return;
    }
    
    // Se chegou aqui, não conseguiu equipar, então devolve para o inventário
    adicionarEquipamento(equipamento);
}