#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef int bool;
#define true 1
#define false 0

/****************************
 * 		NUMERO DE VARIÁVEIS	*
 ***************************/
int NUMERO_DE_VARIAVEIS;

/****************************************************
 * 	MARCA SE JÁ FOI FEITO A CONTAGEM DE VARIÁVEIS	*
 ***************************************************/
int CONTAGEM_DE_VARIAVEIS_FEITO;


/****************************
 * 		NUMERO DE ENTRADAS	*
 ***************************/
int NUMERO_ENTRADAS;



/*******************************
 *	NOME DO ARQUIVO DE ENTRADA *
 *******************************/
char * ARQUIVO_ENTRADA;



/***********************************
 *	DADOS DE ENTRADA DA REDE NEURAL*
 **********************************/
char * DADOS_ENTRADA;



/****************************
 * REFERENCIA DO ARQUIVO	*
*****************************/
FILE * ARQUIVO;



/**********************
 * VALORES DE ENTRADA.*
 **********************/
float * * MATRIZ_ENTRADA;



/********************
 * 	MATRIZ DE PESOS *
 ********************/
float * * PESOS;

/**********************
 * ARRANJO DE SIMBOLOS
 *********************/
typedef struct simbolo
{
	char * variavel;
	int valor;
}simbolo;













/********************************
 *				FUNÇÕES			*
 ********************************/





/********************
 * FUNÇÃO DE ATIVAÇÃO.
*********************/
int ativacao (int valor )
{
	if (valor > 0)
		return valor;
	else
		return 0;
}




/**************************
 * FUNÇÃO DE TREINAMENTO
 *************************/
void treinar()
{

	
}








/**********************
 * EXIBIÇÃO DE AJUDA. *
 *********************/
void ajuda ()
{
	printf ("Autor: Guilherme Santana Coelho\n");
	printf(" 18/03/2018 - Perceptron \n");
	printf(" Ajuda:	-a caminho do arquivo CSV.\n");
}


/********************************
 * LE OS PARAMETROS DE ENTRADA. *
 *******************************/
int leParametros(int numeroDeParametros, char * parametros[])
{
	//COMEÇA A LER OS PARAMETROS A PARTIR DA POSIÇAO 1
	int indice = 1;
	//DECLARAÇÃO DE COMANDOS PADRÕES.
	const char * Ajuda = "-h";
	const char * ComandoArquivo = "-a";
	
	//LÊ TODOS OS PARÂMETROS.
	for ( indice = 1 ; indice < numeroDeParametros; indice++)
	{
		printf("parametro %i: %s\n",indice, parametros[indice]);
		//SE FOR AJUDA
		if ( strcmp (parametros[indice], Ajuda) == 0)
		{
			ajuda();
		}

		if ( strcmp (parametros[indice], ComandoArquivo) == 0)
		{
			ARQUIVO_ENTRADA = parametros[indice+1];
			indice++;
		}

	}
}




/*****************************
 * ABRE O ARQUIVO DE ENTRADA *
*****************************/

void abreArquivoDeDados()
{
	ARQUIVO = fopen(ARQUIVO_ENTRADA,"r");
}
/*****************************
 * FECHA O ARQUIVO DE ENTRADA *
*****************************/
void fechaArquivoDeDados()
{
	fclose(ARQUIVO);
}



/********************************************
 *  conta o número de variáveis do arquvo	*
 ********************************************/
void contaNumeroDeVariaveis(char * valorLido)
{
	NUMERO_DE_VARIAVEIS += 1;
	if (valorLido == NULL)
		CONTAGEM_DE_VARIAVEIS_FEITO = true;
	
}






/************************************
 *	Lê os dados da linha de entrada *
 *	na matriz						*
 ***********************************/
void leValoresDaLinhaDeEntrada( char * linhaDeEntrada)
{
	// const char delimitador = ",";
	char * valores = NULL;
	valores = strtok(linhaDeEntrada,",");
	do 
	{
		valores = strtok(NULL,",");
		if (CONTAGEM_DE_VARIAVEIS_FEITO == false)
		{
			contaNumeroDeVariaveis(valores);
		}
	}while(valores!=NULL);
	// printf("%s\n",linhaDeEntrada);
}


void instanciaPesos()
{
	PESOS = calloc(1*NUMERO_ENTRADAS,sizeof(int));
	int i = 0;
	for (i = 0; i < NUMERO_ENTRADAS; i++)
	{
		PESOS[i] = calloc(NUMERO_DE_VARIAVEIS,sizeof(int));
	}
}



/***
 *	INSTANCIA MATRIZES DE ENTRADA; 
*/
void instanciaMatriz()
{
	MATRIZ_ENTRADA = calloc(1*NUMERO_ENTRADAS,sizeof(float));
	int i = 0;
	for (i = 0; i < NUMERO_ENTRADAS; i++)
	{
		MATRIZ_ENTRADA[i] = calloc(NUMERO_DE_VARIAVEIS,sizeof(float));
	}
}



/**
 *	INSERE O VALOR NA MATRIZ 
 ***/
