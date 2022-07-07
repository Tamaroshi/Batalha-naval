#include "Player.h"
#include <stdio.h>

//Auxiliar 
void Print_Tab(char**);

//Auxiliares da função Posicionar_navio
int Escolhe_Coluna();
int Escolhe_Linha();
int Escolhe_TipoNav();
int Escolhe_Orient();
int switch_Coluna(int);
int Preencher_Tab(int, int, int, int, char**);
int Verificar_coordenada(int, int, int, int, char**);
int Verificar_coordenada_altera(int,int, int);
void PreencherHorizontal(int, int, int, char**);
void PreencherVertical(int, int, int, char**);

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
		printf("\n");
}

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
		printf("\nEntre com o tipo de navio: 5-porta aviao 4-navio de guerra 3-cruzador 2-submarino 1-destruidor: ");
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
    int Vlinha, Vcoluna, count=0;
    //Conta linha
    if(orientacao == 0)
    {
        Vlinha = Verificar_coordenada(linha, coluna, tiponav, orientacao, tab);
        Vcoluna = Verificar_coordenada_altera(coluna, orientacao, tiponav);
        if (Vlinha == 0)
            printf("posicao ocupada por outro Navio\n");

        else if (Vlinha!=0 && Vcoluna!=0)
        {
            PreencherHorizontal(linha, coluna, tiponav, tab);
            count=1;
        }
    }
    //Conta coluna
    else
    {
      Vlinha = Verificar_coordenada_altera(linha, orientacao, tiponav);
      Vcoluna = Verificar_coordenada(linha, coluna, tiponav, orientacao, tab);
      if(Vcoluna == 0)
      	printf("posicao ocupada por outro Navio\n");
        
      else if (Vcoluna != 0 && Vlinha != 0)
      {
        PreencherVertical(linha, coluna, tiponav, tab);
        count=1;
      }
    }

    return count;
}

//Verifica se a linha escolhida pelo usuário não está ocupada, caso esteja devolve 0, 1 se não estiver ocupada.
int Verificar_coordenada(int lin, int col, int tiponav, int d, char **tab)
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

//Retorna 0 se o tiponav n caber no tabuleiro na horizontal ou vertical. 1 se couber 
int Verificar_coordenada_altera(int altera, int orientacao, int tiponav)
{
	int flag = 1;
	switch (tiponav)
	{
	case 5:
		if(altera > 5)
		{
      if(orientacao == 0)
			  printf("Porta aviao ficou fora do tabuleiro so pode usar linha de 1-5\n");
      else
        printf("Porta aviao ficou fora do tabuleiro so pode usar A-F\n");

			flag = 0;
		}
        break;
    
    case 4:
        if(altera>6)
		{
			if(orientacao == 0)
			  printf("Navio de Guerra ficou fora do tabuleiro so pode usar linha 1-6\n");
      else
        printf("Navio de Guerra ficou fora do tabuleiro so pode usar A-G\n");
			flag = 0;
		}
        break;
    case 3:
        if(altera>7)
		{
			if(orientacao == 0)
			  printf("Cruzador ficou fora do tabuleiro so pode usar linha de 1-7\n");
      else
        printf("Submarino ficou fora do tabuleiro so pode usar A-H\n");
			flag = 0;
		}
        break;
    case 2:
		if(altera>7)
		{
			if(orientacao == 0)
			  printf("Cruzador ficou fora do tabuleiro so pode usar linha de 1-7\n");
      else
        printf("Submarino ficou fora do tabuleiro so pode usar A-H\n");
			flag = 0;
		}
        break;
    case 1:
      if(altera==9)
		  {
			if(orientacao == 0)
			  printf("Destruidor ficou fora do tabuleiro so pode usar linha de 1-8\n");
      else
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
