#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

// codigo para compilar
// gcc efe.c -o efe -lallegro -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_image  && ./efe



#define TAM 5

typedef struct {
    int pont;
    char nome[10];
} est;

est player;
bool jogar_novamente;
char tabuleiro[TAM][TAM], tabuleiro_aux[TAM][TAM];
ALLEGRO_EVENT_QUEUE *queue;
ALLEGRO_DISPLAY *disp;
ALLEGRO_FONT *font;
ALLEGRO_FONT *font_info;
ALLEGRO_BITMAP *imgHappy;
ALLEGRO_BITMAP *imgSad;
bool display_close;

void inicializarAllegro(){
    al_init();
    disp = al_create_display(800, 600);
    queue = al_create_event_queue();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_init_image_addon();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    font = al_load_font("rainyhearts.ttf", 50, 0);
    font_info = al_load_font("rainyhearts.ttf", 24, 0);
    imgSad = al_load_bitmap("imgSad.jpg");
    imgHappy = al_load_bitmap("imgHappy.jpg");
    display_close = false;
}

void finalizarAllegro(){
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_event_queue(queue);
}

void ler_ranking(est ranking[TAM]){ //le o ranking global
    FILE *arquivo = fopen("ranking.txt", "r");
    if (arquivo != NULL){
        for (int i = 0; i < 5; i++){
            fscanf(arquivo, "%s %d", ranking[i].nome, &ranking[i].pont);
        }
        fclose(arquivo);
    }
    else{
        arquivo = fopen("ranking.txt", "w");
        if (arquivo != NULL){
            for (int i = 0; i < 5; i++){
                strcpy(ranking[i].nome, "n/a");
                ranking[i].pont = 0;
                fprintf(arquivo, "%s %d\n", ranking[i].nome, ranking[i].pont);
            }
            fclose(arquivo);
        }
        else{
            printf("Erro ao criar o arquivo.\n");
            exit(1);
        }
    }
}

void escrever_ranking(est ranking[TAM]){ //atualiza o ranking global
    FILE *arquivo = fopen("ranking.txt", "w");
    if (arquivo != NULL){
        for (int i = 0; i < 5; i++){
            fprintf(arquivo, "%s %d\n", ranking[i].nome, ranking[i].pont);
        }
        fclose(arquivo);
    }
}

void registra_entrada(est ranking[TAM]){ //registra nova entrada caso pontuacao for maior que alguma do ranking global
    est novaEntrada;
    strncpy(novaEntrada.nome, player.nome, sizeof(novaEntrada.nome) - 1);
    novaEntrada.nome[sizeof(novaEntrada.nome) - 1] = '\0';
    novaEntrada.pont = player.pont;
    for (int i = 0; i < 5; i++){
        if (player.pont >= ranking[i].pont){
            est temp = ranking[i];
            ranking[i] = novaEntrada;
            novaEntrada = temp;
        }
    }
    escrever_ranking(ranking);
}

bool tabuleiro_cheio(){ //verifica se o tabuleiro ta cheio
    int celulas_preenchidas = 0;
    for (int i = 0; i < TAM; i++)
    {
        for (int j = 0; j < TAM; j++)
        {
            if (tabuleiro[i][j] != '\0')
            {
                celulas_preenchidas++;
            }
        }
    }
    if (celulas_preenchidas != TAM * TAM)
        return false;
    else{
        return true;
    }
}

void poe_letra(int n, char tabuleiro[][TAM]){ //poe nova letra no tabuleiro
    int i, j;
    if (!tabuleiro_cheio()){
        do
        {
            i = rand() % 5;
            j = rand() % 5;
        } while (tabuleiro[i][j] != '\0');
    
    if (n == 0)
    {
        tabuleiro[i][j] = 'B';
    }
    else if (n == 1 || n == 2 || n == 3)
    {
        tabuleiro[i][j] = 'A';
    }
    }
}

