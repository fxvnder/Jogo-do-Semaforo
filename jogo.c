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

// SLEEP INSTRUCTIONS ZZZZZZZZZZZZzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz

// DETETA O OS DO UTILIZADOR PARA TER O INCLUDE QUE FAZ O SLEEP - deprecated

//#ifdef WIN32    // caso windows
//    #include <windows.h>
//    #define dorme(x) Sleep(x*100) // case sensitive + o windows funciona com milisegundos
//#else           // caso sistema operativo decente (ou mac)
//    #include <unistd.h>
//    #define dorme(x) usleep(x*100000)
//#endif

// Header Files

#include "menus.h"
#include "jogo.h"
#include "utils.h"

// DEFINE + STRUCTS

//#define LINHASDEFAULT 9 // TAMANHO MAXIMO POSSIVEL
//#define COLUNASDEFAULT 9 // TAMANHO MAXIMO POSSIVEL
//#define TAMANHOX 30

// A ÚNICA VARIÁVEL GLOBAL DESTE PROGRAMA (e a única que merece perdão)
// int NotaTP = 20;
// após muita reflexão, tirei a variável global. não fui capaz de cumprir a minha promessa. peço desculpa.


// CODIGO DO JOGO

// --------------------------------------------------- GUARDA / RETOMA JOGO

void GuardaProg(TabuleiroStr tabuleiroJogo, Player *jog1, Player *jog2){
    FILE* fch = fopen("LastGameSave.bin", "wb");

    if(fch == NULL){
        printf("\nErro a guardar ficheiro.");
        return;
    }

    fwrite(&tabuleiroJogo, sizeof(TabuleiroStr), 1, fch);

    fwrite(&jog1, sizeof(Player), 1, fch);

    fwrite(&jog2, sizeof(Player), 1, fch);

    printf("\nGuardou com sucesso!");

    fclose(fch);
}

void ContinuaJogo(TabuleiroStr *tabuleiroJogo, Player *jog1, Player *jog2){

    limparMemoriaTab(*tabuleiroJogo);

    FILE* fch = fopen("LastGameSave.bin", "r");

    if(fch == NULL){
        printf("\nErro a abrir ficheiro.");
    }

    fread(tabuleiroJogo, sizeof(TabuleiroStr),1, fch);

    fread(jog1, sizeof(Player),1, fch);

    fread(jog2, sizeof(Player),1, fch);

    fclose(fch);
}


// --------------------------------------------------- SAI DO JOGO


void FimDoJogo(int Razao){
    if(Razao == 0){
        printf("\nCom que entao decidiste sair... Bem, ate a proxima! Espero que te tenhas divertido!");
        exit(0);
    } else if(Razao == 1){
        printf("\nAte a proxima!");
        exit(0);
    } else {
        printf("\nBem... Aposto que tiveste uma boa razao... Bye!");
    }
}

// --------------------------------------------------- VERIFICAÇÃO FIM JOGO

// LINHAS

bool VerificaLinha(TabuleiroStr tabuleiroJogo){
    for(int i = 0; i < tabuleiroJogo.linha; i++){
        if (tabuleiroJogo.tab[i][0] != ' ' && tabuleiroJogo.tab[i][0] != 'P'){
            for (int j = 0; j < tabuleiroJogo.coluna; ++j) {
                if (tabuleiroJogo.tab[i][0] == tabuleiroJogo.tab[i][j]){ // todas as peças coincidem
                    if(j == tabuleiroJogo.coluna - 1){
                        return true;
                    }
                }
                else{
                    break;
                }
            }
        }
    }
    return false;
}

// COLUNAS

bool VerificaColuna(TabuleiroStr tabuleiroJogo){
    for(int i = 0; i < tabuleiroJogo.coluna; i++){
        if (tabuleiroJogo.tab[0][i] != ' ' && tabuleiroJogo.tab[0][i] != 'P'){
            for (int j = 0; j < tabuleiroJogo.linha; ++j) {
                if (tabuleiroJogo.tab[0][i] == tabuleiroJogo.tab[j][i]){ // todas as peças coincidem
                    if(j == tabuleiroJogo.linha - 1){
                        return true;
                    }
                }
                else break;
            }
        }
    }

    return false;
}

// DIAGONAIS

