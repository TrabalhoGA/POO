#include "../include/Personagem.h"
#include "../include/Armadura.h"
#include "../include/Arma.h"
#include "../include/Provisao.h"
#include "../include/ReliquiaMagica.h"
#include "../include/Monstro.h"

using namespace std;

int main() {
	// Teste
	// Criacao de um jogador
	Personagem jogador(100, 50, 30, 20, 10);
	cout << "Jogador:" << endl;
	cout << "Energia: " << jogador.getEnergiaAtual() << endl;
	cout << "Habilidade: " << jogador.getHabilidade() << endl;
	cout << "Resistencia: " << jogador.getResistencia() << endl;
	cout << "Magia: " << jogador.getMagia() << endl;
	cout << "Sorte: " << jogador.getSorte() << endl;


	// Criacao de uma armadura
	Armadura armadura("Armadura de Ferro", "Uma armadura resistente", 10, 20, 5);
	jogador.equiparArmadura(&armadura);
	cout << "\nArmadura equipada:" << endl;
	cout << "Nome: " << jogador.getArmadura()->getNome() << endl;
	cout << "Descricao: " << jogador.getArmadura()->getDescricao() << endl;
	cout << "Buff Resistencia: " << jogador.getArmadura()->getBuffResistencia() << endl;


	// Criacao de uma arma
	Arma arma("Espada Longa", "Uma espada afiada", 15, 25, 10);
	jogador.equiparArma(&arma);
	cout << "\nArma equipada:" << endl;
	cout << "Nome: " << jogador.getArma()->getNome() << endl;
	cout << "Descricao: " << jogador.getArma()->getDescricao() << endl;
	cout << "Buff Habilidade: " << jogador.getArma()->getBuffHabilidade() << endl;


	// Criacao de uma Provisao
	Provisao provisao("Elixir de Cura", "Restaura 50 de energia", 0, 50);
	jogador.adicionarProvisao(&provisao);
	cout << "\nProvisao adicionada:" << endl;
	cout << "Nome: " << provisao.getNome() << endl;
	cout << "Descricao: " << provisao.getDescricao() << endl;
	provisao.exibir_atributos();
	jogador.removerProvisao(&provisao);
	cout << "\nProvisao removida." << endl;
	cout << "Provisoes: " << jogador.getProvisoes().size() << endl;

	// Criacao de uma Reliquia Magica
	ReliquiaMagica reliquia("Amuleto da Sorte", "Um amuleto que traz sorte", 5);
	reliquia.setBuffSorte(10);
	jogador.adicionarReliquiaMagica(&reliquia);
	cout << "\nReliquia Magica adicionada:" << endl;
	cout << "Nome: " << jogador.getReliquiasMagicas()[0]->getNome() << endl;
	cout << "Descricao: " << jogador.getReliquiasMagicas()[0]->getDescricao() << endl;
	cout << "Buffs: " << endl;
	jogador.getReliquiasMagicas()[0]->exibir_atributos();
	jogador.removerReliquiaMagica(&reliquia);
	cout << "\nReliquia Magica removida." << endl;
	cout << "Reliquias Magicas: " << jogador.getReliquiasMagicas().size() << endl;

	// Criacao de um monstro
	Monstro rato("Rato Gigante", 30, 10, 5);
	cout << "\nMonstro:" << endl;
	cout << "Nome: " << rato.getNome() << endl;
	cout << "Energia: " << rato.getEnergia() << endl;
	cout << "Habilidade: " << rato.getHabilidade() << endl;
	cout << "Resistencia: " << rato.getResistencia() << endl;

	return 0;
}