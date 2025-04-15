#include "../include/ReliquiaMagica.h"

using namespace std;

ReliquiaMagica::ReliquiaMagica(string n, string d, int m) : Item() {
	setNome(n);
	setDescricao(d);
	setMagiaMinimaNecessaria(m);
	buff_energia = 0;
	buff_habilidade = 0;
	buff_resistencia = 0;
	buff_magia = 0;
	buff_sorte = 0;
}

ReliquiaMagica::~ReliquiaMagica() {
	// dtor
}

void ReliquiaMagica::setBuffEnergia(int e) {
	buff_energia = e;
}

int ReliquiaMagica::getBuffEnergia() {
	return buff_energia;
}

void ReliquiaMagica::setBuffHabilidade(int h) {
	buff_habilidade = h;
}

int ReliquiaMagica::getBuffHabilidade() {
	return buff_habilidade;
}

void ReliquiaMagica::setBuffResistencia(int r) {
	buff_resistencia = r;
}

int ReliquiaMagica::getBuffResistencia() {
	return buff_resistencia;
}

void ReliquiaMagica::setBuffMagia(int m) {
	buff_magia = m;
}

int ReliquiaMagica::getBuffMagia() {
	return buff_magia;
}

void ReliquiaMagica::setBuffSorte(int s) {
	buff_sorte = s;
}

int ReliquiaMagica::getBuffSorte() {
	return buff_sorte;
}

void ReliquiaMagica::exibir_buffs() {
	cout << "Buff Energia: " << buff_energia << endl;
	cout << "Buff Habilidade: " << buff_habilidade << endl;
	cout << "Buff Resistencia: " << buff_resistencia << endl;
	cout << "Buff Magia: " << buff_magia << endl;
	cout << "Buff Sorte: " << buff_sorte << endl;
}