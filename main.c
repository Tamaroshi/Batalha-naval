#include <stdio.h>
#include "PC.h"

//Funções Principais
char** Criar_Tab();
void Free_Tab(char**);
void Print_Tab(char**);
void Posicionar_navio(char**);
void Registrar_Tiro(char**, char**, char**, char**);

//Auxiliar de Posicionar_navio
int Escolhe_Coluna();
int Escolhe_Linha();
int Escolhe_TipoNav();
int Escolhe_Orient();
int switch_Coluna(int);
int Preencher_Tab(int, int, int, int, char**);
int AuxVerificarLinha(int, int, int, char**);
int VerificarColuna(int, int);
void PreencherHorizontal(int, int, int, char**);
void PreencherVertical(int, int, int, char**);
int AuxVerificarColuna(int, int, int, char**);
int VerificarLinha(int, int);

int main()
{
    char** P1 = Criar_Tab();
    char** PC = Criar_Tab();
	//char** tiro_player = Criar_Tab();
	//char** tiro_pc = Criar_Tab();
    Posicionar_navio(P1);
	Posicionar_navio_PC(PC);
	//Registrar_Tiro(P1, PC, tiro_player, tiro_pc);

    Free_Tab(P1);
	Free_Tab(PC);
	//Free_Tab(tiro_player);
	//Free_Tab(tiro_pc);

    return 0;
}

//Aloca memória dinamicamente ao tabuleiro
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
    {
        free(novo[i]);
    }
    free(novo);
}

//Printa o tabuleiro
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

//Posiciona os navios do jogador
void Posicionar_navio(char** tab)
{
    int i = 0, x, y, tiponav, d;
    printf("Tabuleiro do jogador\n");
    Print_Tab(tab);
    while (i != 5)
    {
        tiponav = Escolhe_TipoNav();
        x = Escolhe_Linha();
        y = Escolhe_Coluna();
        d = Escolhe_Orient();
        i += Preencher_Tab(x, y, tiponav, d, tab);
    }
}


//Auxiliares da função Posicionar_navio
//Pede ao usuário a posição coluna
int Escolhe_Coluna()
{
	char coluna;
	int sinal1=0, b;
	while(sinal1!=1)
	{
		printf("Entre com a coluna = ");
		scanf("%s",&coluna);
		printf("\n");
		if(coluna >= 65 && coluna <= 74 || coluna >= 97 && coluna <= 106)
			sinal1=1;
		else
			printf("Coluna invalida - Entre coluna novamente\n");
	}
    b = switch_Coluna(coluna);
	return b;
}

//Retorna o valor da coluna a partir de um char entre A e J ou a e j.
int switch_Coluna(int alfa)
{
	int col;
	switch (alfa)
	{
	case 65:
	case 97:
		col = 0;
		break;
	
	case 66:
	case 98:
		col = 1;
		break;
	
	case 67:
	case 99:
		col = 2;
		break;
	
	case 68:
	case 100:
		col = 3;
		break;
	
	case 69:
	case 101:
		col = 4;
		break;
	
	case 70:
	case 102:
		col = 5;
		break;
	
	case 71:
	case 103:
		col = 6;
		break;

	case 72:
	case 104:
		col = 7;
		break;
		
	case 73:
	case 105:
		col = 8;
		break;
	
	case 74:
	case 106:
		col = 9;
		break;
	

	default :
		break;
	}

	return col;
}

//Pede ao usuário a posição linha
int Escolhe_Linha()
{
	int linha;
	int sinal=0;
	while(sinal!=1)
	{
		printf("Entre com a linha = ");
		scanf("%d",&linha);
		if(linha<=9&&linha>=0)
			sinal=1;
		else
			printf("Linha invalida - Entre linha novamente\n");
	}
	return linha;
}

//Pede ao usuário o tipo do navio a ser colocado
int Escolhe_TipoNav()
{
	char tiponav;
	int sinal2=0;
	while(sinal2!=1)
	{
		printf("\nEntre com o tipo de navio: 5-porta aviao 4-navio de guerra 3-cruzador 2-submarino 1-destruidor\n");
		scanf("%d", &tiponav);
		printf("\n");
		if(tiponav>= 1 && tiponav <= 5)
			sinal2=1;
		else
			printf("Navio invalido - Entre navio novamente\n");
	}
	return tiponav;
}

//Pede ao usuário a orientação do navio
int Escolhe_Orient()
{
    int direcao;
    printf("Entre com a direcao: 0-horizontal 1-vertical\n");
	scanf("%d", &direcao);
	printf("\n");
    return direcao;
}

//Preenche o tabuleiro
int Preencher_Tab(int linha, int coluna, int tiponav, int orientacao, char** tab)
{
    int Vlinha, Vlinha2, Vcoluna, Vcoluna2, count=0;

    //Conta linha
    if(orientacao == 0)
    {
        Vlinha = AuxVerificarLinha(linha, coluna, tiponav, tab);
        Vcoluna = VerificarColuna(coluna, tiponav);
        if (Vlinha == 0)
            printf("posicao ocupada por outro Navio\n");

        else if (Vlinha!=0 && Vcoluna!=0)
        {
            PreencherHorizontal(linha, coluna, tiponav, tab);
            count=1;
        }
    }

    //Conta coluna
    else if(orientacao == 1)
    {
        Vcoluna2 = AuxVerificarColuna(linha, coluna, tiponav, tab);
        Vlinha2 = VerificarLinha(linha, tiponav);
        if(Vcoluna == 0)
		{
			printf("Entrou \n");
			printf("Vlinha2 = %d, Vcoluna2 = %d\n", Vlinha2, Vcoluna2);

            printf("posicao ocupada por outro Navio\n");
		}
        
        else if (Vcoluna!=0 && Vlinha!=0)
        {
            PreencherVertical(linha, coluna, tiponav, tab);
            count=1;
        }
    }

    return count;
}