bool VerificaDiagonal(TabuleiroStr tabuleiroJogo){

    if (tabuleiroJogo.linha != tabuleiroJogo.coluna){
        return false;
    }

    if (tabuleiroJogo.tab[0][0] != ' ' && tabuleiroJogo.tab[0][0] != 'P'){
        for (int i = 0; i < tabuleiroJogo.coluna; ++i) {
            if(tabuleiroJogo.tab[i][i] == tabuleiroJogo.tab[0][0]){
                if(i == tabuleiroJogo.coluna - 1){
                    return true;
                }
            }
            else break;
        }
    }

    if (tabuleiroJogo.tab[0][tabuleiroJogo.linha - 1] != ' ' && tabuleiroJogo.tab[0][tabuleiroJogo.linha - 1] != 'P'){
        for (int i = tabuleiroJogo.coluna; i > 0; --i) {
            if(tabuleiroJogo.tab[i][tabuleiroJogo.linha - 1 - i] == tabuleiroJogo.tab[0][tabuleiroJogo.linha - 1]){
                if(i == tabuleiroJogo.coluna - 1){
                    return true;
                }
            }
            else break;
        }
    }

    return false;
}

// GERENCIA AS VERIFICACOES

bool JogoAcabado(TabuleiroStr tabuleiroJogo){

    // linhas
    if(VerificaLinha(tabuleiroJogo)) return true;

    // colunas
    if(VerificaColuna(tabuleiroJogo)) return true;

    // diagonais
    if(VerificaDiagonal(tabuleiroJogo)) return true;

    // nada
    return false;
}

// --------------------------------------------------- TABULEIRO

// LIMPA A MEMORIA

void limparMemoriaTab(TabuleiroStr tabuleiroJogo) {
    free(tabuleiroJogo.tab);
    //printf("Memoria limpa! Ate a proxima!");
}

// CRIA O TABULEIRO DO JOGO

TabuleiroStr CriaTabuleiro(){
    TabuleiroStr tabuleiroJogo;

    tabuleiroJogo.linha = intUniformRnd(3,5); // obtem o tamanho do tabuleiro
    tabuleiroJogo.coluna = tabuleiroJogo.linha; // obtem o tamanho do tabuleiro

    //fprintf(stderr,"\nA carregar... A criar Tabuleiro...");
    tabuleiroJogo.tab = malloc(sizeof(char*) * tabuleiroJogo.linha);
    for (int i = 0; i < tabuleiroJogo.linha; ++i) {
        tabuleiroJogo.tab[i] = (char*) malloc(tabuleiroJogo.coluna);
    }
    //fprintf(stderr,"\nA carregar... Tabuleiro criado com sucesso!");

    return tabuleiroJogo;
}

// INICIA O TABULEIRO DO JOGO

void CriaTabuleiroInicial(TabuleiroStr tabuleiroJogo){
    //fprintf(stderr,"\nA carregar... A iniciar tabuleiro...");

    for (int i = 0; i < tabuleiroJogo.linha; i++) {
        for (int j = 0; j < tabuleiroJogo.coluna; j++) {
            tabuleiroJogo.tab[i][j] = ' ';
        }
    }

    //fprintf(stderr,"\nA carregar... Tabuleiro iniciado com sucesso!");
}

// CRIA NOVO TABULEIRO EM CASO DE RESIZING ETC.

