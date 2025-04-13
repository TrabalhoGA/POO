#include "../include/Player.h"

using namespace std;

Player::Player(int e, int h, int r, int m, int s) : energia(e), habilidade(h), resistencia(r), magia(m), sorte(s), moedas_de_ouro(0), armadura(nullptr)
{
	//ctor
}

Player::~Player()
{
    //dtor
}

void Player::setEnergia(int e)
{
	energia = e;
}

int Player::getEnergia()
{
	return energia;
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