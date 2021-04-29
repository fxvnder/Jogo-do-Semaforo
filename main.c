// Trabalho Pratico de P
// DEIS-ISEC 2020-2021
// João Oliveira, nº 2018012875

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "menus.h"
// #include "utils.h"

int JogoAnterior(){
    const char *NomeSaveBin = "LastGameSave.bin";
    if( access( NomeSaveBin, F_OK ) == 0 ) {
        // ISTO SIGNIFICA QUE EXISTE UM JOGO ANTERIOR GUARDADO QUE NÃO FOI TERMINADO
        return 1;
    } else {
        // ISTO SIGNIFICA QUE NÃO EXISTE NENHUM SAVE ANTERIOR OU QUE O JOGO ANTERIOR FOI TERMINADO
        return 0;
    }
}

void NovoJogo(char Filename[]){
    //
}

void menu(){
    int inputMenu = 0;
    char Filename[20];

    MenuInicial();

    scanf("%d", &inputMenu);

    if(inputMenu == 1){
        printf("\nQual vai ser o nome do seu jogo?\n");
        scanf("%s", &Filename);
        //NovoJogo(Filename);
    }
    else if(inputMenu == 2){
        //getSaveGame();
    }
    else if(inputMenu == 3){
        exit;
    }
}

int main() {
    int inputMenu = 0;
    bool avancar = false;

    if(JogoAnterior() == 1){
        printf("\nDeixou um jogo por completar! Deseja continuar ou voltar para o menu?\n\n1 - Continuar\n2 - Voltar ao menu");
        scanf("%d", &inputMenu);
        if(inputMenu == 1) {

        }
        else if (inputMenu == 2) {
            menu;
        }
        else printf("\nInput invalido! Volte a tentar.");
    }
    else if(JogoAnterior() == 0){
        menu;
    }

    return 0;
}
