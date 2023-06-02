//jogodavelha.c
//Trabalho I da matéria de ICC 1 - professor Jó Ueyama
//feito pelo aluno Renan Correia Monteiro Soares - 14605661
//data de entrega do trabalho: 02/06/2023

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

char tab[3][3] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
bool controle = 1;
char vencedor;


void mostra_velha(){
    /*--------------------------------------------------------------------------
      -função mostra_velha
      -sem parâmetros
      -sem retorno
      -mostra o tabuleiro do jogo
    --------------------------------------------------------------------------*/
    printf("\n");
    printf("   1   2   3\n");
    for(int i=0; i<3; i++){
        printf("%d  %c | %c | %c\n", i+1, tab[i][0], tab[i][1], tab[i][2]);
    }
    printf("\n");
}


bool verifica_jogador(char entrada){
    /*--------------------------------------------------------------------------
      -função verifica_jogador.
      -recebe como parâmetro a informação sobre quem está jogando,recebido na
    entrada.
      -retorna true se a entrada for válida.
      -a entrada é válida se o jogador for 'O' ou 'X', e ainda deve ser diferente
    do jogador anterior.
    --------------------------------------------------------------------------*/
    static char entrada_anterior;

    if((entrada=='X' || entrada=='O') && (entrada != entrada_anterior)){
        entrada_anterior = entrada;
        return 1;
    }
    else{return 0;}
}


bool verifica_posicao(int linha, int coluna){
    /*--------------------------------------------------------------------------
      -função verifica_posição.
      -recebe como argumento as duas posições recebidas na entrada.
      -retorna 1 se a posição for válida, e 0 caso contrário.
      -verifica se o número está dentro do limite da tabela e também verifica se
    a posição está ocupada ou não.
    --------------------------------------------------------------------------*/

    if(linha > 2 || coluna > 2){return 0;}
    else if(linha < 0 || coluna < 0){return 0;}

    else if(tab[linha][coluna] == 'X' || tab[linha][coluna] == 'O'){return 0;}

    else{return 1;}
}


bool verifica_velha(){
    /*--------------------------------------------------------------------------
      -função verifica_velha.
      -não recebe argumento.
      -retorna 1 se as condições de fim de jogo forem satisfeitas, 0 caso não.
      -modifica a variável global "vencedor"
    --------------------------------------------------------------------------*/

    static int rodada = 0;
    rodada++;

    //conferindo linhas
    for(int i=0; i<3; i++){
        //conferindo horizontais
        if(tab[i][0] == 'X' && tab[i][1] == 'X' && tab[i][2] == 'X'){
            vencedor = 'X';
            return 0;
        }
        if(tab[i][0] == 'O' && tab[i][1] == 'O' && tab[i][2] == 'O'){
            vencedor = 'O';
            return 0;
        }
        //conferindo verticais
        if(tab[0][i] == 'X' && tab[1][i] == 'X' && tab[2][i] == 'X'){
            vencedor = 'X';
            return 0;
        }
        if(tab[0][i] == 'O' && tab[1][i] == 'O' && tab[2][i] == 'O'){
            vencedor = 'O';
            return 0;
        }
    }
    //conferindo diagonais
    if(tab[0][0] == 'X' && tab[1][1] == 'X' && tab[2][2] == 'X'){
        vencedor = 'X';
        return 0;
    }
    if(tab[0][0] == 'O' && tab[1][1] == 'O' && tab[2][2] == 'O'){
        vencedor = 'O';
        return 0;
    }
    if(tab[0][2] == 'X' && tab[1][1] == 'X' && tab[2][0] == 'X'){
        vencedor = 'X';
        return 0;
    }
    if(tab[0][2] == 'O' && tab[1][1] == 'O' && tab[2][0] == 'O'){
        vencedor = 'O';
        return 0;
    }

    //deu velha se apoś 9 rodadas ainda n tiver vencedor
    if(rodada==9){
        vencedor = 'v';
        return 0;
    }

    //retorna 1 se nenhuma condição foi satisfeita
    return 1;
}


int main(){
    printf("BEM VINDO AO JOGO DA VELHA!!!!!\n");

    while(controle){
        char jogador = ' ';
        int posicao_linha = 0;
        int posicao_coluna = 0;

        mostra_velha();

        //entrada dos dados
        printf("vez de qual jogador? ");
        scanf("%c", &jogador);
        setbuf(stdin, NULL);

        printf("qual a posicao da linha? ");
        scanf("%d", &posicao_linha);
        setbuf(stdin, NULL);

        printf("qual a posicao da coluna? ");
        scanf("%d", &posicao_coluna);
        setbuf(stdin, NULL);

        system("cls");

        /*verifica se o jogador e as posições colocadas são válidas.
        Se não, printará uma mensagem e pulará uma iteração, voltando ao inicio
        do while.*/

        /*primeiro se verifica a posição, pois assim a variavel entrada_anterior
        não será modificada indevidamente*/

        if(verifica_posicao(posicao_linha-1, posicao_coluna-1)){
          if(verifica_jogador(jogador)){
            tab[posicao_linha-1][posicao_coluna-1] = jogador;
            printf("\n");
          }
          else{
              printf("ENTRADA INVALIDA, TENTE NOVAMENTE\n\n");
              continue;
          }
        }

        else{
            printf("ENTRADA INVALIDA, TENTE NOVAMENTE\n");
            continue;
        }

        //vai receber 0 se o jogo acabar ou 1 para continuar
        controle = verifica_velha();

        //fim do while
    }

    //finalização do programa
    if(vencedor == 'v'){
        printf("O JOGO ACABOU\nDEU VELHA\n");
    }
    else{
        printf("O JOGO ACABOU\nO JOGADOR \"%c\" VENCEU\n", vencedor);
    }

    mostra_velha();

    return 0;
}