void insereValorNaMatriz(int linha , int indice,char * valor)
{
	MATRIZ_ENTRADA[linha][indice] = atof(valor);
}


/**
 *	INSERE VALOR ALETÓRIO NA MATRIZ DE PESOS 
 ***/
void insereValoresAleatoriosDePesos()
{
	int i;
	int j = 0;
	printf("PESOS:\n");
	for (i = 0 ; i < NUMERO_ENTRADAS; i++)
	{
		for(j = 0; j < NUMERO_DE_VARIAVEIS; j++)
		{
			PESOS[i][j] = rand()%20;
		}
		printf("\n");	
	}	
}

void imprimeMatrizDePesos()
{
	int i;
	int j = 0;
	printf("PESOS:\n");
	for (i = 0 ; i < NUMERO_ENTRADAS; i++)
	{
		for(j = 0; j < NUMERO_DE_VARIAVEIS; j++)
		{
			printf("[%.2f] ",PESOS[i][j]);
		}
		printf("\n");	
	}	
}


void imprimeMatrizDeEntrada()
{
	int i;
	int j = 0;
	printf("\nMatriz:\n");
	for (i = 0 ; i < NUMERO_ENTRADAS; i++)
	{
		for(j = 0; j < NUMERO_DE_VARIAVEIS; j++)
		{
			printf("[%.2f] ",MATRIZ_ENTRADA[i][j]);
		}
		printf("\n");	
	}	
	
}

/************************************
 *	insere os dados da linha de entrada *
 *	na matriz						*
 ***********************************/
void insereValoresNaMatriz(int numeroTupla, char * linhaDeEntrada)
{
	// const char delimitador = ",";
	char * valores = NULL;
	int indice = 0;
	valores = strtok(linhaDeEntrada,",");
	for ( indice = 0; indice < NUMERO_DE_VARIAVEIS; indice++) 
	{
		insereValorNaMatriz(numeroTupla, indice, valores);
		valores = strtok(NULL,",");	
	}
	// printf("%s\n",linhaDeEntrada);
}








/************************************
 * 		CONTA NUMERO DE TUPLAS		*
 ***********************************/
void contaNumeroDeTuplas()
{
	char buffer [255];
	int status = 0;
	 
	while (status >= 0)
	{
		//lê uma linha do arquivo de entrada;
		status = fscanf(ARQUIVO,"%s", buffer);
		if (status == -1)
			continue;
		NUMERO_ENTRADAS = NUMERO_ENTRADAS + 1;
	}
}



/************************************
 * 		LE ARQUIVOS DE DADOS.		*
 ***********************************/
void leArquivoDeDados()
{
	contaNumeroDeTuplas();
	fseek(ARQUIVO, 0, SEEK_SET);
	char buffer [255];
	int status = 0;
	 
	while (status >= 0)
	{
		//lê uma linha do arquivo de entrada;
		status = fscanf(ARQUIVO,"%s", buffer);
		if (status == -1)
			continue;
		leValoresDaLinhaDeEntrada(buffer);

	}

}

void insereDadosNaMatrizDeEntrada()
{
	fseek(ARQUIVO, 0, SEEK_SET);
	char linha [255];
	int status = 0;
	int numeroTupla = 0;
	while (status >= 0)
	{
		//lê uma linha do arquivo de entrada;
		status = fscanf(ARQUIVO,"%s", linha);
		if (status == -1)
			continue;
		insereValoresNaMatriz(numeroTupla, linha);
		numeroTupla += 1;
	}

}



void exibeInformacoesLidaDaEntrada()
{
	printf("\nNumero de variaves: %i\n",NUMERO_DE_VARIAVEIS);
	printf("Numero de entradas: %i\n",NUMERO_ENTRADAS);
	//printf("Numero de variaves: %i\n",NUMERO_DE_VARIAVEIS);
}



























/************************************************
 * 					INICIA O PROGRAMA.			*
 ***********************************************/



void declaraVariaveisDeInicio()
{
	ARQUIVO_ENTRADA = NULL;
	CONTAGEM_DE_VARIAVEIS_FEITO = false;
	NUMERO_DE_VARIAVEIS = 0;
	NUMERO_ENTRADAS = 0;
}


int iniciaPrograma( int numeroDeParametros, char * parametros[])
{
	declaraVariaveisDeInicio();
	leParametros(numeroDeParametros, parametros);
	if (ARQUIVO_ENTRADA != NULL)
	{
		abreArquivoDeDados();
		leArquivoDeDados();
		instanciaMatriz();
		instanciaPesos();
		insereDadosNaMatrizDeEntrada();
		insereValoresAleatoriosDePesos();
		imprimeMatrizDeEntrada();
		imprimeMatrizDePesos();
	}

	exibeInformacoesLidaDaEntrada();
		
}


void propriedadeAutor()
{
	printf("Perceptron - Guilherme Santana Coelho - inicio: 03/18/2018\n");
}





/****************
 * PRINCIPAL.	*
 ****************/
int main (int numeroDeParametros, char * parametros [] ){
	propriedadeAutor();
	iniciaPrograma(numeroDeParametros, parametros);
	fechaArquivoDeDados();
	return 0;
}