void cor_letra(char letra, int *r, int *g, int *b){ //define a cor da casa do tabuleiro a ser desenhada
    switch (letra){
    case 'A':
        *r = 245; *g = 248; *b = 167;
        break;
    case 'B':
        *r = 240; *g = 244; *b = 123;
        break;
    case 'C':
        *r = 235; *g = 241; *b = 78;
        break;
    case 'D':
        *r = 231; *g = 238; *b = 35;
        break;
    case 'E':
        *r = 184; *g = 190; *b = 28;
        break;
    case 'F':
        *r = 115; *g = 119; *b = 17;
        break;
    default:
        *r = 192; *g = 158; *b = 222;
        break;
    }
}

int pontuacao(char tabuleiro[][TAM]){ //calcula pontuacao atual do tabuleiro
    int pontuacao = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            switch (tabuleiro[i][j]) {
            case 'A':
                pontuacao += 10;
                break;
            case 'B':
                pontuacao += 30;
                break;
            case 'C':
                pontuacao += 90;
                break;
            case 'D':
                pontuacao += 270;
                break;
            case 'E':
                pontuacao += 810;
                break;
            case 'F':
                pontuacao += 2430;
                break;
            }
        }
    }
    return pontuacao;
}

void desenharTabuleiro(est ranking[TAM]){
    player.pont = pontuacao(tabuleiro);
    al_clear_to_color(al_map_rgb(217, 196, 235));
    for (int i = 0; i < TAM; i++){
        for (int j = 0; j < TAM; j++){
            int x = 150 + j * 100;
            int y = 50 + i * 100;
            char letra = tabuleiro[i][j];
            int r, g, b;
            cor_letra(letra, &r, &g, &b);
            al_draw_rectangle(x, y, x + 100, y + 100, al_map_rgb(115, 94, 133), 10);
            al_draw_filled_rectangle(x + 5, y + 5, x + 95, y + 95, al_map_rgb(r, g, b));

            al_draw_textf(font, al_map_rgb(0, 0, 0), x + 50, y + 28, ALLEGRO_ALIGN_CENTER, "%c", letra);
        }
    }
    if (player.pont > ranking[0].pont){
        al_draw_textf(font_info, al_map_rgb(0, 0, 0), 400, 10, ALLEGRO_ALIGN_CENTER, "Pontuação: %d Recorde: %d", player.pont, player.pont);
    }
    else{
        al_draw_textf(font_info, al_map_rgb(0, 0, 0), 400, 10, ALLEGRO_ALIGN_CENTER, "Pontuação: %d Recorde: %d", player.pont, ranking[0].pont);
    }

    al_flip_display();
}

char upa_cor(char letra){ //transforma 3 letras em 1 letra
    switch (letra){
    case 'A':
        return 'B';
        break;
    case 'B':
        return 'C';
        break;
    case 'C':
        return 'D';
        break;
    case 'D':
        return 'E';
        break;
    case 'E':
        return 'F';
    }
}

void junta_letra_left(char tabuleiro[][TAM], int i){ //funcao de juntar as letras
    if (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2] && tabuleiro[i][4] == tabuleiro[i][3] && tabuleiro[i][4] != '\0' && upa_cor(tabuleiro[i][4]) == upa_cor(upa_cor(tabuleiro[i][0])))
    {
        tabuleiro[i][0] = upa_cor(tabuleiro[i][4]);
        for (int j = 1; j < TAM; j++)
        {
            tabuleiro[i][j] = '\0';
        }
    }
    else
        for (int j = 0; j < 3; j++)
        {
            if (tabuleiro[i][j] == tabuleiro[i][j + 1] && tabuleiro[i][j + 1] == tabuleiro[i][j + 2] && tabuleiro[i][j] != '\0')
            {
                tabuleiro[i][j] = upa_cor(tabuleiro[i][j]);
                tabuleiro[i][j + 1] = '\0';
                tabuleiro[i][j + 2] = '\0';
                if (tabuleiro[i][j + 3] != '\0' && j < 2)
                {
                    tabuleiro[i][j + 1] = tabuleiro[i][j + 3];
                    tabuleiro[i][j + 3] = '\0';
                    if (tabuleiro[i][j + 4] != '\0' && j < 1)
                    {
                        tabuleiro[i][j + 2] = tabuleiro[i][j + 4];
                        tabuleiro[i][j + 4] = '\0';
                    }
                }
                else if (tabuleiro[i][j + 4] != '\0' && j < 1)
                {
                    tabuleiro[i][j + 1] = tabuleiro[i][j + 4];
                    tabuleiro[i][j + 4] = '\0';
                }
            }
        }
}