TabuleiroStr CriaNovoTabuleiro(TabuleiroStr TabuleiroAntigo, int Aumenta) {
    TabuleiroStr NovoTabJogo = TabuleiroAntigo;

    // LINHA

    if (Aumenta == 1) {

        NovoTabJogo.linha = TabuleiroAntigo.linha + 1;
        NovoTabJogo.coluna = TabuleiroAntigo.coluna;

        // REALOCAR O ARRAY
        NovoTabJogo.tab = realloc(NovoTabJogo.tab, NovoTabJogo.linha*sizeof(char*));

        // REALOCAR O CONTEUDO PREVIAMENTE ALOCADO PARA INCREMENTAR A LINHA
        // NovoTabJogo.tab = (char**) realloc(NovoTabJogo.tab, sizeof(char**));

        // ALOCAR A LINHA NOVA
        NovoTabJogo.tab[NovoTabJogo.linha - 1] = (char *) malloc(sizeof (char*) * NovoTabJogo.coluna);

        // PREENCHER A LINHA NOVA COM ' '
        for (int i = 0; i < NovoTabJogo.coluna; ++i) {
            NovoTabJogo.tab[NovoTabJogo.linha - 1][i] = ' ';
        }

        // RETORNA O NOVO TABULEIRO
        return NovoTabJogo;
    }

    // COLUNA

    else {
        NovoTabJogo.linha = TabuleiroAntigo.linha;
        NovoTabJogo.coluna = TabuleiroAntigo.coluna + 1;

        // REALOCAR O ARRAY
        // NovoTabJogo.tab = realloc(NovoTabJogo.tab, NovoTabJogo.coluna*sizeof(char*));

        // REALOCAR O CONTEUDO PREVIAMENTE ALOCADO PARA INCREMENTAR A LINHA
        for (int i = 0; i < TabuleiroAntigo.linha; ++i) {
            NovoTabJogo.tab[i] = (char*) realloc(NovoTabJogo.tab[i], sizeof(char) * NovoTabJogo.coluna);
        }

        // ALOCAR A COLUNA NOVA
//        for (int i = TabuleiroAntigo.coluna; i < NovoTabJogo.coluna; ++i) {
//            NovoTabJogo.tab[i] = (char *) malloc(sizeof (char*) * NovoTabJogo.coluna);
//        }

        // PREENCHER A COLUNA NOVA COM ' '
        for (int i = 0; i < NovoTabJogo.linha; ++i) {
            NovoTabJogo.tab[i][NovoTabJogo.coluna - 1] = ' ';
        }

        // RETORNA O NOVO TABULEIRO
        return NovoTabJogo;
    }

}

// IMPRIME O TABULEIRO

void ImprimeTabuleiro(TabuleiroStr tabuleiroJogo){
    //fprintf(stderr,"\nA carregar Tabuleiro...");
    printf("\n\nTabuleiro:\n");
    for(int i=0;i<tabuleiroJogo.linha;i++){
        for(int j=0;j<tabuleiroJogo.coluna;j++){
            printf("[ %c ]\t",tabuleiroJogo.tab[i][j]); // vai imprimir as linhas, basicamente
        }
        printf("\n");
    }
}

// TRATA DE COLOCAR AS JOGADAS NO TABULEIRO

bool PreencheTabuleiro(TabuleiroStr tabuleiroJogo, int x, int y, bool pedra, bool isBot) {

    //fprintf(stderr,"%d",tabuleiroJogo.tab[x][y]);
    
//    if (x > tabuleiroJogo.linha || y > tabuleiroJogo.coluna)
//    {
//        return false; // OH NO!!!
//    }

    if (x < tabuleiroJogo.linha &&  y < tabuleiroJogo.coluna) {
        if (!pedra) {
            //if (tabuleiroJogo.tab[x][y] != ' ' && tabuleiroJogo.tab[x][y] != 'G' && tabuleiroJogo.tab[x][y] != 'Y' && tabuleiroJogo.tab[x][y] != 'R' && tabuleiroJogo.tab[x][y] != 'P'){
            //    return false;
            //}
            if (tabuleiroJogo.tab[x][y] == ' ') {
                tabuleiroJogo.tab[x][y] = 'G';
                return true;
            }
            if (tabuleiroJogo.tab[x][y] == 'G') {
                tabuleiroJogo.tab[x][y] = 'Y';
                return true;
            }
            if (tabuleiroJogo.tab[x][y] == 'Y') {
                tabuleiroJogo.tab[x][y] = 'R';
                return true;
            }
            if (tabuleiroJogo.tab[x][y] == 'R') {
                if (!isBot){
                    printf("\nEstas a tentar jogar numa peca que ja se encontra vermelha!");
                }
                return false;
            }
            if (tabuleiroJogo.tab[x][y] == 'P') {
                if (!isBot){
                    printf("\nEstas a tentar jogar onde esta uma pedra! Tenta novamente.\n");
                }
            }
            else return false;
        }

        if (pedra) {
            if (tabuleiroJogo.tab[x][y] == 'P') {
                if (!isBot){
                    printf("\nEstas a tentar jogar uma pedra onde ja ha uma! Tenta novamente.\n");
                }
                return false;
            }
            else {
                tabuleiroJogo.tab[x][y] = 'P';
                return true;
            }
        }

        return false;
    } else return false;

}

// --------------------------------------------------- FICHEIROS

