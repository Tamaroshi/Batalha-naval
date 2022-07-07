#include <stdio.h>
#include <stdlib.h>
#include "PC.h"
#include "Player.h"
#include "Tiro.h"

//Funções Principais
char** Criar_Tab();
void Free_Tab(char**);
void Print_Tab(char**);

//Funções Principais dos headers
/*
//Função para fazer posicionamento dos navios do computador;
void Posicionar_navio_PC(char**);

//Função para fazer o posicionamento dos navios do jogador
void Posicionar_navio(char**);

//Função para registrar os tiros do jogador e computador
void Registrar_Tiro(char**, char**, char**, char**);
*/

int main()
{
    char** P1 = Criar_Tab();
    char** PC = Criar_Tab();
    char** tiro_player = Criar_Tab();
	char** tiro_pc = Criar_Tab();

    Posicionar_navio(P1);
	Posicionar_navio_PC(PC);
	Registrar_Tiro(P1, PC, tiro_player, tiro_pc);

    Free_Tab(P1);
	Free_Tab(PC);
	Free_Tab(tiro_player);
	Free_Tab(tiro_pc);

    return 0;
}

//Aloca memória dinamicamente para os tabuleiros
char** Criar_Tab()
{
    char** novo = (char**)malloc(10*sizeof(char*));
    for (int i = 0; i < 10; i++)
        novo[i] = (char*)malloc(10*sizeof(char));

    if(novo!=NULL)
    {
        for (int x = 0; x < 10; x++)
        {
            for (int z = 0; z < 10; z++)
                novo[x][z] = '-';
        }
    }
    return novo;
}

//Libera a memória alocada dinamicamente
void Free_Tab(char** novo)
{
    for (int i = 0; i < 10; i++)
        free(novo[i]);
    free(novo);
}

//Printa o tabuleiro
//Coloquei as linhas de 0-9 por estética.
void Print_Tab(char** novo)
{
	printf("   A B C D E F G H I J\n");
    for(int i = 0; i < 10; i++)
    {
        printf("%d  ", i);
        for (int j = 0; j < 10; j++)
        {
            printf("%c ", novo[i][j]);
            if(j == 9)
                printf("\n");
        }
    }
}