void junta_letra_right(char tabuleiro[][TAM], int i){
    if (tabuleiro[i][4] == tabuleiro[i][3] && tabuleiro[i][3] == tabuleiro[i][2] && tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][0] != '\0' && upa_cor(tabuleiro[i][0]) == upa_cor(upa_cor(tabuleiro[i][4]))){
        tabuleiro[i][4] = upa_cor(tabuleiro[i][0]);
        for (int j = 3; j >= 0; j--){
            tabuleiro[i][j] = '\0';
        }
    }
    else
        for (int j = TAM - 1; j > 1; j--){
            if (tabuleiro[i][j] == tabuleiro[i][j - 1] && tabuleiro[i][j - 1] == tabuleiro[i][j - 2] && tabuleiro[i][j] != '\0'){
                tabuleiro[i][j] = upa_cor(tabuleiro[i][j]);
                tabuleiro[i][j - 1] = '\0';
                tabuleiro[i][j - 2] = '\0';
                if (tabuleiro[i][j - 3] != '\0' && j > 2){
                    tabuleiro[i][j - 1] = tabuleiro[i][j - 3];
                    tabuleiro[i][j - 3] = '\0';
                    if (tabuleiro[i][j - 4] != '\0' && j > 3){
                        tabuleiro[i][j - 2] = tabuleiro[i][j - 4];
                        tabuleiro[i][j - 4] = '\0';
                    }
                }
                else if (tabuleiro[i][j - 4] != '\0' && j > 3){
                    tabuleiro[i][j - 1] = tabuleiro[i][j - 4];
                    tabuleiro[i][j - 4] = '\0';
                }
            }
        }
}

void junta_letra_up(char tabuleiro[][TAM], int i){
    if (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i] && tabuleiro[4][i] == tabuleiro[3][i] && tabuleiro[4][i] != '\0' && upa_cor(tabuleiro[4][i]) == upa_cor(upa_cor(tabuleiro[0][i]))){
        tabuleiro[0][i] = upa_cor(tabuleiro[4][i]);
        for (int j = 1; j < TAM; j++){
            tabuleiro[j][i] = '\0';
        }
    }
    else
        for (int j = 0; j < 3; j++){
            if (tabuleiro[j][i] == tabuleiro[j + 1][i] && tabuleiro[j + 1][i] == tabuleiro[j + 2][i] && tabuleiro[j][i] != '\0'){
                tabuleiro[j][i] = upa_cor(tabuleiro[j][i]);
                tabuleiro[j + 1][i] = '\0';
                tabuleiro[j + 2][i] = '\0';
                if (tabuleiro[j + 3][i] != '\0' && j < 2){
                    tabuleiro[j + 1][i] = tabuleiro[j + 3][i];
                    tabuleiro[j + 3][i] = '\0';
                    if (tabuleiro[j + 4][i] != '\0' && j < 1){
                        tabuleiro[j + 2][i] = tabuleiro[j + 4][i];
                        tabuleiro[j + 4][i] = '\0';
                    }
                }
                else if (tabuleiro[j + 4][i] != '\0' && j < 1){
                    tabuleiro[j + 1][i] = tabuleiro[j + 4][i];
                    tabuleiro[j + 4][i] = '\0';
                }
            }
        }
}

