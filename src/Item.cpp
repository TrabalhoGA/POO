#include "../include/Item.h"

using namespace std;

Item::Item() {
	// ctor
}

Item::~Item() {
	// dtor
}

void Item::setNome(string n) {
	nome = n;
}

string Item::getNome() {
	return nome;
}

void Item::setDescricao(string d) {
	descricao = d;
}

string Item::getDescricao() {
	return descricao;
}

void Item::setMagiaMinimaNecessaria(int m) {
	magia_minima_necessaria = m;
}

int Item::getMagiaMinimaNecessaria() {
	return magia_minima_necessaria;
}