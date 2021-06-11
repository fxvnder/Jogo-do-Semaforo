// Trabalho Pratico de Programação
// DEIS-ISEC 2020-2021
// João Oliveira, nº 2018012875

// Libraries

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// decidi incluir o stdbool, pois é parte do standard C99 e eu sou dependente de boolean, sendo que é de boa prática
// usá-lo para variáveis descartáveis e proteção do programa :P

// também podia fazer
// #define char bool
// #define true 1
// #define false 0
// mas não tem tanta piada x]

#include <string.h>
// #include <conio.h>

//  #include <unistd.h>
//  ^^  decidi não usar o access() para ficheiros, para não arriscar ter problemas com compilação noutros PCs,
//      apesar de ser uma library standard do C99.

// Header Files

#include "menus.h"
#include "jogo.h"
#include "utils.h"

// DEFINE + STRUCTS

//#define LINHASDEFAULT 9 // TAMANHO MAXIMO POSSIVEL
//#define COLUNASDEFAULT 9 // TAMANHO MAXIMO POSSIVEL
//#define TAMANHOX 30


// CODIGO DO JOGO


// LIMPA A MEMORIA

void limparMemoriaTab(TabuleiroStr tabuleiroJogo) {
    free(tabuleiroJogo.tab);
    printf("Memoria limpa! Ate a proxima!");
}

// CRIA O TABULEIRO DO JOGO

TabuleiroStr CriaTabuleiro(){
    TabuleiroStr tabuleiroJogo;

    tabuleiroJogo.linha = intUniformRnd(3,5); // obtem o tamanho do tabuleiro
    tabuleiroJogo.coluna = tabuleiroJogo.linha; // obtem o tamanho do tabuleiro

    printf("\nA carregar... A criar Tabuleiro...");
    tabuleiroJogo.tab = malloc(sizeof(char*) * tabuleiroJogo.linha);
    for (int i = 0; i < tabuleiroJogo.linha; ++i) {
        tabuleiroJogo.tab[i] = (char*) malloc(tabuleiroJogo.coluna);
    }
    printf("\nA carregar... Tabuleiro criado com sucesso!");

    return tabuleiroJogo;
}

// INICIA O TABULEIRO DO JOGO

void CriaTabuleiroInicial(TabuleiroStr tabuleiroJogo){
    printf("\nA carregar... A iniciar tabuleiro...\n");
    for (int i = 0; i < tabuleiroJogo.linha; ++i) {
        for (int j = 0; j < tabuleiroJogo.coluna; ++j) {
            tabuleiroJogo.tab[i][j] = '_';
        }
    }
    printf("\nA carregar...Tabuleiro iniciado com sucesso!");
}

// IMPRIME O TABULEIRO

void ImprimeTabuleiro(TabuleiroStr tabuleiroJogo){
    printf("\nTabuleiro:\n");
    for(int i=0;i<tabuleiroJogo.linha;i++){
        for(int j=0;j<tabuleiroJogo.coluna;j++){
            printf("[ %c ]\t",tabuleiroJogo.tab[i][j]); // vai imprimir as linhas, basicamente
        }
        printf("\n");
    }
}

// CRIA JOGADOR

Player CriaJogador(char PlayerUsername[TAMANHOX]){
    Player Jogador;
    strcpy(Jogador.UserName, PlayerUsername); // atribui o nickname ao jogador
    Jogador.PowerUps[0] = 0; // Adiciona pedra = 0, o jogo ainda nao comecou, ele ainda nao usou este power up
    Jogador.PowerUps[1] = 0; // Adiciona linha/coluna = 0 ^^ idem
    return Jogador;
}

// MANAGE DAS JOGADAS

char RecebeJogada(Player JogadorRonda){
    char Jogada;

    printf("\nO que pretende fazer, %c?\nInsira o num da coluna ou 's' para sair\n>", *JogadorRonda.UserName);
    scanf("%c", &Jogada);

    return Jogada;
}

// CARREGA JOGO

bool JogoAnterior(){
    FILE * saveFile;
    saveFile = fopen("LastGameSave.bin", "rb"); // read-only binary. só vai verificar se o ficheiro existe.
    if (saveFile){
        // ISTO SIGNIFICA QUE EXISTE UM JOGO ANTERIOR GUARDADO QUE NÃO FOI TERMINADO
        fclose(saveFile);
        return true;
    } else {
        // ISTO SIGNIFICA QUE NÃO EXISTE NENHUM SAVE ANTERIOR OU QUE O JOGO ANTERIOR FOI TERMINADO
        // não tem "fclose()" pois não é necessário fechar um ficheiro que nem foi aberto, não é?
        return false;
    }
}

// NOVO JOGO

void NovoJogo(Player Player1, Player Player2, char Filename){

    initRandom(); // inicia o randomizer

    TabuleiroStr TabuleiroJogo = CriaTabuleiro();

    int nRondas = 1;
    bool QueroSair = false;

    CriaTabuleiroInicial(TabuleiroJogo);

    do {
        ImprimeTabuleiro(TabuleiroJogo);
        RecebeJogada(Player1);
        ImprimeTabuleiro(TabuleiroJogo);
        RecebeJogada(Player2);
        QueroSair = true;
    } while (!QueroSair);

    limparMemoriaTab(TabuleiroJogo);
}

// MENU INICIAL

void menu(){
    char inputMenu = 0;
    char Filename;
    bool avancar = false;
    char UserName1[TAMANHOX];
    char UserName2[TAMANHOX];

    MenuInicial();

    do {

        scanf("%c", &inputMenu);

        switch (inputMenu) {

            case '1':
                avancar = true;
                printf("\nQual vai ser o nickname do Jogador A?\n> ");
                scanf("%s", &UserName1[TAMANHOX]);
                printf("\nQual vai ser o nickname do Jogador B?\n> ");
                scanf("%s", &UserName2[TAMANHOX]);
                printf("\nQual vai ser o nome do seu jogo?\n> ");
                scanf("%s", &Filename);
                NovoJogo(CriaJogador(UserName1), CriaJogador(UserName2), Filename);
                break;

            case '2':
                avancar = true;
                //getSaveGame();
                break;

            case '3':
                avancar = false;
                ComandoAjuda();
                break;

            case '9':
                avancar = true;
                exit(0);
                // break; - nao necessario por causa do exit

            default:
                printf("\nInput invalido! Tente novamente.\n>");

        }

    } while (avancar == false);

}

// INICIO DO JOGO

void StartGame(){
    char inputMenu = '0';
    bool avancar = false;

    bool HaJogoAnterior = JogoAnterior();

    if (HaJogoAnterior == true) {
        do {
            printf("\nDeixou um jogo por completar! Deseja continuar ou voltar para o menu?\n\n1 - Continuar\n2 - Voltar ao menu");
            scanf("%c", &inputMenu);
            if (inputMenu == '1') {
                avancar = true;
                printf("\nGanda fixe!");
            } else if (inputMenu == '2') {
                avancar = true;
                menu();
            }
            else printf("\nInput invalido! Volte a tentar.");
        } while (avancar == false);
    } else menu();
}