void ImprimeVencedor(FILE *ficheiroTXT, Player Vencedor, int nRondas, bool isBot){
    if (isBot){
        fprintf(ficheiroTXT, "APOS %d RONDAS, O ROBOT %s GANHOU.", nRondas, Vencedor.UserName);
    } else fprintf(ficheiroTXT, "O JOGADOR %s GANHOU COM %d RONDAS.", Vencedor.UserName, nRondas);
}

void ImprimeFicheiro(FILE *ficheiroTXT, TabuleiroStr tabuleiroJogo, int nRondas){
    fprintf(ficheiroTXT, "- Ronda %d -\n\n", nRondas);
    for(int i=0;i<tabuleiroJogo.linha;i++) {
        for (int j = 0; j < tabuleiroJogo.coluna; j++) {
            fprintf(ficheiroTXT, "[%c]", tabuleiroJogo.tab[i][j]);
        }
        fprintf(ficheiroTXT,"\n");
    }
    fprintf(ficheiroTXT,"\n\n");
}

FILE * CriaFicheiro(char FilenameF[TAMANHOX]){
    FILE * Ficheiro = fopen(FilenameF,"w"); // abre o ficheiro

    if(Ficheiro == NULL)
    {
        printf("Oops? Nao tenho permissao para criar ficheiros?\n"); // ??? espero que nao aconteça, porém para debug dá jeito
    }

    //fclose(Ficheiro); // fecha o ficheiro

    return Ficheiro; // retorna o ficheiro criado
}

void AbreFicheiro(char Filename[TAMANHOX]){
    FILE * ficheiro;
    char s;

    printf("%s" , Filename);

    ficheiro=fopen(Filename,"r");

    if(ficheiro==NULL)
    {
        printf("\nErro a abrir ficheiro.");
    }

    do {
        s = getc(ficheiro);
        printf("%c",s);
    } while(s!=EOF);

    printf("\nPrime qualquer tecla para voltar ao menu.");

    fclose(ficheiro);
}

// --------------------------------------------------- JOGADORES

// CRIA JOGADOR

Player CriaJogador(char PlayerUsername[TAMANHOX], bool isBOT){
    //fprintf(stderr,"\nA carregar... A criar Jogador %s...", PlayerUsername);
    Player Jogador;
    strcpy(Jogador.UserName, PlayerUsername); // atribui o nickname ao jogador
    Jogador.PowerUps[0] = 0; // Adiciona pedra = 0, o jogo ainda nao comecou, ele ainda nao usou este power up
    Jogador.PowerUps[1] = 0; // Adiciona linha/coluna = 0 ^^ idem
    if (isBOT == true){
        Jogador.isBot = true;
    } else Jogador.isBot = false;
    //fprintf(stderr,"\nA carregar... Jogador %s criado com sucesso!", Jogador.UserName);
    return Jogador;
}

// --------------------------------------------------- JOGADAS

// MANAGE DAS JOGADAS

