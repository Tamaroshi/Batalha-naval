#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "PC.h"


char** Criar_Tab();
void Free_Tab(char**);
void Print_Tab(char**);
int Escolhe_Coluna_PC(int);
int Escolhe_Linha_PC(int);
int Escolhe_Orient_PC();
int Preencher_Tab_PC(int, int, int, int, char**);
int Verificar_escolha(int, int, int, int, char**);
void PreencherHorizontal_PC(int, int, int, char**);
void PreencherVertical_PC(int, int, int, char**);

void Posicionar_navio_PC(char** tab)
{
    int i = 0, x, y, tiponav, d, verificar;
    srand(time(NULL));
    while(i<5)
    {
        tiponav = i+1;
        //printf("tiponav = %d\n", tiponav);
        d = Escolhe_Orient_PC();
        //printf("d = %d\n", d);
        switch(tiponav)
        {
            case 5:
                if(d == 0)
                {
                    x = Escolhe_Linha_PC(10);
                    //printf("x = %d\n", x);
                    y = Escolhe_Coluna_PC(6);
                    //printf("y = %d\n", y);
                    i += Preencher_Tab_PC(x, y, tiponav, d, tab);
                }

                else
                {
                    x = Escolhe_Linha_PC(6);
                    //printf("x = %d\n", x);
                    y = Escolhe_Coluna_PC(10);
                    //printf("y = %d\n", y);
                    i += Preencher_Tab_PC(x, y, tiponav, d, tab);
                }

                break;
                
            case 4:
                if(d == 0)
                {
                    x = Escolhe_Linha_PC(10);
                    //printf("x = %d\n", x);
                    y = Escolhe_Coluna_PC(7);
                    //printf("y = %d\n", y);
                    i += Preencher_Tab_PC(x, y, tiponav, d, tab);
                }

                else
                {
                    x = Escolhe_Linha_PC(7);
                    //printf("x = %d\n", x);
                    y = Escolhe_Coluna_PC(10);
                    //printf("y = %d\n", y);
                    i += Preencher_Tab_PC(x, y, tiponav, d, tab);
                }
                break;
                
            case 3:
                if(d == 0)
                {
                    x = Escolhe_Linha_PC(10);
                    //printf("x = %d\n", x);
                    y = Escolhe_Coluna_PC(8);
                    //printf("y = %d\n", y);
                    i += Preencher_Tab_PC(x, y, tiponav, d, tab);
                }

                else
                {
                    x = Escolhe_Linha_PC(8);
                    //printf("x = %d\n", x);
                    y = Escolhe_Coluna_PC(10);
                    //printf("y = %d\n", y);
                    i += Preencher_Tab_PC(x, y, tiponav, d, tab);
                }
                break;
                
            case 2:
                if(d == 0)
                {
                    x = Escolhe_Linha_PC(10);
                    //printf("x = %d\n", x);
                    y = Escolhe_Coluna_PC(8);
                    //printf("y = %d\n", y);
                    i += Preencher_Tab_PC(x, y, tiponav, d, tab);
                }

                else
                {
                    x = Escolhe_Linha_PC(8);
                    //printf("x = %d\n", x);
                    y = Escolhe_Coluna_PC(10);
                    //printf("y = %d\n", y);
                    i += Preencher_Tab_PC(x, y, tiponav, d, tab);
                }
                break;
                
            case 1:
                if(d == 0)
                {
                    x = Escolhe_Linha_PC(10);
                    //printf("x = %d\n", x);
                    y = Escolhe_Coluna_PC(10);
                    //printf("y = %d\n", y);
                    i += Preencher_Tab_PC(x, y, tiponav, d, tab);
                }

                else
                {
                    x = Escolhe_Linha_PC(10);
                    //printf("x = %d\n", x);
                    y = Escolhe_Coluna_PC(10);
                    //printf("y = %d\n", y);
                    i += Preencher_Tab_PC(x, y, tiponav, d, tab);
                }
                break;
                
            default:
                break;
        }
    }
    printf("       Computador\n");
    Print_Tab(tab);
}

int Escolhe_Coluna_PC(int a)
{
    int col;
    col = rand()%a;
    return col;
}

