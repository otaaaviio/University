#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "tela.h"
#include <stdbool.h>
#include <string.h>
#include <unistd.h>


// gcc -Wall -o t4 t4.c tela.c -lm   

typedef struct{
  int tecla, barra, pont;
  char nome[100];
  cor cor_random, max_dist;
  posicao pos_r, pos_g, pos_b;
  double tempo, inicio;
  float distancia, distanciaMax, pont_final;
} est;

void definicao_inicial(est *jogo) // OK
{
  jogo->barra = 3;
  jogo->cor_random.vermelho = rand() % 256;
  jogo->cor_random.verde = rand() % 256;
  jogo->cor_random.azul = rand() % 256;
  jogo->pos_r.linha = 10;
  jogo->pos_r.coluna = 0;
  jogo->pos_g.linha = 11;
  jogo->pos_g.coluna = 0;
  jogo->pos_b.linha = 12;
  jogo->pos_b.coluna = 0;
  jogo->inicio = tela_relogio();
}

void pega_nome(est *jogo) {
  printf("\nVocê pode entrar no ranking!\nPara finalizar, digite seu nome (mínimo 3 letras): ");
  
  fgets(jogo->nome, sizeof(jogo->nome), stdin);
  
  int len = strlen(jogo->nome);
  
  if (len > 0 && jogo->nome[len - 1] == '\n') {
    jogo->nome[len - 1] = '\0';
    len--;
  }
  
  while (len < 3) {
    printf("Erro! Mínimo de 3 letras no nome.\n");
    printf("Digite seu nome novamente: ");
    
    fgets(jogo->nome, sizeof(jogo->nome), stdin);
    
    len = strlen(jogo->nome);
    
    if (len > 0 && jogo->nome[len - 1] == '\n') {
      jogo->nome[len - 1] = '\0';
      len--;
    }
  }
}

void ler_ranking(est (*ranking)[3]) {
  FILE* arquivo = fopen("ranking.txt", "r");
  if (arquivo != NULL) {
    for (int i = 0; i < 3; i++) {
      fscanf(arquivo, "%s %d", (*ranking)[i].nome, &(*ranking)[i].pont);
    }
    fclose(arquivo);
  }
}

void escrever_ranking(est ranking[3]) {
  FILE* arquivo = fopen("ranking.txt", "w");
  if (arquivo != NULL) {
    for (int i = 0; i < 3; i++) {
      fprintf(arquivo, "%s %d\n", ranking[i].nome, ranking[i].pont);
    }
    fclose(arquivo);
  }
}

void registra_entrada(est jogo, est ranking[]) {
  est novaEntrada;
  strncpy(novaEntrada.nome, jogo.nome, sizeof(novaEntrada.nome) - 1);
  novaEntrada.nome[sizeof(novaEntrada.nome) - 1] = '\0';
  novaEntrada.pont = jogo.pont_final;
  for (int i = 0; i < 3; i++) {
    if (novaEntrada.pont >= ranking[i].pont) {
      est temp = ranking[i];
      ranking[i] = novaEntrada;
      novaEntrada = temp;
    }
  }
  escrever_ranking(ranking);
}

int calcula_pontuacao(est jogo){ // OK
  int dR, dG, dB;
  int MaxR, MaxG, MaxB;
  // distancia real
  dR = jogo.cor_random.vermelho - jogo.pos_r.coluna;
  dG = jogo.cor_random.verde - jogo.pos_g.coluna;
  dB = jogo.cor_random.azul - jogo.pos_b.coluna;
  jogo.distancia = sqrt((dR * dR) + (dG * dG) + (dB * dB));
  //distancia maxima
  MaxR = jogo.cor_random.vermelho - jogo.max_dist.vermelho;
  MaxG = jogo.cor_random.verde - jogo.max_dist.verde;
  MaxB = jogo.cor_random.azul - jogo.max_dist.azul;
  jogo.distanciaMax = sqrt((MaxR * MaxR) + (MaxG * MaxG) + (MaxB * MaxB));

  float p = ((1 - (jogo.distancia / jogo.distanciaMax)) * 100);
  float adicional = p * (20.0 - jogo.tempo) * 5.0  / 100;

  if(p + adicional < 100) return (p + adicional);
  else return 100;
}

void define_dist_max(est* jogo){ // OK
  if (jogo->cor_random.vermelho >= 128)
    jogo->max_dist.vermelho = 0;
  else
    jogo->max_dist.vermelho = 255;

  if (jogo->cor_random.verde >= 128)
    jogo->max_dist.verde = 0;
  else
    jogo->max_dist.verde = 255;

  if (jogo->cor_random.azul >= 128)
    jogo->max_dist.azul = 0;
  else
    jogo->max_dist.azul = 255;

  
  jogo->pos_r.coluna *= 2;
  jogo->pos_g.coluna *= 2;
  jogo->pos_b.coluna *= 2;
}

void tabelaRanking(est ranking[]) { 
  tela_limpa();
  tela_cor_normal();
  tela_posiciona((posicao){0,0});
  printf("      Tabela de Ranking:     \n");
  printf("-----------------------------\n");
  printf("| posição | nome | pontuação \n");
  printf("-----------------------------\n");
  for (int i = 0; i < 3; i++) {
    printf("|   %dº    |   %d/100  |  %s\n", i+1, ranking[i].pont, ranking[i].nome);
  }
  tela_posiciona((posicao){15,0});
  tela_cor_normal();
}

