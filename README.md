# Documentação do Projeto POO

Este projeto implementa um sistema de personagem com itens, equipamentos e armaduras, utilizando conceitos de Programação Orientada a Objetos.

## Classes

### Item

Classe base que representa itens genéricos no jogo.

#### Atributos:
- `nome`: Nome do item
- `descricao`: Descrição detalhada do item
- `magia_minima_necessaria`: Nível mínimo de magia que o jogador precisa para usar o item

#### Métodos:
- Getters e setters para todos os atributos
- Construtor padrão e destrutor virtual

### Provisao

Subclasse de Item que representa itens consumíveis no jogo.

#### Atributos:
- Herda todos os atributos da classe Item
- `bonus_energia`: Quantidade de energia que a provisão recupera quando consumida

#### Métodos:
- Getters e setters para o atributo específico
- Construtor que inicializa nome, descrição, magia mínima necessária e bônus de energia

### Equipamento

Classe base que representa itens de equipamento genéricos no jogo.

#### Atributos:
- `nome`: Nome do equipamento
- `descricao`: Descrição detalhada do equipamento
- `habilidade_minima_necessaria`: Nível mínimo de habilidade que o jogador precisa para usar o equipamento
- `resistencia_minima_necessaria`: Nível mínimo de resistência que o jogador precisa para usar o equipamento

#### Métodos:
- Getters e setters para todos os atributos
- Construtor padrão e destrutor virtual

### Arma

Subclasse de Equipamento que representa especificamente as armas no jogo.

#### Atributos:
- Herda todos os atributos da classe Equipamento
- `buff_habilidade`: Bônus de habilidade que a arma proporciona ao jogador

#### Métodos:
- Getters e setters para o atributo específico
- Construtor que inicializa nome, descrição, habilidade mínima, resistência mínima, e buff de habilidade
- `evoluirArma`: Permite melhorar o buff de habilidade da arma

### Armadura

Subclasse de Equipamento que representa especificamente as armaduras no jogo.

#### Atributos:
- Herda todos os atributos da classe Equipamento
- `buff_resistencia`: Bônus de resistência que a armadura proporciona ao jogador

#### Métodos:
- Getters e setters para o atributo específico
- Construtor que inicializa nome, descrição, requisitos mínimos e buff de resistência
- `evoluirArmadura`: Permite melhorar o buff de resistência da armadura

### Player

Classe que representa o personagem jogável.

#### Atributos:
- `energia`: Pontos de vida do personagem
- `habilidade`: Nível de habilidade e dano do personagem
- `resistencia`: Capacidade de resistir a danos
- `magia`: Poder mágico do personagem
- `sorte`: Influencia eventos aleatórios a favor do personagem
- `moedas_de_ouro`: Moeda do jogo
- `armadura`: Referência para a armadura equipada pelo jogador
- `arma`: Referência para a arma equipada pelo jogador
- `provisoes`: vetor que referencia os itens equipados pelo jogador

#### Métodos:
- Getters e setters para todos os atributos
- Construtor que inicializa os atributos base do personagem
- `equiparArmadura`: Permite equipar uma armadura ao personagem
- `getArmadura`: Retorna a armadura atualmente equipada
- `equiparArma`: Permite equipar uma arma ao personagem
- `getArma`: Retorna a armadura atualmente equipada
- `adicionarProvisao`: Adiciona a provisão ao inventário do jogador
- `removerProvisao`: Remove a provisão do inventário do jogador
- `getProvisoes`: Retorna todas as provisões que estão no inventário do jogador