# Documentação do Projeto POO

Este projeto implementa um sistema de personagem com itens, equipamentos e armaduras, utilizando conceitos de Programação Orientada a Objetos.

## Classes

### Item

Classe abstrata para os itens do jogo.

#### Atributos:
- `nome`: Nome do item
- `descricao`: Descrição detalhada do item
- `magia_minima_necessaria`: Nível mínimo de magia que o jogador precisa para usar o item

#### Métodos:
- Getters e setters para todos os atributos
- Construtor padrão e destrutor virtual
- `exibir_atributos`: Método virtual puro para forçar a implementação nas classes derivadas

### Provisao

Subclasse de Item que representa itens consumíveis no jogo.

#### Atributos:
- Herda todos os atributos da classe Item
- `bonus_energia`: Quantidade de energia que a provisão recupera quando consumida

#### Métodos:
- Getters e setters para o atributo específico
- Construtor que inicializa nome, descrição, magia mínima necessária e bônus de energia
- `exibir_atributos`: Exibe a quantidade de energia que a provisão recupera

### ReliquiaMagica

Subclasse de Item que representa relíquias mágicas especiais que concedem buffs aos atributos do jogador.

#### Atributos:
- Herda todos os atributos da classe Item
- `buff_energia`: Buff de energia que a relíquia proporciona ao jogador
- `buff_habilidade`: Buff de habilidade que a relíquia proporciona ao jogador
- `buff_resistencia`: Buff de resistência que a relíquia proporciona ao jogador
- `buff_magia`: Buff de magia que a relíquia proporciona ao jogador
- `buff_sorte`: Buff de sorte que a relíquia proporciona ao jogador

#### Métodos:
- Getters e setters para todos os atributos específicos
- Construtor que inicializa nome, descrição e magia mínima necessária
- `exibir_atributos`: Exibe todos os buffs que a relíquia proporciona

### Monstro

Classe que representa os inimigos do jogo.

#### Atributos:
- `nome`: Nome do monstro
- `energia`: Pontos de vida do monstro
- `habilidade`: Nível de habilidade de combate do monstro
- `resistencia`: Capacidade de resistir a danos

#### Métodos:
- Getters e setters para todos os atributos
- Construtor que inicializa nome, energia, habilidade e resistência
- Destrutor virtual

### Equipamento

Classe abstrata para os equipamentos do jogo.

#### Atributos:
- `nome`: Nome do equipamento
- `descricao`: Descrição detalhada do equipamento
- `habilidade_minima_necessaria`: Nível mínimo de habilidade que o jogador precisa para usar o equipamento
- `resistencia_minima_necessaria`: Nível mínimo de resistência que o jogador precisa para usar o equipamento

#### Métodos:
- Getters e setters para todos os atributos
- Construtor padrão e destrutor virtual
- `evoluir_equipamento`: Método virtual puro para forçar a implementação nas classes derivadas

### Arma

Subclasse de Equipamento que representa especificamente as armas no jogo.

#### Atributos:
- Herda todos os atributos da classe Equipamento
- `buff_habilidade`: Buff de habilidade que a arma proporciona ao jogador

#### Métodos:
- Getters e setters para o atributo específico
- Construtor que inicializa nome, descrição, habilidade mínima, resistência mínima, e buff de habilidade
- `evoluir_equipamento`: Permite melhorar o buff de habilidade da arma

### Armadura

Subclasse de Equipamento que representa especificamente as armaduras no jogo.

#### Atributos:
- Herda todos os atributos da classe Equipamento
- `buff_resistencia`: Buff de resistência que a armadura proporciona ao jogador

#### Métodos:
- Getters e setters para o atributo específico
- Construtor que inicializa nome, descrição, requisitos mínimos e buff de resistência
- `evoluir_equipamento`: Permite melhorar o buff de resistência da armadura

### Personagem

Classe que representa o personagem jogável.

#### Atributos:
- `max_energia`: Energia máxima do personagem
- `energia_atual`: Energia atual do personagem
- `habilidade`: Nível de habilidade e dano do personagem
- `resistencia`: Capacidade de resistir a danos
- `magia`: Poder mágico do personagem
- `sorte`: Influencia eventos aleatórios a favor do personagem
- `moedas_de_ouro`: Moeda do jogo
- `armadura`: Referência para a armadura equipada pelo jogador
- `arma`: Referência para a arma equipada pelo jogador
- `provisoes`: Vetor que referencia as provisões no inventário do jogador
- `reliquias_magicas`: Vetor que referencia as relíquias mágicas do jogador

#### Métodos:
- Getters e setters para todos os atributos
- Construtor que inicializa os atributos base do personagem
- `equiparArmadura`: Permite equipar uma armadura ao personagem
- `getArmadura`: Retorna a armadura atualmente equipada
- `equiparArma`: Permite equipar uma arma ao personagem
- `getArma`: Retorna a arma atualmente equipada
- `adicionarProvisao`: Adiciona a provisão ao inventário do jogador
- `removerProvisao`: Remove a provisão do inventário do jogador
- `getProvisoes`: Retorna todas as provisões que estão no inventário do jogador
- `adicionarReliquiaMagica`: Adiciona uma relíquia mágica ao jogador
- `removerReliquiaMagica`: Remove uma relíquia mágica do jogador
- `getReliquiasMagicas`: Retorna todas as relíquias mágicas do jogador