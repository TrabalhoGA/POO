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
    public:
		Personagem(int e, int h, int r, int m, int s);
		virtual ~Personagem();

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

		void equiparArmadura(Armadura* armadura);
		Armadura* getArmadura();

		void equiparArma(Arma* arma);
		Arma* getArma();

		void adicionarProvisao(Provisao* provisao);
		void removerProvisao(Provisao* provisao);
		vector<Provisao*> getProvisoes();

		void adicionarReliquiaMagica(ReliquiaMagica* reliquia);
		void removerReliquiaMagica(ReliquiaMagica* reliquia);
		vector<ReliquiaMagica*> getReliquiasMagicas();

    protected:

    private:
		int max_energia;
		int energia_atual;
    	int habilidade;
    	int resistencia;
    	int magia;
    	int sorte;
		int moedas_de_ouro;
		Armadura* armadura;
		Arma* arma;
		vector<Provisao*> provisoes;
		vector<ReliquiaMagica*> reliquias_magicas;
};

#endif // PERSONAGEM_H
