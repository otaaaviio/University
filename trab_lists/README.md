## Estrutura do Projeto

O projeto está organizado da seguinte forma:

```
/home/ota/projects/University/trab_lists/
├── src/
│   ├── jogador.cpp
│   ├── treinador.cpp
│   ├── time.cpp
│   ├── partida.cpp
│   ├── rodada.cpp
│   └── main.cpp
├── include/
│   ├── jogador.h
│   ├── treinador.h
│   ├── time.h
│   ├── partida.h
│   └── rodada.h
└── README.md
```

## Dependências

Para compilar e executar o projeto, você precisará do seguinte:

- g++ (GCC) 7.5.0 ou superior
- Sistema operacional Linux

## Compilação e Execução

Para compilar o programa, navegue até o diretório raiz e execute o seguinte comando:

```sh
g++ src/*.cpp -o list && ./list
```

## Descrição das Classes

Utilizei classes para cada tipo de cadastro do programa. Em cada classe, há a possibilidade de adicionar, remover ou pesquisar o cadastro. Além disso, todas as listas encadeadas têm uma função para apagá-las, evitando vazamento de memória e utilização desnecessária de memória.

### Classe Jogador

Contém, além das funções obrigatórias, funções para relatório por jogador e classificação de artilharia.

### Classe Treinador

Contém apenas as funções obrigatórias, pois não é preciso mais do que isso para essa lista.

### Classe Time

Contém, além das funções obrigatórias, funções para adicionar jogadores ao time (no máximo 25 jogadores), adicionar treinador, gerar relatório por time e gerar classificação geral de todos os times do campeonato.

### Classe Partida

Contém, além das funções obrigatórias, uma função à parte para narrar a partida, onde a pessoa informa lance, minuto, jogador e time, podendo narrar vários lances numa partida.

### Classe Rodada

Contém função para cadastrar rodadas a partir das partidas lançadas. Essa classe só contém isso, pois não foi solicitada nenhuma ação adicional com ela.

## Interface

Fiz uma interface no terminal, o que acabou necessitando de muitas linhas de código (dobrou o número de linhas), porém é possível fazer todo o controle de um campeonato de futebol.

Diante dessas informações, percebemos que realizei todos os pontos que foram pedidos no enunciado do trabalho. O trabalho foi feito em Linux.

Para compilar o programa, deve ser utilizado o seguinte código:

```sh
g++ list.cpp -o list && ./list
```