TabuleiroStr RecebeJogada(Player* JogadorRonda, TabuleiroStr tabuleiroJogo, bool isBOT, Player* OutroJogador){
    int Jogada, Linha, xy, decisao, JogadaBOT, LinhaBOT, xyBOT, decisaoBOT, querGuardarProg;
    bool JogadaCompletada = false;
    bool JogadaCompletadaBOT = false;
    TabuleiroStr NovoTabuleiroJogo;

    if (!isBOT){ // SE NAO FOR BOT
        do {
            printf("\nO que pretende fazer, %s?\nInsira o num da coluna, '9' para aumentar uma linha/coluna ou '0' para sair\n> ", JogadorRonda->UserName);
            scanf("%d", &Jogada);
            getchar();

            switch (Jogada) {
                case 9:
                    if (JogadorRonda->PowerUps[1] < 2){
                        printf("\nQueres aumentar uma linha ou coluna?\n1 - Linha\n2 - Coluna\n0 - Volta atras\n> ");
                        scanf(" %d", &xy);
                        switch (xy) {
                            case 1:
                                JogadorRonda->PowerUps[1]++;
                                NovoTabuleiroJogo = CriaNovoTabuleiro(tabuleiroJogo, 1);
                                //fprintf(stderr,"\naumentou...");
                                return NovoTabuleiroJogo;

                            case 2:
                                JogadorRonda->PowerUps[1]++;
                                NovoTabuleiroJogo = CriaNovoTabuleiro(tabuleiroJogo, 2);
                                return NovoTabuleiroJogo;

                            case 9:
                                JogadaCompletada = false;
                                break;

                            default:
                                JogadaCompletada = false;
                        }
                    } else printf("\nJa usaste esse poder 2 vezes. Nao podes voltar a usa-lo.");
                    break;

                case 0:
                    printf("\nPretende guardar o progresso para continuar mais tarde?\n1 - Sim\nPrima outra tecla para nao guardar.\n> ");
                    scanf(" %d", &querGuardarProg);
                    if (querGuardarProg == 1){
                        GuardaProg(tabuleiroJogo, JogadorRonda, OutroJogador);
                        limparMemoriaTab(tabuleiroJogo);
                        FimDoJogo(1);
                    } else FimDoJogo(0);
                    break;

                default:
                    if (Jogada <= tabuleiroJogo.coluna){
                        printf("\nInsira o num da linha\n> ");
                        scanf(" %d", &Linha);
                        if (Linha <= tabuleiroJogo.linha){
                            if(JogadorRonda->PowerUps[0] < 1){
                                printf("\nQueres jogar pedra?\n1 - Sim\n2 - Nao\n> ");
                                scanf(" %d", &decisao);
                                switch (decisao) {
                                    case 1:
                                        JogadorRonda->PowerUps[0]++;
                                        JogadaCompletada = PreencheTabuleiro(tabuleiroJogo, Linha - 1, Jogada - 1, true, false);
                                        break;
                                    case 2:
                                        JogadaCompletada = PreencheTabuleiro(tabuleiroJogo, Linha - 1, Jogada - 1, false, false);
                                        break;
                                    default:
                                        printf("\nInput invalido!\n");
                                }
                            } else JogadaCompletada = PreencheTabuleiro(tabuleiroJogo, Linha - 1, Jogada - 1, false, false);
                        } else printf("\nInput invalido!\n");
                    } else printf("\nInput invalido!\n");
                    break;
            }
        } while (!JogadaCompletada);
        return tabuleiroJogo;
    } else { // SE FOR BOT
        do {
            JogadaBOT = intUniformRnd(1, 9);
            if (JogadaBOT == 9){
                if (JogadorRonda->PowerUps[1] < 2) {
                    xyBOT = intUniformRnd(1,3);
                    switch (xyBOT) {
                        case 1:
                            JogadorRonda->PowerUps[1]++;
                            NovoTabuleiroJogo = CriaNovoTabuleiro(tabuleiroJogo, 1);
                            //fprintf(stderr,"\naumentou...");
                            return NovoTabuleiroJogo;

                        case 2:
                            JogadorRonda->PowerUps[1]++;
                            NovoTabuleiroJogo = CriaNovoTabuleiro(tabuleiroJogo, 2);
                            return NovoTabuleiroJogo;

                        default:
                            JogadaCompletadaBOT = false;
                    }
                } else {
                    JogadaCompletadaBOT = false;
                }
            } else {
                if (JogadaBOT < tabuleiroJogo.coluna){
                    LinhaBOT = intUniformRnd(1, tabuleiroJogo.linha);
                    if (LinhaBOT < tabuleiroJogo.linha){
                        if(JogadorRonda->PowerUps[0] < 1){
                            decisaoBOT = intUniformRnd(1, 5);
                            if (decisaoBOT == 1) {
                                JogadaCompletadaBOT = PreencheTabuleiro(tabuleiroJogo, intUniformRnd(0, tabuleiroJogo.linha), intUniformRnd(0, tabuleiroJogo.coluna), true, true);
                                JogadorRonda->PowerUps[0]++;
                            } else {
                                JogadaCompletadaBOT = PreencheTabuleiro(tabuleiroJogo, intUniformRnd(0, tabuleiroJogo.linha), intUniformRnd(0, tabuleiroJogo.coluna), false, true);
                            }
                        } else JogadaCompletadaBOT = PreencheTabuleiro(tabuleiroJogo, intUniformRnd(0, tabuleiroJogo.linha), intUniformRnd(0, tabuleiroJogo.coluna), false, true);
                    } else JogadaCompletadaBOT = false;
                }
                else JogadaCompletadaBOT = false;
            }
        } while (!JogadaCompletadaBOT);
        return tabuleiroJogo;
    }

}

// --------------------------------------------------- JOGO

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

