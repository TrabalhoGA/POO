#include "../include/Jogo.h"
#include "../include/TelaInventario.h"
#include "../include/Personagem.h"
#include "../include/ArquivoManager.h"

using namespace std;

// Inicialização da variável estática
Jogo* Jogo::instance = nullptr;

// Implementação do método getInstance com Lazy Initialization
Jogo* Jogo::getInstance() {
    if (instance == nullptr) {
        instance = new Jogo();
    }
    return instance;
}

// Método para liberar a instância
void Jogo::releaseInstance(){
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
    }
}

// Método para resetar a instância
void Jogo::resetInstance(){
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
    }
}

Jogo::Jogo() : estadoAtual(nullptr), sair(false) {
    // Construtor
}

Jogo::~Jogo() {
    delete estadoAtual;
}

void Jogo::exibirTela() {
    if (estadoAtual) {
        estadoAtual->exibirTela();
    }
}

void Jogo::handleInput(int input) {
    if (estadoAtual) {
        estadoAtual->handleInput(input);
    }
}

void Jogo::mudarEstado(TelaEstado* novoEstado) {
    if (estadoAtual) {
        delete estadoAtual; // Libera a memória do estado atual
    }
    estadoAtual = novoEstado; // Define o novo estado
}

void Jogo::setNomeSave(const string& nome) {
    nomeSave = nome;
}

string Jogo::getNomeSave() const {
    return nomeSave;
}

void Jogo::setDiretorioAtual(const string& diretorio) {
    diretorioAtual = diretorio;
}

string Jogo::getDiretorioAtual() const {
    return diretorioAtual;
}

void Jogo::setFaseAtual(int fase){
    faseAtual = fase;
}

int Jogo::getFaseAtual() const {
    return faseAtual;
}

void Jogo::avancarFase(int incremento) {
    setFaseAtual(faseAtual + incremento);
}

TelaEstado* Jogo::getEstadoAtual() const {
    return estadoAtual;
}

void Jogo::limparTela() {
#ifdef _WIN32
    system("cls");  // Windows
#else
    system("clear");  // Linux / macOS
#endif
}

void Jogo::salvarJogo() {
	// Instanciar o personagem
    Personagem* p = Personagem::getInstance();

	// Obter o diretório atual e a fase atual
    string diretorioFase = diretorioAtual + ":" + to_string(faseAtual);

	// Obter os atributos do personagem
    string personagemAtributos = to_string(p->getMaxEnergia()) + "," +
        to_string(p->getEnergiaAtual()) + "," +
        to_string(p->getHabilidade()) + "," +
        to_string(p->getResistencia()) + "," +
        to_string(p->getMagia()) + "," +
        to_string(p->getSorte()) + "," +
        to_string(p->getMoedasDeOuro());

	// Obter a armadura do personagem
    string armadura = "Nenhuma";
    if (p->getArmadura() != nullptr) {
        armadura = p->getArmadura()->getNome() + "," +
            p->getArmadura()->getDescricao() + "," +
            to_string(p->getArmadura()->getHabilidadeMinimaNecessaria()) + "," +
            to_string(p->getArmadura()->getResistenciaMinimaNecessaria()) + "," +
            to_string(p->getArmadura()->getBuffResistencia());
    }

	// Obter a arma do personagem
    string arma = "Nenhuma";
    if (p->getArma() != nullptr) {
        arma = p->getArma()->getNome() + "," +
            p->getArma()->getDescricao() + "," +
            to_string(p->getArma()->getHabilidadeMinimaNecessaria()) + "," +
            to_string(p->getArma()->getResistenciaMinimaNecessaria()) + "," +
            to_string(p->getArma()->getBuffHabilidade());
    }

	// Obter as provisões do personagem
    string provisoes;
    if (!p->getProvisoes().empty()) {
        for (size_t i = 0; i < p->getProvisoes().size(); i++) { 
            Provisao* provisao = p->getProvisoes().at(i); 
            provisoes += provisao->getNome() + "," +
                        provisao->getDescricao() + "," +
                        to_string(provisao->getMagiaMinimaNecessaria()) + "," +
                        to_string(provisao->getBonusEnergia()) + ";";
        }
    }
	else {
		provisoes = "Nenhuma";
	}

	// Obter as relíquias mágicas do personagem
    string reliquias;
    if (!p->getReliquiasMagicas().empty()) {
	    for (size_t i = 0; i < p->getReliquiasMagicas().size(); i++) {
		    ReliquiaMagica* reliquia = p->getReliquiasMagicas().at(i);
		    reliquias += reliquia->getNome() + "," +
			    reliquia->getDescricao() + "," +
			    to_string(reliquia->getMagiaMinimaNecessaria()) + "," +
			    to_string(reliquia->getBuffEnergia()) + "," +
                to_string(reliquia->getBuffHabilidade()) + "," +
                to_string(reliquia->getBuffResistencia()) + "," +
                to_string(reliquia->getBuffMagia()) + "," +
                to_string(reliquia->getBuffSorte()) + ";";
	    }
    }
    else {
		reliquias = "Nenhuma";
	}

	// Juntar todas as informações em uma string
	string dadosSalvar = diretorioFase + "\n" +
		personagemAtributos + "\n" +
        armadura + "\n" +
		arma + "\n" +
		provisoes + "\n" +
		reliquias;

	// Salvar os dados no arquivo
	ArquivoManager::getInstance()->escreverArquivo(getNomeSave(), dadosSalvar);
}

void Jogo::excluirSave() {
    remove(getNomeSave().c_str());
}

bool Jogo::sairJogo() {
    return sair;
}

void Jogo::setSairJogo(bool s) {
    sair = s;
}