int Escolhe_Linha_PC(int a)
{
    int lin;
    lin = rand()%a;
    return lin;
}

int Escolhe_Orient_PC()
{
    int o;
    o = rand()%2;
    return o;
}

//Preenche o tabuleiro
int Preencher_Tab_PC(int linha, int coluna, int tiponav, int orientacao, char** tab)
{
    int flag, count=0;
    //Conta linha
    if(orientacao == 0)
    {
        flag = Verificar_escolha(linha, coluna, tiponav, orientacao, tab);
        if(flag == 1)
        {
            PreencherHorizontal_PC(linha, coluna, tiponav, tab);
            count++;
        }
    }

    //Conta coluna
    else
    {
        flag = Verificar_escolha(linha, coluna, tiponav, orientacao, tab);
        if(flag == 1)
        {
            PreencherVertical_PC(linha, coluna, tiponav, tab);
            count++;
        }
    } 

    return count;
}

//Verifica se a linha/coluna escolhida pelo usuário não está ocupada, caso esteja devolve 0, 1 se não estiver ocupada.
int Verificar_escolha(int lin, int col, int tiponav, int d, char **tab)
{
    int flag=1, i, j;
	switch (tiponav)
	{
	case 5:
		i=5;
        break;
    
    case 4:
        i=4;
        break;
    case 3:
        i=3;
        break;
    case 2:
		i=3;
        break;
    case 1:
        i=2;
        break;
    default:
        break;
    }

    if(d == 0)
    {
        for(j=0;j<i;j++)
        {
            if(tab[lin][col+j]!='-')
                flag=0;
        }
    }

    else
    {
        for(j=0;j<i;j++)
	    {
		    if(tab[lin+j][col]!='-')
			    flag=0;
	    }
    }

    return flag;
}

//Preenche o Tabuleiro na Horizontal
void PreencherHorizontal_PC(int lin, int col, int tiponav, char** nav)
{
    switch (tiponav)
    {
    case 5:
        for(int j=0;j<5;j++)
			nav[lin][col+j]='P';
		//printf("Tabuleiro do jogador\n");
		//Print_Tab(nav);
        break;
    
    case 4:
        for(int j=0;j<4;j++)
			nav[lin][col+j]='G';
		//printf("Tabuleiro do jogador\n");
		//Print_Tab(nav);
        break;
    case 3:
        for(int j=0;j<3;j++)
			nav[lin][col+j]='C';
		//printf("Tabuleiro do jogador\n");
		//Print_Tab(nav);
        break;
    case 2:
        for(int j=0;j<3;j++)
			nav[lin][col+j]='S';
		//printf("Tabuleiro do jogador\n");
		//Print_Tab(nav);
        break;
    case 1:
        for(int j=0;j<2;j++)
			nav[lin][col+j]='D';
		//printf("Tabuleiro do jogador\n");
		//Print_Tab(nav);
        break;
    default:
        break;
    }
}

//Preenche o Tabuleiro na Vertical
void PreencherVertical_PC(int lin, int col, int tiponav, char** nav)
{
    switch (tiponav)
    {
    case 5:
        for(int j=0;j<5;j++)
			nav[lin+j][col] = 'P';
		//printf("Tabuleiro do jogador\n");
		//Print_Tab(nav);
        break;
    
    case 4:
        for(int j=0;j<4;j++)
			nav[lin+j][col] = 'G';
		//printf("Tabuleiro do jogador\n");
		//Print_Tab(nav);

        break;
    case 3:
        for(int j=0;j<3;j++)
			nav[lin+j][col] = 'C';
		//printf("Tabuleiro do jogador\n");
		//Print_Tab(nav);
        break;
    case 2:
        for(int j=0;j<3;j++)
			nav[lin+j][col] = 'S';
		///printf("Tabuleiro do jogador\n");
		//Print_Tab(nav);
        break;
    case 1:
        for(int j=0;j<2;j++)
			nav[lin+j][col] = 'D';
		//printf("Tabuleiro do jogador\n");
		//Print_Tab(nav);
        break;
    default:
        break;
    }
}