void NovoJogo(Player Player1, Player Player2, char FilenameF[TAMANHOX], TabuleiroStr tabuleiroJogo){

    initRandom(); // inicia o randomizer

    int QuemGanha = 0; // 0 = ninguem; 1 = P1; 2 = P2/PC
    int nRondas = 1; // nRondas inicial

    bool AcabouJogo = false; // Protege o jogo

    // CRIA FICHEIRO
    FILE * FicheiroJogo = CriaFicheiro(FilenameF);

    // FICHEIRO DO JOGO
    //FILE * Ficheiro;

    // Filename + txt para criar o ficheiro de texto

    // strncat(&FilenameF, ".txt", 1);
    //
    // printf("%s",&FilenameF);

    CriaTabuleiroInicial(tabuleiroJogo);

    printf("\n\nBom jogo! Diverte-te!\n");

    do {

        // PLAYER 1 NÃO BOT

        if(!JogoAcabado(tabuleiroJogo) && !Player1.isBot){
            printf("\n- !!! RONDA %d - TURNO DO JOGADOR %s !!! -", nRondas, Player1.UserName);
            ImprimeTabuleiro(tabuleiroJogo);
            ImprimeFicheiro(FicheiroJogo, tabuleiroJogo, nRondas);
            tabuleiroJogo = RecebeJogada(&Player1, tabuleiroJogo, false, &Player2);
            nRondas++;
            QuemGanha = 1;
        }

        // PLAYER 2 NÃO BOT

        if(!JogoAcabado(tabuleiroJogo) && !Player2.isBot){
            printf("\n- !!! RONDA %d - TURNO DO JOGADOR %s !!! -", nRondas, Player2.UserName);
            ImprimeTabuleiro(tabuleiroJogo);
            ImprimeFicheiro(FicheiroJogo, tabuleiroJogo, nRondas);
            tabuleiroJogo = RecebeJogada(&Player2, tabuleiroJogo, false, &Player1);
            nRondas++;
            QuemGanha = 2;
        }

        // getchar();

        // PLAYER 1 BOT

        if(!JogoAcabado(tabuleiroJogo) && Player1.isBot){
            printf("\n- !!! RONDA %d - TURNO DO BOT PLAYER 1 !!! -", nRondas);
            ImprimeTabuleiro(tabuleiroJogo);
            ImprimeFicheiro(FicheiroJogo, tabuleiroJogo, nRondas);
            tabuleiroJogo = RecebeJogada(&Player1, tabuleiroJogo, true, &Player2);
            nRondas++;
            QuemGanha = 1;
        }

        // PLAYER 2 BOT

        if(!JogoAcabado(tabuleiroJogo) && Player2.isBot){
            printf("\n- !!! RONDA %d - TURNO DO BOT PLAYER 2 !!! -", nRondas);
            ImprimeTabuleiro(tabuleiroJogo);
            ImprimeFicheiro(FicheiroJogo, tabuleiroJogo, nRondas);
            tabuleiroJogo = RecebeJogada(&Player2, tabuleiroJogo, true, &Player1);
            nRondas++;
            QuemGanha = 2;
        }

        // QUANDO O JOGO ACABA

        if (JogoAcabado(tabuleiroJogo)){
            printf("----- !!! ACABOU O JOGO !!! -----");
            ImprimeTabuleiro(tabuleiroJogo);
            ImprimeFicheiro(FicheiroJogo, tabuleiroJogo, nRondas);
            AcabouJogo = true;
            if (QuemGanha == 1){
                if (!Player1.isBot && Player2.isBot || !Player1.isBot && !Player2.isBot){
                    ImprimeVencedor(FicheiroJogo, Player1, nRondas, false);
                    printf("\n\nParabens %s! Ganhaste com %d rondas!", Player1.UserName, nRondas);
                } else {
                    ImprimeVencedor(FicheiroJogo, Player1, nRondas, true);
                    printf("\n\nO %s ganhou com %d rondas!", Player1.UserName, nRondas);
                }
            } else {
                if (!Player1.isBot && Player2.isBot) {
                    ImprimeVencedor(FicheiroJogo, Player2, nRondas, true);
                    printf("\n\nApos %d rondas, o BOT ganhou-te... Acho que devias refletir sobre isso...", nRondas);
                } else if (Player1.isBot && Player2.isBot){
                    ImprimeVencedor(FicheiroJogo, Player2, nRondas, true);
                    printf("\n\nApos %d rondas, o BOT %s GANHOU.", nRondas, Player2.UserName);
                } else {
                    ImprimeVencedor(FicheiroJogo, Player2, nRondas, false);
                    printf("\n\nParabens %s! Ganhaste com %d rondas!", Player2.UserName, nRondas);
                }
            }

        }

        getchar();

    } while (!AcabouJogo);

    fclose(FicheiroJogo);

    printf("\nFicheiro fechado com seguranca.");

    limparMemoriaTab(tabuleiroJogo);

    printf("\nMemoria limpa.");

    printf("\nAte a proxima!");

}

