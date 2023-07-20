// t3 lab 1

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

void corl(int r, int g, int b){
  printf("\e[38;2;%d;%d;%dm", r, g, b);
}

void corf(int r, int g, int b){
  printf("\e[48;2;%d;%d;%dm", r, g, b);
}

void corn(void){
  printf("\e[m");
}

void pos(int lin, int col){
  printf("\e[%d;%dH", lin, col);
}

void limpa(void){
  printf("\e[2J");
}

void att_ranking(int melhoresResultados[3], int pontuacaoAtual){
  for (int i = 0; i < 3; i++) {
        if (pontuacaoAtual > melhoresResultados[i]) {
            for (int j = 2; j > i; j--) {
                melhoresResultados[j] = melhoresResultados[j-1];
            }
            melhoresResultados[i] = pontuacaoAtual;
            break;
        }
    }
}

void cor_escolhida(int c1, int c2, int c3){
  corf(c1, c2, c3);
  for(int l = 0; l < 8; l++)
    for(int c = 23; c < 18+23; c++){
      pos(l, c);
      printf(" ");
    }
    printf("\n");
}

int calculaDist(int r, int g, int b, int c1, int c2, int c3) {
  int dR = r - c1;
  int dG = g - c2;
  int dB = b - c3;
  return sqrt((dR * dR) + (dG * dG) + (dB * dB));
}

int pontuacao(int c1, int c2, int c3, int r, int g, int b, int melhoresResultados[3], int i){
  int a, k, c;

  if(r>=128) a = 0;
  else a = 255;
  if(g>=128) k = 0;
  else k = 255;
  if(b>=128) c = 0;
  else c = 255;

  float distancia = calculaDist(r, g, b, c1, c2, c3);
  float maxDistancia = calculaDist(r, g, b, a, k, c);
  
  int pont = (1 - (distancia / maxDistancia)) * 100;
  pos(0, 45);
  corn();
  printf("Pontuação da tentativa %d de 5: %d/100", i+1, pont);
  att_ranking(melhoresResultados, pont);
  char enter;
  scanf("%c", &enter);
  scanf("%c", &enter);
}

int pega_cores(int r, int g, int b, int melhoresResultados[3], int i){
  int c1, c2, c3;
  corn();
  printf("\nDigite um numero para a cor vermelho: ");
  scanf("%d", &c1);
  for(int i=0; i<255; i+=2){
    if(i == c1 || i + 1 == c1){
      corn();
      printf(" ");
    } else {
      corf(i, 0, 0);
      printf(" ");
    }
  }
  corn();
  printf("\nDigite um numero para a cor verde: ");
  scanf("%d", &c2);
  for(int i=0; i<255; i+=2){
    if(i == c2 || i + 1 == c2){
      corn();
      printf(" ");
    } else {
      corf(0, i, 0);
      printf(" ");
    }
  }
  corn();
  printf("\nDigite um numero para a cor azul: ");
  scanf("%d", &c3);
  for(int i=0; i<255; i+=2){
    if(i == c3 || i + 1 == c3){
      corn();
      printf(" ");
    } else {
      corf(0, 0, i);
      printf(" ");
    }
  }
  corn();
  cor_escolhida(c1, c2, c3);
  pontuacao(c1, c2, c3, r, g, b, melhoresResultados, i);
}

void cor_inicial(int r, int g, int b){
  corf(r, g, b);
  for(int l = 0; l < 8; l++)
    for(int c = 0; c < 18; c++){
      pos(l, c);
      printf(" ");
    }
}

int jogarNovamente() {
    char resposta;
    
    pos(15, 0);
    printf("Deseja jogar novamente? (S/N): ");
    scanf(" %c", &resposta);
    
    if (resposta == 'S' || resposta == 's') 
      return 1;
    else 
      return 0;
}

void exibirTabelaRanking(int resultados[3]) {
  limpa();
  pos(0,0);
  printf("   Tabela de Ranking:\n");
  printf("-----------------------\n");
  printf("| Posição | Pontuação |\n");
  printf("-----------------------\n");
  for (int i = 0; i < 3; i++) {
    printf("|   %dº    |   %d/100  |\n", i+1, resultados[i]);
  }
  pos(8, 0);
}




int main()
{
  int jogar = 1;
  int melhoresResultados[3] = {0};
  int jogafora[3] = {0};

  while(jogar){
    srand(time(0));
    int r = rand() % 256, g = rand() % 256, b = rand() % 256;
    for(int i=0; i<5; i++){
      if(i == 4){
        limpa();
        cor_inicial(r, g, b);
        pega_cores(r, g, b, melhoresResultados, i);
      }
      else{
        limpa();
        cor_inicial(r, g, b);
        pega_cores(r, g, b, jogafora, i);
      }
    }

    jogar = jogarNovamente();
  }

  if(!jogar)
    exibirTabelaRanking(melhoresResultados);
}