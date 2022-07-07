#include "Tiro.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Funções	 auxiliares
void Print_Tab(char**);
int Escolhe_Coluna();
int Escolhe_Linha();
int Escolhe_Coluna_PC(int);
int Escolhe_Linha_PC(int);

//Funções para Registrar_Tiro
void Printar_Regra(int, char**, char**, int);
int Printar_Resultados(int, char**, char**, int);
void Tiro(char**, char**);
void Tiro_PC(char**, char**);
int VerificaTiro(char**, char **, int, int, int);
int Navios_afundados(char**, char**, int);
int NavioAfundou(char**, char**, int);
int VerificarAcertos(char**, char**, int);


//Começa sempre pelo player
void Registrar_Tiro(char** tab1, char** tab2, char** tiro_player, char** tiro_PC)
{
	int Vitoria = 0, First_Turn, count1=0, count2=0, i;
	while (Vitoria != 1)
	{
		//Player = 0
		Printar_Regra(0, tab1, tiro_player, count1);
		Tiro(tab2, tiro_player);
		i = 5;
		while (i>0)
		{
			count1 += Navios_afundados(tab2, tiro_player, i);
			i--;
		}
		Vitoria = Printar_Resultados(0, tab1, tiro_player, count1);
		//Não saia do loop, fiz essa gambiarra
		if(Vitoria == 1)
			break;



		//PC = 1
		//Printar_Regra(1, tab2, tiro_PC, count2);
		Tiro_PC(tab1, tiro_PC);
		i = 5;
		while (i>0)
		{
			count2 += Navios_afundados(tab1, tiro_PC, i);
			i--;
		}
		Vitoria = Printar_Resultados(1, tab2, tiro_PC, count2);
		if(Vitoria == 1)
			break;
	}
}

//A cada turno é printado as informações do que deve ser feito
void Printar_Regra(int first_turn, char** tab, char** tiro, int navioqty)
{
	printf("\n--Etapa de tiros ");
	if(first_turn == 0)
		printf("do Jogador--\n");
	else
		printf("do Computador--\n");
	Print_Tab(tab);
	printf("\n");
	printf("Marca os tiros da seguinte forma: O-agua X-fogo A-afundou\n\n");
	printf("Tabuleiro que registra os tiros\n");
	Print_Tab(tiro);
	printf("Navios Afundados = %d\n\n", navioqty);
	printf("Entre com as coordenadas dos tres tiros\n\n");
}

//Verifica se o jogador ou o PC ganhou
int Printar_Resultados(int escolhido, char** tab, char** tiro, int afundados)
{
	int flag=0;
	if(escolhido == 0)
		printf("jogador\n");
	else
		printf("Computador\n");
	Print_Tab(tab);
	printf("\n");			
	Print_Tab(tiro);
	printf("Navios Afundados = %d\n\n",afundados);
	
	if(afundados==5)
	{
		flag=1;
		if(escolhido == 0)
			printf("O jogador ganhou\n");
		else
			printf("O computador ganhou\n");
	}
	return flag;	
}

//Colocar escolha para o pc, usar if else;
//Registra os tiros do jogador
void Tiro(char** tab, char** tiro)
{
	int count=0, x, y, teste;
	while (count < 3)
	{
		printf("Tiro %d\n", count+1);
		x = Escolhe_Linha();
		y = Escolhe_Coluna();
		teste = VerificaTiro(tiro, tab, x, y, 0);
		if(teste == 1)
			count++;
	}

	return;	
}

//Registra os tiros do PC
void Tiro_PC(char** tab, char** tiro)
{
	int count=0, x, y, teste;
	srand(time(NULL));
	while (count<3)
	{
		x = Escolhe_Linha_PC(10);
		y = Escolhe_Coluna_PC(10);
		teste = VerificaTiro(tiro, tab, x, y, 1);
		if(teste == 1)
			count++;
	}
	
}

