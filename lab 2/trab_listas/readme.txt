Olá, nesse arquivo descrevo como realizei o trabalho 
e o que foi feito do enunciado do trabalho.

Utilizei classes pra cada tipo de cadastro do programa, em cada classe tem a possibilidade de adicionar, remover ou pesquisar o cadastro.
Além disso todas as listas encadeadas tem uma função para apagar elas para evitar vazamento de memória e utilização desnecessária de memória.
Classe jogador:
Contém além das funções obrigatórias, funções para relatório por jogador, classificação de artilharia.
Classe treinador:
Contém apenas as funções obrigatórias, pois não é preciso mais do que isso para essa lista.
Classe time:
Contém além das funções obrigatórias, funções para adicionar jogadores ao time (no maximo 25 jogadores), adicionar treinador, gerar relatorio por time,
gerar classificação geral de todos os times do campeonato.
Classe partida:
Contém além das funções obrigatórias. Para narrar a partida é utilzada uma função a parte, onde a pessoa informa lance, minuto, jogador e time, podendo 
narrar varios lances numa partida.
Classe rodada:
Contém função para cadastrar rodadas a partir das partidas lançadas, essa classe so contém isso pois nao foi solicitado nehuma ação com ela.

Fiz uma interface no terminal, isso acabou necessitando de muitas linhas de código (dobrou o numero de linhas), porém é possivel fazer todo o controle de um
campeonato de futebol.

Diante dessas informações, percebemos que realizei todos pontos que foram pedidos no enunciado
do trabalho.
O trabalho foi feito em linux.
Para compilar o programa deve ser utilizado o seguinte código:
g++ list.cpp -o list && ./list