void junta_letra_down(char tabuleiro[][TAM], int i){
    if (tabuleiro[4][i] == tabuleiro[3][i] && tabuleiro[3][i] == tabuleiro[2][i] && tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[0][i] != '\0' && upa_cor(tabuleiro[0][i]) == upa_cor(upa_cor(tabuleiro[4][i]))){
        tabuleiro[4][i] = upa_cor(tabuleiro[0][i]);
        for (int j = 3; j >= 0; j--){
            tabuleiro[j][i] = '\0';
        }
    }
    else
        for (int j = TAM - 1; j > 1; j--) {
            if (tabuleiro[j][i] == tabuleiro[j - 1][i] && tabuleiro[j - 1][i] == tabuleiro[j - 2][i] && tabuleiro[j][i] != '\0'){
                tabuleiro[j][i] = upa_cor(tabuleiro[j][i]);
                tabuleiro[j - 1][i] = '\0';
                tabuleiro[j - 2][i] = '\0';
                if (tabuleiro[j - 3][i] != '\0' && j > 2){
                    tabuleiro[j - 1][i] = tabuleiro[j - 3][i];
                    tabuleiro[j - 3][i] = '\0';
                    if (tabuleiro[j - 4][i] != '\0' && j > 3)
                    {
                        tabuleiro[j - 2][i] = tabuleiro[j - 4][i];
                        tabuleiro[j - 4][i] = '\0';
                    }
                }
                else if (tabuleiro[j - 4][i] != '\0' && j > 3){
                    tabuleiro[j - 1][i] = tabuleiro[j - 4][i];
                    tabuleiro[j - 4][i] = '\0';
                }
            }
        }
}

void move_linha_left(char tabuleiro[][TAM]){//funcao de mover as letras
    for (int i = 0; i < TAM; i++){
        char temp[TAM];
        int j, a = 0;
        for (j = 0; j < TAM; j++){
            if (tabuleiro[i][j] != '\0'){
                temp[a] = tabuleiro[i][j];
                a++;
            }
        }
        for (j = 0; j < TAM; j++){
            if (j < a)
                tabuleiro[i][j] = temp[j];
            else
                tabuleiro[i][j] = '\0';
        }

        junta_letra_left(tabuleiro, i);
    }
}

void move_linha_right(char tabuleiro[][TAM]){
    for (int i = 0; i < TAM; i++){
        char temp[TAM];
        int j;
        int b = TAM - 1;
        for (j = TAM - 1; j >= 0; j--){
            if (tabuleiro[i][j] != '\0'){
                temp[b] = tabuleiro[i][j];
                b--;
            }
        }
        for (j = 0; j < TAM; j++){
            if (j <= b)
                tabuleiro[i][j] = '\0';
            else
                tabuleiro[i][j] = temp[j];
        }
        junta_letra_right(tabuleiro, i);
    }
}

void move_coluna_up(char tabuleiro[][TAM]){
    for (int i = 0; i < TAM; i++){
        char temp[TAM];
        int j;
        int a = 0;
        for (j = 0; j < TAM; j++){
            if (tabuleiro[j][i] != '\0')
            {
                temp[a] = tabuleiro[j][i];
                a++;
            }
        }
        for (j = 0; j < TAM; j++)
        {
            if (j < a)
                tabuleiro[j][i] = temp[j];
            else
                tabuleiro[j][i] = '\0';
        }
        junta_letra_up(tabuleiro, i);
    }
}

void move_coluna_down(char tabuleiro[][TAM]){
    for (int i = 0; i < TAM; i++){
        char temp[TAM];
        int j;
        int b = TAM - 1;
        for (j = TAM - 1; j >= 0; j--)
        {
            if (tabuleiro[j][i] != '\0')
            {
                temp[b] = tabuleiro[j][i];
                b--;
            }
        }
        for (j = 0; j < TAM; j++)
        {
            if (j <= b)
                tabuleiro[j][i] = '\0';
            else
                tabuleiro[j][i] = temp[j];
        }
        junta_letra_down(tabuleiro, i);
    }
}

