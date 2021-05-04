// Trabalho Pratico de Programação
// DEIS-ISEC 2020-2021
// João Oliveira, nº 2018012875

// Libraries

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// decidi incluir o stdbool, pois é parte do standard C99 e eu sou dependente de boolean, sendo que é de boa prática
// usá-lo para variáveis descartáveis e proteção do programa :P

#include <string.h>
// #include <conio.h>

// também podia fazer
// #define char bool
// #define true 1
// #define false 0
// mas não tem tanta piada x]

//  #include <unistd.h>
//  ^^  decidi não usar o access() para ficheiros, para não arriscar ter problemas com compilação noutros PCs,
//      apesar de ser uma library standard do C99.

// Header Files

#include "menus.h"
#include "jogo.h"
// #include "utils.h"

// DEFINE + STRUCTS

#define LINHASDEFAULT 4
#define COLUNASDEFAULT 4
#define TAMANHOX 30

typedef struct Players{
    char UserName[TAMANHOX];
    int PowerUps[2];
}Player;

void ImprimeTabuleiro(char Tabuleiro[LINHASDEFAULT][COLUNASDEFAULT], int Linh, int Cols){
    for(int i=0;i<Linh;i++){
        for(int j=0;j<Cols;j++){
            printf("%c\t",Tabuleiro[i][j]);
        }
    }
}

Player CriaJogador(char PlayerUsername[TAMANHOX]){
    Player Jogador;
    strcpy(Jogador.UserName, PlayerUsername);
    Jogador.PowerUps[0] = 0;
    Jogador.PowerUps[1] = 0;
    return Jogador;
}

char RecebeJogada(){
    char Jogada;

    printf("\nO que pretende fazer?\n>");
    scanf("%c", &Jogada);

    return Jogada;
}

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

void NovoJogo(Player Player1, Player Player2, char Filename[]){

}

void menu(){
    int inputMenu = 0;
    char Filename[20];
    bool avancar = false;
    char UserName1[20];
    char UserName2[20];

    MenuInicial();

    do {
        scanf("%d", &inputMenu);

        if(inputMenu == 1){
            avancar = true;
            printf("\nQual vai ser o nome do Jogador 1?\n> ");
            scanf("%s", &UserName1);
            printf("\nQual vai ser o nome do Jogador 2?\n> ");
            scanf("%s", &UserName2);
            printf("\nQual vai ser o nome do seu jogo?\n> ");
            scanf("%s", &Filename);
            NovoJogo(CriaJogador(UserName1), CriaJogador(UserName2), Filename);
        }
        else if(inputMenu == 2){
            avancar = true;
            //getSaveGame();
        }
        else if(inputMenu == 3){
            avancar = true;
            exit;
        }
        else if(inputMenu == 9){
            avancar = false;
            ComandoAjuda();
        }
        else printf("\nInput invalido! Tente novamente.\n>");
    } while (avancar == false);
}

void StartGame(){
    int inputMenu = 0;
    bool avancar = false;

    bool HaJogoAnterior = JogoAnterior();

    if (HaJogoAnterior == true) {
        do {
            printf("\nDeixou um jogo por completar! Deseja continuar ou voltar para o menu?\n\n1 - Continuar\n2 - Voltar ao menu");
            scanf("%d", &inputMenu);
            if (inputMenu == 1) {
                avancar = true;
                printf("\nGanda fixe!");
            } else if (inputMenu == 2) {
                avancar = true;
                menu();
            }
            else printf("\nInput invalido! Volte a tentar.");
        } while (avancar == false);
    } else menu();
}