#include "../include/Player.h"

using namespace std;

Player::Player(int e, int h, int r, int m, int s) : max_energia(e), energia_atual(e), habilidade(h), resistencia(r), magia(m), sorte(s), moedas_de_ouro(0), armadura(nullptr), arma(nullptr)
{
	//ctor
}

Player::~Player()
{
    //dtor
}

void Player::setMaxEnergia(int e)
{
	max_energia = e;
}

int Player::getMaxEnergia()
{
	return max_energia;
}

void Player::setEnergiaAtual(int e)
{
	energia_atual = e;
}

int Player::getEnergiaAtual()
{
	return energia_atual;
}

void Player::setHabilidade(int h)
{
	habilidade = h;
}

int Player::getHabilidade()
{
	return habilidade;
}

void Player::setResistencia(int r)
{
	resistencia = r;
}

int Player::getResistencia()
{
	return resistencia;
}
void Player::setMagia(int m)
{
	magia = m;
}

int Player::getMagia()
{
	return magia;
}

void Player::setSorte(int s)
{
	sorte = s;
}

int Player::getSorte()
{
	return sorte;
}

void Player::setMoedasDeOuro(int m)
{
	moedas_de_ouro = m;
}

int Player::getMoedasDeOuro()
{
	return moedas_de_ouro;
}

void Player::equiparArmadura(Armadura* armadura)
{
	this->armadura = armadura;
}

Armadura* Player::getArmadura()
{
	return armadura;
}

void Player::equiparArma(Arma* arma)
{
	this->arma = arma;
}

Arma* Player::getArma()
{
	return arma;
}

void Player::adicionarProvisao(Provisao* provisao)
{
	provisoes.push_back(provisao);
}

void Player::removerProvisao(Provisao* provisao)
{
	auto it = find(provisoes.begin(), provisoes.end(), provisao);
	if (it != provisoes.end()) {
		provisoes.erase(it);
	}
}

vector<Provisao*> Player::getProvisoes()
{
	return provisoes;
}

void Player::adicionarReliquiaMagica(ReliquiaMagica* reliquia)
{
	reliquias_magicas.push_back(reliquia);
}

void Player::removerReliquiaMagica(ReliquiaMagica* reliquia)
{
	auto it = find(reliquias_magicas.begin(), reliquias_magicas.end(), reliquia);
	if (it != reliquias_magicas.end()) {
		reliquias_magicas.erase(it);
	}
}

vector<ReliquiaMagica*> Player::getReliquiasMagicas()
{
	return reliquias_magicas;
}