void desenha_tela_inicial(){
    int x = 300, y = 240;
    al_clear_to_color(al_map_rgb(217, 196, 235));

    al_draw_textf(font_info, al_map_rgb(0, 0, 0), x + 100, y - 40, ALLEGRO_ALIGN_CENTER, "Digite seu nome para começar (3 a 8 letras):");
    al_draw_rectangle(x - 1, y - 1, x + 201, y + 41, al_map_rgb(115, 94, 133), 2);
    al_draw_filled_rectangle(x, y, x + 200, y + 40, al_map_rgb(192, 158, 222));
    al_draw_textf(font_info, al_map_rgb(0, 0, 0), x + 100, y + 8, ALLEGRO_ALIGN_CENTER, "%s", player.nome);

    al_draw_filled_rectangle(x - 50, y + 100, x + 250, y + 140, al_map_rgb(115, 94, 133));
    al_draw_textf(font_info, al_map_rgb(0, 0, 0), x + 100, y + 108, ALLEGRO_ALIGN_CENTER, "Aperte ENTER para começar!");

    al_draw_textf(font_info, al_map_rgb(0, 0, 0), x + 100, 550, ALLEGRO_ALIGN_CENTER, "Quando o jogo terminar aparecerá o ranking com as 5 melhores pontuações.");
    al_flip_display();
}

void tela_inicial(){
    int indice = 0;
    bool loop = true;
    for(int i = 0; i < 9; i++)
        player.nome[i] = '\0';

    while (!display_close && loop){
        desenha_tela_inicial(player);

        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_KEY_CHAR && indice <= 7){
            int c = event.keyboard.unichar;
            if ((event.keyboard.unichar >= 'A' && event.keyboard.unichar <= 'Z') || (event.keyboard.unichar >= 'a' && event.keyboard.unichar <= 'z') || event.keyboard.unichar == ' '){
                player.nome[indice] = (char)c;
                indice++;
            }
        }

        if (event.type == ALLEGRO_EVENT_KEY_DOWN){
            if (event.keyboard.keycode == ALLEGRO_KEY_ENTER && indice > 2)
                loop = false;
            if(event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && indice > 0){
                indice--;
                player.nome[indice] = '\0';
            }
        }

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            display_close = true;
        }
    }
}

bool acaba_partida(char tabuleiro[][TAM]){ //verifica se pode acabar a partida
    for (int i = 0; i < 5; i++){ // verifica se tem F no tabuleiro
        for (int j = 0; j < 5; j++){
            if (tabuleiro[i][j] == 'F')
                return false;
        }
    }

    if (!tabuleiro_cheio())
        return true;

    for (int i = 0; i < TAM; i++){ // verifica se tem movimento possivel
        for (int j = 0; j < 3; j++){ // esquerda e cima
            if (tabuleiro[i][j] == tabuleiro[i][j + 1] && tabuleiro[i][j + 1] == tabuleiro[i][j + 2]){
                return true;
            }
            if (tabuleiro[j][i] == tabuleiro[j + 1][i] && tabuleiro[j + 1][i] == tabuleiro[j + 2][i]){
                return true;
            }
        }
    }

    return false;
}

void tabuleiro_inicial(){ //inicializa o tabuleiro para poder jogar
    for(int i= 0; i<5;i++){ // esvazia o tabuleiro
        for(int j= 0; j<5;j++){
            tabuleiro[i][j] = '\0';
        }
    }
    //poe 2 letras aleatorias em posicoes aleatorias
    poe_letra(rand() % 4, tabuleiro);
    poe_letra(rand() % 4, tabuleiro);
}

void copiaTabuleiro(char tabuleiro[][5], char tabuleiro_aux[][5]) { //auxiliar para verificaJogada
    memcpy(tabuleiro_aux, tabuleiro, sizeof(char) * 5 * 5);
}

