#pragma once
#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include "Armadura.h"
#include "Arma.h"
#include "Provisao.h"
#include "ReliquiaMagica.h"

#include <vector>

using namespace std;

class Personagem
{
    private:
        // Construtor privado (parte do padrão Singleton)
        Personagem();
        // Instância estática
        static Personagem* instance;
        
        // Atributos da classe
        int max_energia;
        int energia_atual;
        int habilidade;
        int resistencia;
        int magia;
        int sorte;
        int moedas_de_ouro;
        Armadura* armadura;
        Arma* arma;
        vector<Provisao*>* provisoes;
        vector<ReliquiaMagica*>* reliquias_magicas;
        vector<Equipamento*>* equipamentos;

    public:
        // Proibir cópia e atribuição
        Personagem(const Personagem&) = delete;
        Personagem& operator=(const Personagem&) = delete;
        
        virtual ~Personagem();

        // Método estático para acessar a instância única
        static Personagem* getInstance();
        
        // Métodos para resetar ou liberar a instância
        static void resetInstance();
        static void releaseInstance();

        void carregarAtributosAleatoriamente();

        void setMaxEnergia(int e);
        int getMaxEnergia();

        void setEnergiaAtual(int e);
        int getEnergiaAtual();

        void setHabilidade(int h);
        int getHabilidade();

        void setResistencia(int r);
        int getResistencia();

        void setMagia(int m);
        int getMagia();

        void setSorte(int s);
        int getSorte();

        void setMoedasDeOuro(int m);
        int getMoedasDeOuro();

        void equiparArmadura(Armadura* novaArmadura);
        Armadura* getArmadura();

        void equiparArma(Arma* novaArma);
        Arma* getArma();

        void adicionarProvisao(Provisao* provisao);
        void removerProvisao(Provisao* provisao);
        void usarProvisao(Provisao* provisao);
        vector<Provisao*> getProvisoes();

        void adicionarReliquiaMagica(ReliquiaMagica* reliquia);
        void removerReliquiaMagica(ReliquiaMagica* reliquia);
        vector<ReliquiaMagica*> getReliquiasMagicas();

        void adicionarEquipamento(Equipamento* equipamento);
        void removerEquipamento(Equipamento* equipamento);
        vector<Equipamento*> getEquipamentos();
        void equiparEquipamento(int index);
};

#endif // PERSONAGEM_H