// --------------------------------------------------- MENUS

// MENU INICIAL

void menu(TabuleiroStr tabuleiroJogo){
    char inputMenu = '0';
    char inputMenu2 = '0';
    char Filename[TAMANHOX];
    //char FilenameOpen[TAMANHOX];
    bool avancar = false;
    bool avancar2 = false;
    char UserName1[TAMANHOX];
    char UserName2[TAMANHOX];

    MenuInicial();

    do {

        scanf(" %c", &inputMenu);
        getchar();

        switch (inputMenu) {

            case '1':
                do {
                    printf("\nQual o tipo de Jogo?\n1 - 1v1\n2 - 1vBOT\n3 - BOTvBOT\n> ");

                    scanf("%c", &inputMenu2);
                    getchar();

                    switch (inputMenu2) {
                        case '1':
                            avancar = true;
                            avancar2 = true;
                            printf("\nQual vai ser o nickname do Jogador A?\n> ");
                            scanf("%s", UserName1);
                            printf("\nQual vai ser o nickname do Jogador B?\n> ");
                            scanf("%s", UserName2);
                            printf("\nQual vai ser o nome do ficheiro?\n> ");
                            scanf("%s", Filename);
                            sprintf(Filename, "%s.txt", Filename);
                            NovoJogo(CriaJogador(UserName1, false), CriaJogador(UserName2, false), Filename, tabuleiroJogo);
                            break;

                        case '2':
                            avancar = true;
                            avancar2 = true;
                            printf("\nQual o teu nickname?\n> ");
                            scanf("%s", UserName1);
                            strcpy(UserName2,"BOT");
                            printf("\nQual vai ser o nome do ficheiro?\n> ");
                            scanf("%s", Filename);
                            sprintf(Filename, "%s.txt", Filename);
                            NovoJogo(CriaJogador(UserName1, false), CriaJogador(UserName2, true), Filename, tabuleiroJogo);
                            break;

                        case '3':
                            avancar = true;
                            avancar2 = true;
                            strcpy(UserName1,"BOT PLAYER 1");
                            strcpy(UserName2,"BOT PLAYER 2");
                            printf("\nQual vai ser o nome do ficheiro?\n> ");
                            scanf("%s", Filename);
                            sprintf(Filename, "%s.txt", Filename);
                            NovoJogo(CriaJogador(UserName1, true), CriaJogador(UserName2, true), Filename, tabuleiroJogo);
                            break;

                        default:
                            printf("\nInput invalido, tenta novamente!");
                    }

                } while (!avancar2);
                break;

            case '2':
                avancar = false;
                printf("\nQual o nome do ficheiro? (Coloca .txt no fim!)\n> ");
                gets(Filename);
                AbreFicheiro(Filename);
                getchar();
                MenuInicial();
                //getSaveGame();
                break;

            case '3':
                avancar = false;
                ComandoAjuda();
                break;

            case '9':
                FimDoJogo(1);

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

    TabuleiroStr TabuleiroJogoCont = CriaTabuleiro();

    Player Jog1 = CriaJogador("Jogador 1",false);

    Player Jog2 = CriaJogador("Jogador 2",false);

    char FileNameDef[TAMANHOX] = "FilenameDefault.txt";

    if (HaJogoAnterior) {
        do {
            printf("\nDeixou um jogo por completar!\nDeseja continuar ou voltar para o menu?\n\n1 - Continuar\n2 - Voltar ao menu\n> ");
            scanf(" %c", &inputMenu);
            if (inputMenu == '1') {
                avancar = true;
                ContinuaJogo(&TabuleiroJogoCont, &Jog1, &Jog2);
                NovoJogo(Jog1, Jog2, FileNameDef, TabuleiroJogoCont);
            } else if (inputMenu == '2') {
                avancar = true;
                menu(TabuleiroJogoCont);
            }
            else printf("\nInput invalido! Volte a tentar.");
        } while (avancar == false);
    } else menu(TabuleiroJogoCont);
}