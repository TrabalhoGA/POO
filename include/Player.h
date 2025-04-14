#ifndef PLAYER_H
#define PLAYER_H

#include "Armadura.h"
#include "Arma.h"
#include "Provisao.h"

#include <vector>

using namespace std;

class Player
{
    public:
		Player(int e, int h, int r, int m, int s);
        virtual ~Player();

		void setEnergia(int e);
		int getEnergia();

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

    protected:

    private:
        int energia;
        int habilidade;
        int resistencia;
        int magia;
        int sorte;
        int moedas_de_ouro;
		Armadura* armadura;
		Arma* arma;
		vector<Provisao*> provisoes;
};

#endif // PLAYER_H