//Verifica se a posição escolhida ainda não foi usada
int VerificaTiro(char** tiro, char ** nav, int lin, int col, int escolhido)
{
	int teste=0;
	switch(escolhido)
	{
		case 0:
			if(!((tiro[lin][col]=='A')||(tiro[lin][col]=='X')||(tiro[lin][col]=='O')))
			{
				if(nav[lin][col]=='-')
					tiro[lin][col]='O';
				else
					tiro[lin][col]='X';
				teste=1;
			}

			else
					printf("Posicao ocupada - tente novamente\n");
			break;

		case 1:
			if(!((tiro[lin][col]=='A')||(tiro[lin][col]=='X')||(tiro[lin][col]=='O')))
			{
				if(nav[lin][col]=='-')
					tiro[lin][col]='O';
				else
					tiro[lin][col]='X';
				teste=1;
			}
			break;
		
		default:
			break;
	}
  return teste;
}

// Tab é o tabuleiro do adversário
//Conta a quantidade de navios afundados
int Navios_afundados(char** tab, char** tiro, int navio)
{
	int count = 0, navio_afundado=0;
	count = VerificarAcertos(tab, tiro, navio);
	switch(navio)
	{
		case 5:
			if(count == 5)
				navio_afundado = NavioAfundou(tab, tiro, count);
			break;

		case 4:
			if(count == 4)
				navio_afundado = NavioAfundou(tab, tiro, count);
			break;

		case 3: 
			if(count == 3)
				navio_afundado = NavioAfundou(tab, tiro, count);
			break;

		case 2:
			if(count == 2)
				navio_afundado = NavioAfundou(tab, tiro, count);
			break;

		case 1:
			if(count == 1)
				navio_afundado = NavioAfundou(tab, tiro, count);
			break;

		default:
			break;
	}
	//printf("navio_afundado = %d, navio = %d\n", navio_afundado, navio);
	return navio_afundado;
}

//Conta quantos tiros um determinado navio levou, retorna um inteiro equivalente a quantidade de acertos ao navio;
int VerificarAcertos(char **nav, char** tiro, int tiponav)
{
    int count=0;
		char navios[] = "DSCGP";
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if(nav[i][j] == navios[tiponav-1] && tiro[i][j] == 'X')
						{
							//printf("%c\n", navios[tiponav-1]);
              count++;
						}
        }
    }
		if(tiponav == 2 && count == 3)
			return count = 2;
		else if(tiponav == 1 && count == 2)
			return count = 1;
		//printf("count = %d, tiponav = %d\n", count, tiponav);
    return count;
}

//No tabuleiro de tiros, substitui o X por A, indicando que o navio foi afundado, retorna a quantidade de navios afundados
int NavioAfundou(char** nav, char** tiro, int tiponavio)
{
    int lin, col, navafund=0;;
    switch (tiponavio)
    {
    case 5:
        for(lin=0;lin<10;lin++)
				{
					for(col=0;col<10;col++)
					{
						if(nav[lin][col]=='P')
							tiro[lin][col]='A';
					}
				}	
				navafund=1;
        break;
    
    case 4:
        for(lin=0;lin<10;lin++)
				{
					for(col=0;col<10;col++)
					{
						if(nav[lin][col]=='G')
							tiro[lin][col]='A';
					}
				}
				navafund=1;
        break;

    case 3:
        for(lin=0;lin<10;lin++)
				{
					for(col=0;col<10;col++)
					{
						if(nav[lin][col]=='C')
							tiro[lin][col]='A';
					}
				}	
				navafund=1;
        break;

    case 2:
        for(lin=0;lin<10;lin++)
				{
					for(col=0;col<10;col++)
					{
						if(nav[lin][col]=='S')
							tiro[lin][col]='A';
					}
				}
				navafund=1;
        break;

    case 1:
        for(lin=0;lin<10;lin++)
				{
					for(col=0;col<10;col++)
					{
						if(nav[lin][col]=='D')
							tiro[lin][col]='A';
					}
				}
				navafund=1;
        break;


    default:
        break;
    }

		//printf("tiponavio = %d, navafund = %d\n", tiponavio, navafund);
    return navafund;
}