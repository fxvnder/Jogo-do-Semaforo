// Trabalho Pratico de P
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

//  #include <unistd.h>
//  ^^  decidi não usar o access() para ficheiros, para não arriscar ter problemas com compilação noutros PCs,
//      apesar de ser uma library standard do C99.

// Header Files

#include "menus.h"
// #include "utils.h"

bool JogoAnterior(){
    FILE * saveFile;
    saveFile = fopen("LastGameSave.bin", "rb"); // read-only. só vai verificar se o ficheiro existe.
    if (saveFile){
        // ISTO SIGNIFICA QUE EXISTE UM JOGO ANTERIOR GUARDADO QUE NÃO FOI TERMINADO
        fclose(saveFile);
        return true;
    }else{
        // ISTO SIGNIFICA QUE NÃO EXISTE NENHUM SAVE ANTERIOR OU QUE O JOGO ANTERIOR FOI TERMINADO
        return false;
    }
}

void NovoJogo(char Filename[]){
    //
}

void menu(){
    int inputMenu = 0;
    char Filename[20];
    bool avancar = false;

    MenuInicial();

    do {
        scanf("%d", &inputMenu);

        if(inputMenu == 1){
            avancar = true;
            printf("\nQual vai ser o nome do seu jogo?\n");
            scanf("%s", &Filename);
            //NovoJogo(Filename);
        }
        else if(inputMenu == 2){
            avancar = true;
            //getSaveGame();
        }
        else if(inputMenu == 3){
            exit;
        }
        else printf("\nInput invalido! Tente novamente.\n>");
    } while (avancar == false);

}

int main() {
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

    return 0;
}