//Verifica se a linha escolhida pelo usuário não está ocupada, caso esteja devolve 0, 1 se não estiver ocupada.
int AuxVerificarLinha(int lin, int col, int tiponav, char **tab)
{
    int flag=1, i;
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

    for(int j=0;j<i;j++)
	{
		if(tab[lin][col+j]!='-')
			flag=0;
	}
    return flag;
}

//Retorna 0 se o tiponav n caber no tabuleiro, na horizontal. 1 se couber
int VerificarColuna(int col, int tiponav)
{
	int flag = 1;
	switch (tiponav)
	{
	case 5:
		if(col > 5)
		{
			printf("Porta aviao ficou fora do tabuleiro so pode usar A-F\n");
			flag = 0;
		}
        break;
    
    case 4:
        if(col>6)
		{
			printf("Navio de Guerra ficou fora do tabuleiro so pode usar A-G\n");
			flag = 0;
		}
        break;
    case 3:
        if(col>7)
		{
			printf("Cruzador ficou fora do tabuleiro so pode usar A-H\n");
			flag = 0;
		}
        break;
    case 2:
		if(col>7)
		{
			flag = 0;
			printf("Submarino ficou fora do tabuleiro so pode usar A-H\n");
		}
        break;
    case 1:
        if(col==9)
		{
			printf("Destruidor ficou fora do tabuleiro so pode usar A-I\n");
			flag = 0;
		}
        break;
    default:
        break;
    }
	return flag;
}

//Preenche o Tabuleiro na Horizontal
void PreencherHorizontal(int lin, int col, int tiponav, char** nav)
{
    switch (tiponav)
    {
    case 5:
        for(int j=0;j<5;j++)
			nav[lin][col+j]='P';
		printf("Tabuleiro do jogador\n");
		Print_Tab(nav);
        break;
    
    case 4:
        for(int j=0;j<4;j++)
			nav[lin][col+j]='G';
		printf("Tabuleiro do jogador\n");
		Print_Tab(nav);
        break;
    case 3:
        for(int j=0;j<3;j++)
			nav[lin][col+j]='C';
		printf("Tabuleiro do jogador\n");
		Print_Tab(nav);
        break;
    case 2:
        for(int j=0;j<3;j++)
			nav[lin][col+j]='S';
		printf("Tabuleiro do jogador\n");
		Print_Tab(nav);
        break;
    case 1:
        for(int j=0;j<2;j++)
			nav[lin][col+j]='D';
		printf("Tabuleiro do jogador\n");
		Print_Tab(nav);
        break;
    default:
        break;
    }
}

//Verifica se a coluna escolhida pelo usuário nãoe está ocupada, caso esteja devolve 0, 1 se não estiver ocupada.
int AuxVerificarColuna(int lin, int col, int tiponav, char** nav)
{
    int flag=1, i=0;
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
    for(int j=0;j<i;j++)
	{
		if(nav[lin+j][col]!='-')
			flag=0;
	}
    return flag;
}

//Retorna 0 se o tiponav n caber no tabuleiro, na Vertical. 1 se couber 
int VerificarLinha(int linha, int tiponav)
{
	int flag = 1;
	switch (tiponav)
	{
	case 5:
		if(linha > 5)
		{
			printf("Porta aviao ficou fora do tabuleiro so pode usar linha de 1-6\n");
			flag = 0;
		}
        break;
    
    case 4:
        if(linha>6)
		{
			printf("Navio de Guerra ficou fora do tabuleiro so pode usar linha 1=7\n");
			flag = 0;
		}
        break;
    case 3:
        if(linha>7)
		{
			printf("Cruzador ficou fora do tabuleiro so pode usar linha de 1-7\n");
			flag = 0;
		}
        break;
    case 2:
		if(linha>7)
		{
			printf("Submarino ficou fora do tabuleiro so pode usar linha de 1-7\n");
			flag = 0;
		}
        break;
    case 1:
        if(linha==9)
		{
			printf("Destruidor ficou fora do tabuleiro so pode usar linha de 1-8\n");
			flag = 0;
		}
        break;
    default:
        break;
    }
	return flag; 
}

//Preenche o Tabuleiro na Vertical
void PreencherVertical(int lin, int col, int tiponav, char** nav)
{
    switch (tiponav)
    {
    case 5:
        for(int j=0;j<5;j++)
			nav[lin+j][col] = 'P';
		printf("Tabuleiro do jogador\n");
		Print_Tab(nav);
        break;
    
    case 4:
        for(int j=0;j<4;j++)
			nav[lin+j][col]='G';
		printf("Tabuleiro do jogador\n");
		Print_Tab(nav);

        break;
    case 3:
        for(int j=0;j<3;j++)
			nav[lin+j][col]='C';
		printf("Tabuleiro do jogador\n");
		Print_Tab(nav);
        break;
    case 2:
        for(int j=0;j<3;j++)
			nav[lin+j][col]='S';
		printf("Tabuleiro do jogador\n");
		Print_Tab(nav);
        break;
    case 1:
        for(int j=0;j<2;j++)
			nav[lin+j][col]='D';
		printf("Tabuleiro do jogador\n");
		Print_Tab(nav);
        break;
    default:
        break;
    }
}