void cor_quadrado(cor c, int num) // OK
{
  int col_i, col_f;
  switch (num)
  { // define o quadrado que será desenhado, o de cor aleatória ou o quadrado com a cor escolhida pelo usuario
  case 1:
    col_i = 0;
    col_f = 18;
    break;
  case 2:
    col_i = 25;
    col_f = 43;
    break;
  }
  tela_cor_fundo(c);
  for (int l = 0; l < 8; l++)
  {
    for (int c = col_i; c < col_f; c++)
    {
      tela_posiciona((posicao){l, c});
      printf(" ");
    }
  }
}

void imprime_barras(void) // OK
{
  tela_posiciona((posicao){10, 0});
  for (int aux = 1; aux <= 3; aux++)
  { // alterna entre as cores vermelho, verde, azul, respectivamente
    int a = 0, b = 0, c = 0;
    switch (aux)
    {
    case 1:
      a = 1;
      break;
    case 2:
      b = 1;
      break;
    case 3:
      c = 1;
      break;
    }
    for (int i = 0; i <= 255; i += 2)
    { // imprime a cor selecionada no switch
      tela_cor_fundo((cor){i * a, i * b, i * c});
      printf(" ");
    }
    printf("\n");
  }
  tela_cor_normal();
}

void move_vermelho(est *jogo) // OK
{
  if (jogo->barra == 3)
  {
    switch (jogo->tecla)
    {
    case c_left:
      if (jogo->pos_r.coluna > 1)
        jogo->pos_r.coluna--;
      break;
    case c_right:
      if (jogo->pos_r.coluna < 128)
        jogo->pos_r.coluna++;
      break;
    case c_down:
      jogo->barra--;
      break;
    }
  }
}

void move_verde(est *jogo) // OK
{
  if (jogo->barra == 2)
  {
    switch (jogo->tecla)
    {
    case c_left:
      if (jogo->pos_g.coluna > 1)
        jogo->pos_g.coluna--;
      break;
    case c_right:
      if (jogo->pos_g.coluna < 128)
        jogo->pos_g.coluna++;
      break;
    case c_down:
      jogo->barra--;
      break;
    case c_up:
      jogo->barra++;
      break;
    }
  }
}

void move_azul(est *jogo) // OK
{
  if (jogo->barra == 1)
  {
    switch (jogo->tecla)
    {
    case c_left:
      if (jogo->pos_b.coluna > 1)
        jogo->pos_b.coluna--;
      break;
    case c_right:
      if (jogo->pos_b.coluna < tela_ncol())
        jogo->pos_b.coluna++;
      break;
    case c_up:
      jogo->barra++;
      break;
    }
  }
}

void deseha_bolinhas(est jogo) { // OK
  tela_cor_normal();
  tela_cor_fundo((cor){255, 255, 255});
  tela_posiciona(jogo.pos_r);
  if (jogo.barra == 3) { putchar('#');
  }
  else { putchar(' ');
  }
  tela_posiciona(jogo.pos_g);
  if (jogo.barra == 2) { putchar('#');
  }
  else { putchar(' ');
  }
  tela_posiciona(jogo.pos_b);
  if (jogo.barra == 1) { putchar('#');
  }
  else { putchar(' ');
  }
}

void desenha_tela(est jogo) { // OK
  tela_cor_normal();
  tela_limpa();

  cor_quadrado(jogo.cor_random, 1);
  imprime_barras();

  tela_posiciona((posicao){60, 0});
  printf("Tempo: %.1f/20", jogo.tempo);

  deseha_bolinhas(jogo);
}

void desenha_tela_final(est jogo, bool ganhou, est ranking[]){ 
  tela_cor_normal();
  tela_limpa();
  cor selected = {jogo.pos_r.coluna, jogo.pos_g.coluna, jogo.pos_b.coluna};
  cor_quadrado(jogo.cor_random, 1);
  cor_quadrado(selected, 2);
  tela_cor_normal();
  printf("\n\nSua pontuação foi: %0.1f/100", jogo.pont_final);
  if (ganhou) {
    pega_nome(&jogo);
    registra_entrada(jogo, ranking);
  }
  else {
    printf("\nInfelizmente sua pontuação não foi suficiente para ser adicionada no ranking. Tente novamente!");
    sleep(4);
  }
  tabelaRanking(ranking);
}

int main()
{
  srand(time(0));
  tela_cria();
  tela_limpa();
  tela_mostra_cursor(false);

  est ranking[3];
  ler_ranking(&ranking);

  est jogo;
  definicao_inicial(&jogo);

  // jogador escolhe a cor
  do {
    jogo.tecla = tela_le_char();
    move_verde(&jogo);
    move_vermelho(&jogo);
    move_azul(&jogo);
    jogo.tempo = tela_relogio() - jogo.inicio;
    desenha_tela(jogo);
  } while ((jogo.tempo <= 20) && (jogo.tecla != c_enter));

  tela_destroi();
  //calcula a pontuaçao dele
  define_dist_max(&jogo);
  jogo.pont_final = calcula_pontuacao(jogo);
  
  //desenha a tela final e verifica se a pontuaçao é suficiente para entrar no ranking
  desenha_tela_final(jogo, jogo.pont_final > ranking[2].pont, ranking);

  sleep(3);
  tela_cor_normal();
}