bool verificaJogada(char tabuleiro[][5], char tabuleiroAnterior[][5]) { //verifica teve movimentação no tabuleiro para definir se vai ou nao por letra nova
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (tabuleiro[i][j] != tabuleiroAnterior[i][j]) {
                return true; 
            }
        }
    }
    return false;
}

void tela_tabuleiro(est ranking[TAM]){
    tabuleiro_inicial();
    if(!display_close)
        do{
            ALLEGRO_EVENT event;
            al_wait_for_event(queue, &event);

            copiaTabuleiro(tabuleiro, tabuleiro_aux);
            if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                switch (event.keyboard.keycode){
                    case ALLEGRO_KEY_UP:
                            move_coluna_up(tabuleiro);
                        break;
                    case ALLEGRO_KEY_DOWN:
                            move_coluna_down(tabuleiro);
                        break;
                    case ALLEGRO_KEY_LEFT:
                            move_linha_left(tabuleiro); 
                        break;
                    case ALLEGRO_KEY_RIGHT:
                            move_linha_right(tabuleiro); 
                        break;
                }
                if(verificaJogada(tabuleiro, tabuleiro_aux) && (event.keyboard.keycode == ALLEGRO_KEY_UP || event.keyboard.keycode == ALLEGRO_KEY_DOWN || event.keyboard.keycode == ALLEGRO_KEY_LEFT || event.keyboard.keycode == ALLEGRO_KEY_RIGHT))
                    poe_letra(rand() % 4, tabuleiro);
            }

            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                display_close = true;
            }
            
            desenharTabuleiro(ranking);
        } while (acaba_partida(tabuleiro) && !display_close);
}

void tela_final(est ranking[], bool display_close){
    if(!display_close)
        do{ 
            ALLEGRO_EVENT event;
            al_wait_for_event(queue, &event);

            al_clear_to_color(al_map_rgb(217, 196, 235));
            al_draw_textf(font_info, al_map_rgb(0, 0, 0), 330, 10, ALLEGRO_ALIGN_LEFT, "Ranking:");
            for (int i = 0; i < 5; i++){
                al_draw_textf(font_info, al_map_rgb(0, 0, 0), 330, 40 + i * 25, ALLEGRO_ALIGN_LEFT, "%d ", i + 1);
                al_draw_textf(font_info, al_map_rgb(0, 0, 0), 350, 40 + i * 25, ALLEGRO_ALIGN_LEFT, "-> %d - %s", ranking[i].pont, ranking[i].nome);
            }

            if (player.pont > ranking[4].pont){
                al_draw_textf(font_info, al_map_rgb(0, 0, 0), 400, 195, ALLEGRO_ALIGN_CENTER, "%s, você entrou no ranking!", player.nome);
                al_draw_bitmap(imgHappy, 163, 250, 0);
            }
            else{
                al_draw_textf(font_info, al_map_rgb(0, 0, 0), 400, 195, ALLEGRO_ALIGN_CENTER, "%s, você não tem pontuação suficiente para entrar no ranking.", player.nome);
                al_draw_bitmap(imgSad, 262, 250, 0);
            }
            al_draw_textf(font_info, al_map_rgb(0, 0, 0), 400, 550, ALLEGRO_ALIGN_CENTER, "Para jogar novamente aperte ENTER!");

            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                display_close = true;
            }

            if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ENTER){
                jogar_novamente = true;
            }

            al_flip_display();
        } while (!display_close && !jogar_novamente);
}

int main(){
    srand(time(0));
    inicializarAllegro();
    est ranking[5];

    do{
        jogar_novamente = false;
        ler_ranking(ranking);
        tela_inicial();
        tela_tabuleiro(ranking);
        registra_entrada(ranking);
        tela_final(ranking, display_close);
    } while(jogar_novamente && !display_close);

    finalizarAllegro();
}