#include "../include/Player.h"
#include "../include/Armadura.h"

using namespace std;

int main() {
	// Teste
	// Criacao de um jogador
	Player jogador(100, 50, 30, 20, 10);
	// Criacao de uma armadura
	Armadura armadura("Armadura de Ferro", "Uma armadura resistente", 10, 20, 5);
	// Equipar a armadura no jogador
	jogador.equiparArmadura(&armadura);
	// Exibir informacoes do jogador e da armadura equipada
	cout << "Jogador:" << endl;
	cout << "Energia: " << jogador.getEnergia() << endl;
	cout << "Habilidade: " << jogador.getHabilidade() << endl;
	cout << "Resistencia: " << jogador.getResistencia() << endl;
	cout << "Magia: " << jogador.getMagia() << endl;
	cout << "Sorte: " << jogador.getSorte() << endl;
	if (jogador.getArmadura()) {
		cout << "\nArmadura equipada:" << endl;
		cout << "Nome: " << jogador.getArmadura()->getNome() << endl;
		cout << "Descricao: " << jogador.getArmadura()->getDescricao() << endl;
		cout << "Buff Resistencia: " << jogador.getArmadura()->getBuffResistencia() << endl;
	}
	else {
		cout << "\nNenhuma armadura equipada." << endl;
	}

	return 0;
}