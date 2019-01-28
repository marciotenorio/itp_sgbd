#include "info.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
Autor: Márcio Tenório Júnior
Versão: 1.0
Data: 29/11/2018
*/

/* 
	Funções para retornar buscas de todos os tipos e extração de informações
	em geral do BD

	1 - Padrão para funções

    Funções que retornarem 1 não foram executadas como o esperado, já se o retorno for 0 foram executadas perfeitamente. 

2 - Formatação do código

    Usaremos como padrão formatação do plugin do Sublime "Easy Clang Format".

3- Diretórios e arquivos auxiliares

    Como parte da modularização os headers e os outros arquivos necessarios para os cabeçalhos estão salvos na pasta "sgbd_itp/funcoes".

    O diretorio "sgbd_itp/colunas_tabelas" é onde fica salvo o arquivo de texto que contém os nomes das colunas e seus respectivos tipos, sendo dessa forma por exemplo:

    "nome_da_tabela.txt coluna1 coluna2 %u %s \n"

    O diretorio "sgbd_itp/urls_tabelas" é onde fica salvo as tabelas existentes seguidas da quantidade de colunas que ela possui, por exemplo:
    
    "nome_da_tabela.txt 2\n"
*/


void mostrar_tabelas(){

	/*
	Lista todos as tabelas existentes em urls_tabelas.txt que são as tabelas válidas no banco
	*/
	FILE *urls_tabelas = fopen("urls_tabelas/urls_tabelas.txt", "r");

	char nome_tabela[20];
	int qnt_colunas=0;
	while((fscanf(urls_tabelas, "%s %d\n", nome_tabela, &qnt_colunas)) != EOF)
	{
		printf("%s\n", nome_tabela);
	}
	fclose(urls_tabelas);

}


int listar_dados()
{

	char str_aux[500], str_aux2[500];
	int cont=0, aux=0;


	/*
	Validando a existencia da tabela
	*/
	char tabela_url[50];
	
	printf("Qual o nome da tabela para listar os dados? (Com o fim .txt)\n");
		scanf("%s", tabela_url);
	

	FILE *urls_tabelas = fopen("urls_tabelas/urls_tabelas.txt", "r");
	
	while( (fgets(str_aux, 500, urls_tabelas) != NULL))
	{
		sscanf(str_aux, "%s %d\n", str_aux2, &aux);

		if( !(strcmp(str_aux2, tabela_url)))
		{
			cont=1;
				break;
		}
	}

	if(cont==0)
	{	
		fclose(urls_tabelas);
		printf("ERRO: Tabela não existente!\n");
			return 1;
	}

	fclose(urls_tabelas);

	
	/*
	Listando dados
	*/
	FILE *tabela = fopen(tabela_url, "r");

	while( (fgets(str_aux, 500, tabela)) != NULL) 
	{
		printf("%s", str_aux);
	}

	fclose(tabela);

	return 0;

}



int pesquisar_valor()
{

	char str_aux[500], str_aux2[500];
	int cont=0, aux=0;

	printf("Digite o nome da tabela que tera um valor pesquisado (nome.txt):\n");
	char tabela_url[50];
		scanf("%s", tabela_url);


	/*
	Validando a existencia da tabela
	*/

	FILE *urls_tabelas = fopen("urls_tabelas/urls_tabelas.txt", "r");
	
	while( (fscanf(urls_tabelas, "%s %d\n", str_aux, &aux) != EOF))
	{
		if( !(strcmp(str_aux, tabela_url)))
		{
			cont=1;
				break;
		}
	}

	if(cont==0)
	{
		printf("ERRO: Tabela não existente!\n");
		fclose(urls_tabelas);
		return 1;
	}

	fclose(urls_tabelas);


	/*
	Recebendo as colunas e tipos
	*/
	urls_tabelas = fopen("urls_tabelas/urls_tabelas.txt", "r");

	char nome[20];
	int qtd_colunas=0;
	while((fscanf(urls_tabelas, "%s %d\n", nome, &qtd_colunas)) != EOF)
	{

		if( !(strcmp(nome, tabela_url)) )
		{
			break;
		}
	}


	fclose(urls_tabelas);

	char **tipos_coluna; 
	tipos_coluna = malloc(sizeof(char*)*(2*qtd_colunas));		/*Matriz de strings alocada dinamicamente*/
	for (int i = 0; i < 2*qtd_colunas; ++i)
	{
		tipos_coluna[i] = malloc(sizeof(char)*20);
	}


	/*
	Recebendo os nomes e seus respectivos tipos das colunas
	*/
	FILE *colunas_tabelas = fopen("colunas_tabelas/colunas_tabelas.txt", "r");

	char validar[50];
	while((fscanf(colunas_tabelas, "%s\n", validar)) != EOF)
	{
		if( !(strcmp(validar,tabela_url)) )
		{	
			for (int i = 0; i < 2*qtd_colunas; ++i)
			 {
				fscanf(colunas_tabelas, " %s", tipos_coluna[i]);
			 }
			 	break; 
		}
	}


	fclose(colunas_tabelas);


	/*
	Exibindo as colunas e seus tipos
	*/

	printf("Abaixo as colunas e seus tipos disponiveis para pesquisa:\n\n");
	for (int i = 0; i < qtd_colunas; ++i)
	{
		printf("%s ", tipos_coluna[i]);
	}
		printf("\n");

	for (int i = qtd_colunas; i < 2*qtd_colunas; ++i)
	{
		printf("%s   ", tipos_coluna[i]);
	}
		printf("\n\n");


	/*
	Recebendo qual coluna pesquisar
	*/
	printf("Digite o nome da coluna que tera um valor pesquisado:\n\n");
	char coluna_escolhida[20];
		scanf("%s", coluna_escolhida);


	/*
	Descobrindo o tipo da coluna escolhida
	*/
	char tipo_coluna_escolhida[10];
	cont=0;
	for (int i = 0; i < qtd_colunas; ++i)
		{
			if( !(strcmp(coluna_escolhida, tipos_coluna[i])))
			{
				i=qtd_colunas;
				for (int j = 0 ; j < cont; ++j, ++i)
				{
				}
					strcpy(tipo_coluna_escolhida, tipos_coluna[i]);
						break;
			}

			cont++;
		}

	/*
	Quantidade de execuções da strtok no momento da pesquisa
	*/
	int ordem_coluna = cont;
	
	/*
	Comparando a coluna recebida com as existentes, exibindos os resultados e validando a comparação com o tipo do dado armazenado 
	  	>, >=, ==, <, <= ao valor informado
	*/
	printf("Digite o valor a ser pesquisado:\n");
	char valor[100];
		scanf("%s", valor);

	printf("Qual o tipo de pesquisa: >, >=, ==, < ou <= \n");
	char tipo_pesquisa[10];
		scanf("%s", tipo_pesquisa);

	FILE *tabela = fopen(tabela_url, "r"); 

 
	if( !(strcmp(tipo_pesquisa, ">")))
	{ 
		//Se o dado for um inteiro sem sinal
		if( !(strcmp(tipo_coluna_escolhida, "%u")))
		{

			while( fgets(str_aux, 500, tabela) != NULL)
			{
				strcpy(str_aux2, str_aux);

				cont=0;
				char *aux_str = strtok(str_aux, " ");
				while(aux_str != NULL)
				{

					if(cont == ordem_coluna)
					{
						break;
					}

					aux_str = strtok(NULL, " ");
					cont++;
				}

				unsigned int busca, valor_aux;

				sscanf(aux_str, "%u", &busca);
				sscanf(valor, "%u", &valor_aux);

				if(busca > valor_aux)
				{
					printf("%s", str_aux2);
				}

			}
			
		}

		//Se o dado for uma string
		else if( !(strcmp(tipo_coluna_escolhida, "%s")))
		{

			while( fgets(str_aux, 500, tabela) != NULL)
			{
				strcpy(str_aux2, str_aux);

				cont=0;
				char *aux_str = strtok(str_aux, " ");
				while(aux_str != NULL)
				{

					if(cont == ordem_coluna)
					{
						break;
					}

					aux_str = strtok(NULL, " ");
					cont++;
				}

				if(strcmp(valor, aux_str) > 0)
				{
					printf("%s", str_aux2);
				}
			

			}
			
		}

		//Se o dado for um inteiro
		else if( !(strcmp(tipo_coluna_escolhida, "%d")))
		{

			while( fgets(str_aux, 500, tabela) != NULL)
			{
				strcpy(str_aux2, str_aux);

				cont=0;
				char *aux_str = strtok(str_aux, " ");
				while(aux_str != NULL)
				{

					if(cont == ordem_coluna)
					{
						break;
					}

					aux_str = strtok(NULL, " ");
					cont++;
				}

				printf("%s\n", aux_str);
				if(atoi(aux_str) > atoi(valor))
				{
					printf("%s", str_aux2);
				}

			}

		}


		//Se o dado for um float
		else if( !strcmp(tipo_coluna_escolhida, "%f"))
		{

			while( fgets(str_aux, 500, tabela) != NULL)
			{
				strcpy(str_aux2, str_aux);

				cont=0;
				char *aux_str = strtok(str_aux, " ");
				while(aux_str != NULL)
				{

					if(cont == ordem_coluna)
					{
						break;
					}

					aux_str = strtok(NULL, " ");
					cont++;
				}

				//Garantindo que o ultimo caractere do dado retornado não tenha "\n" no fim


				if(atof(aux_str) > atof(valor))
				{
					printf("%s", str_aux2);
				}

			}
		
		}


		//Se o dado for um double
		else if( !(strcmp(tipo_coluna_escolhida, "%lf")))
		{

			while( fgets(str_aux, 500, tabela) != NULL)
			{
				strcpy(str_aux2, str_aux);

				cont=0;
				char *aux_str = strtok(str_aux, " ");
				while(aux_str != NULL)
				{

					if(cont == ordem_coluna)
					{
						break;
					}

					aux_str = strtok(NULL, " ");
					cont++;
				}

				double busca, valor_aux;

				sscanf(valor, "%lf", &valor_aux);
				sscanf(aux_str, "%lf", &busca);

				if( busca > valor_aux)
				{
					printf("%s", str_aux2);
				}

			}

		}


		//Se o dado for um char
		else if( !(strcmp(tipo_coluna_escolhida, "%c")))
		{

			while( fgets(str_aux, 500, tabela) != NULL)
			{
				strcpy(str_aux2, str_aux);

				cont=0;
				char *aux_str = strtok(str_aux, " ");
				while(aux_str != NULL)
				{

					if(cont == ordem_coluna)
					{
						break;
					}

					aux_str = strtok(NULL, " ");
					cont++;
				}

				char busca, valor_aux;

				sscanf(valor, "%c", &valor_aux);
				sscanf(aux_str, "%c", &busca);

				if( busca > valor_aux)
				{
					printf("%s", str_aux2);
				}

			}


		}
	}

	else if( !(strcmp(tipo_pesquisa, ">=")))
	{

		//Se o dado for um inteiro sem sinal
		if( !(strcmp(tipo_coluna_escolhida, "%u")))
		{

			while( fgets(str_aux, 500, tabela) != NULL)
			{
				strcpy(str_aux2, str_aux);

				cont=0;
				char *aux_str = strtok(str_aux, " ");
				while(aux_str != NULL)
				{

					if(cont == ordem_coluna)
					{
						break;
					}

					aux_str = strtok(NULL, " ");
					cont++;
				}

				unsigned int busca, valor_aux;

				sscanf(aux_str, "%u", &busca);
				sscanf(valor, "%u", &valor_aux);

				if(busca >= valor_aux)
				{
					printf("%s", str_aux2);
				}

			}
			
		}

		//Se o dado for uma string
		else if( !(strcmp(tipo_coluna_escolhida, "%s")))
		{

			while( fgets(str_aux, 500, tabela) != NULL)
			{
				strcpy(str_aux2, str_aux);

				cont=0;
				char *aux_str = strtok(str_aux, " ");
				while(aux_str != NULL)
				{

					if(cont == ordem_coluna)
					{
						break;
					}

					aux_str = strtok(NULL, " ");
					cont++;
				}

				if(strcmp(valor, aux_str) >= 0)
				{
					printf("%s", str_aux2);
				}				

			}
			
		}

		//Se o dado for um inteiro
		else if( !(strcmp(tipo_coluna_escolhida, "%d")))
		{

			while( fgets(str_aux, 500, tabela) != NULL)
			{
				strcpy(str_aux2, str_aux);

				cont=0;
				char *aux_str = strtok(str_aux, " ");
				while(aux_str != NULL)
				{

					if(cont == ordem_coluna)
					{
						break;
					}

					aux_str = strtok(NULL, " ");
					cont++;
				}


				if(atoi(aux_str) >= atoi(valor))
				{
					printf("%s", str_aux2);
				}

			}

		}


		//Se o dado for um float
		else if( !strcmp(tipo_coluna_escolhida, "%f"))
		{

			while( fgets(str_aux, 500, tabela) != NULL)
			{
				strcpy(str_aux2, str_aux);

				cont=0;
				char *aux_str = strtok(str_aux, " ");
				while(aux_str != NULL)
				{

					if(cont == ordem_coluna)
					{
						break;
					}

					aux_str = strtok(NULL, " ");
					cont++;
				}


				if(atof(aux_str) >= atof(valor))
				{
					printf("%s", str_aux2);
				}

			}
			
		}


		//Se o dado for um double
		else if( !(strcmp(tipo_coluna_escolhida, "%lf")))
		{

			while( fgets(str_aux, 500, tabela) != NULL)
			{
				strcpy(str_aux2, str_aux);

				cont=0;
				char *aux_str = strtok(str_aux, " ");
				while(aux_str != NULL)
				{

					if(cont == ordem_coluna)
					{
						break;
					}

					aux_str = strtok(NULL, " ");
					cont++;
				}

				double busca, valor_aux;

				sscanf(valor, "%lf", &valor_aux);
				sscanf(aux_str, "%lf", &busca);

				if( busca >= valor_aux)
				{
					printf("%s", str_aux2);
				}

			}

		}


		//Se o dado for um char
		else if( !(strcmp(tipo_coluna_escolhida, "%c")))
		{

			while( fgets(str_aux, 500, tabela) != NULL)
			{
				strcpy(str_aux2, str_aux);

				cont=0;
				char *aux_str = strtok(str_aux, " ");
				while(aux_str != NULL)
				{

					if(cont == ordem_coluna)
					{
						break;
					}

					aux_str = strtok(NULL, " ");
					cont++;
				}

				char busca, valor_aux;

				sscanf(valor, "%c", &valor_aux);
				sscanf(aux_str, "%c", &busca);

				if( busca >= valor_aux)
				{
					printf("%s", str_aux2);
				}

			}


		}
	}
		
	else if( !(strcmp(tipo_pesquisa, "==")))
	{
		//Se o dado for um inteiro sem sinal
		if( !(strcmp(tipo_coluna_escolhida, "%u")))
		{

			while( fgets(str_aux, 500, tabela) != NULL)
			{
				strcpy(str_aux2, str_aux);

				cont=0;
				char *aux_str = strtok(str_aux, " ");
				while(aux_str != NULL)
				{

					if(cont == ordem_coluna)
					{
						break;
					}

					aux_str = strtok(NULL, " ");
					cont++;
				}

				unsigned int busca, valor_aux;

				sscanf(aux_str, "%u", &busca);
				sscanf(valor, "%u", &valor_aux);

				if(busca == valor_aux)
				{
					printf("%s", str_aux2);
				}

			}

		}			

		//Se o dado for uma string
		else if( !(strcmp(tipo_coluna_escolhida, "%s")))
		{

			while( fgets(str_aux, 500, tabela) != NULL)
			{
				strcpy(str_aux2, str_aux);

				cont=0;
				char *aux_str = strtok(str_aux, " ");
				while(aux_str != NULL)
				{

					if(cont == ordem_coluna)
					{
						break;
					}

					aux_str = strtok(NULL, " ");
					cont++;
				}

				if(strcmp(valor, aux_str) == 0)
				{
					printf("%s", str_aux2);
				}

			}
				
		}

		//Se o dado for um inteiro
		else if( !(strcmp(tipo_coluna_escolhida, "%d")))
		{

			while( fgets(str_aux, 500, tabela) != NULL)
			{
				strcpy(str_aux2, str_aux);

				cont=0;
				char *aux_str = strtok(str_aux, " ");
				while(aux_str != NULL)
				{

					if(cont == ordem_coluna)
					{
						break;
					}

					aux_str = strtok(NULL, " ");
					cont++;
				}


				if(atoi(aux_str) == atoi(valor))
				{
					printf("%s", str_aux2);
				}

			}

		}


		//Se o dado for um float
		else if( !strcmp(tipo_coluna_escolhida, "%f"))
		{

			while( fgets(str_aux, 500, tabela) != NULL)
			{
				strcpy(str_aux2, str_aux);

				cont=0;
				char *aux_str = strtok(str_aux, " ");
				while(aux_str != NULL)
				{

					if(cont == ordem_coluna)
					{
						break;
					}

					aux_str = strtok(NULL, " ");
					cont++;
				}


				if(atof(aux_str) == atof(valor))
				{
					printf("%s", str_aux2);
				}

			}
			
		}


		//Se o dado for um double
		else if( !(strcmp(tipo_coluna_escolhida, "%lf")))
		{

			while( fgets(str_aux, 500, tabela) != NULL)
			{
				strcpy(str_aux2, str_aux);

				cont=0;
				char *aux_str = strtok(str_aux, " ");
				while(aux_str != NULL)
				{

					if(cont == ordem_coluna)
					{
						break;
					}

					aux_str = strtok(NULL, " ");
					cont++;
				}

				double busca, valor_aux;

				sscanf(valor, "%lf", &valor_aux);
				sscanf(aux_str, "%lf", &busca);

				if( busca == valor_aux)
				{
					printf("%s", str_aux2);
				}

			}

		}


		//Se o dado for um char
		else if( !(strcmp(tipo_coluna_escolhida, "%c")))
		{

			while( fgets(str_aux, 500, tabela) != NULL)
			{
				strcpy(str_aux2, str_aux);

				cont=0;
				char *aux_str = strtok(str_aux, " ");
				while(aux_str != NULL)
				{

					if(cont == ordem_coluna)
					{
						break;
					}

					aux_str = strtok(NULL, " ");
					cont++;
				}

				char busca, valor_aux;

				sscanf(valor, "%c", &valor_aux);
				sscanf(aux_str, "%c", &busca);

				if( busca == valor_aux)
				{
					printf("%s", str_aux2);
				}

			}


		}	
	}

	else if( !(strcmp(tipo_pesquisa, "<")))
	{
		//Se o dado for um inteiro sem sinal
		if( !(strcmp(tipo_coluna_escolhida, "%u")))
		{

			while( fgets(str_aux, 500, tabela) != NULL)
			{
				strcpy(str_aux2, str_aux);

				cont=0;
				char *aux_str = strtok(str_aux, " ");
				while(aux_str != NULL)
				{

					if(cont == ordem_coluna)
					{
						break;
					}

					aux_str = strtok(NULL, " ");
					cont++;
				}

				unsigned int busca, valor_aux;

				sscanf(aux_str, "%u", &busca);
				sscanf(valor, "%u", &valor_aux);

				if(busca < valor_aux)
				{
					printf("%s", str_aux2);
				}

			}

		}			

		//Se o dado for uma string
		else if( !(strcmp(tipo_coluna_escolhida, "%s")))
		{

			while( fgets(str_aux, 500, tabela) != NULL)
			{
				strcpy(str_aux2, str_aux);

				cont=0;
				char *aux_str = strtok(str_aux, " ");
				while(aux_str != NULL)
				{

					if(cont == ordem_coluna)
					{
						break;
					}

					aux_str = strtok(NULL, " ");
					cont++;
				}

				if(strcmp(valor, aux_str) < 0)
				{
					printf("%s", str_aux2);
				}				
			}
				
		}

		//Se o dado for um inteiro
		else if( !(strcmp(tipo_coluna_escolhida, "%d")))
		{

			while( fgets(str_aux, 500, tabela) != NULL)
			{
				strcpy(str_aux2, str_aux);

				cont=0;
				char *aux_str = strtok(str_aux, " ");
				while(aux_str != NULL)
				{

					if(cont == ordem_coluna)
					{
						break;
					}

					aux_str = strtok(NULL, " ");
					cont++;
				}


				if(atoi(aux_str) < atoi(valor))
				{
					printf("%s", str_aux2);
				}

			}

		}


		//Se o dado for um float
		else if( !strcmp(tipo_coluna_escolhida, "%f"))
		{

			while( fgets(str_aux, 500, tabela) != NULL)
			{
				strcpy(str_aux2, str_aux);

				cont=0;
				char *aux_str = strtok(str_aux, " ");
				while(aux_str != NULL)
				{

					if(cont == ordem_coluna)
					{
						break;
					}

					aux_str = strtok(NULL, " ");
					cont++;
				}


				if(atof(aux_str) < atof(valor))
				{
					printf("%s", str_aux2);
				}

			}
			
		}


		//Se o dado for um double
		else if( !(strcmp(tipo_coluna_escolhida, "%lf")))
		{

			while( fgets(str_aux, 500, tabela) != NULL)
			{
				strcpy(str_aux2, str_aux);

				cont=0;
				char *aux_str = strtok(str_aux, " ");
				while(aux_str != NULL)
				{

					if(cont == ordem_coluna)
					{
						break;
					}

					aux_str = strtok(NULL, " ");
					cont++;
				}

				double busca, valor_aux;

				sscanf(valor, "%lf", &valor_aux);
				sscanf(aux_str, "%lf", &busca);

				if( busca < valor_aux)
				{
					printf("%s", str_aux2);
				}

			}

		}


		//Se o dado for um char
		else if( !(strcmp(tipo_coluna_escolhida, "%c")))
		{

			while( fgets(str_aux, 500, tabela) != NULL)
			{
				strcpy(str_aux2, str_aux);

				cont=0;
				char *aux_str = strtok(str_aux, " ");
				while(aux_str != NULL)
				{

					if(cont == ordem_coluna)
					{
						break;
					}

					aux_str = strtok(NULL, " ");
					cont++;
				}

				char busca, valor_aux;

				sscanf(valor, "%c", &valor_aux);
				sscanf(aux_str, "%c", &busca);

				if( busca < valor_aux)
				{
					printf("%s", str_aux2);
				}

			}


		}	
	}

	else if( !(strcmp(tipo_pesquisa, "<=")))
	{
		//Se o dado for um inteiro sem sinal
		if( !(strcmp(tipo_coluna_escolhida, "%u")))
		{
			strcpy(str_aux2, str_aux);

			while( fgets(str_aux, 500, tabela) != NULL)
			{

				cont=0;
				char *aux_str = strtok(str_aux, " ");
				while(aux_str != NULL)
				{

					if(cont == ordem_coluna)
					{
						break;
					}

					aux_str = strtok(NULL, " ");
					cont++;
				}

				unsigned int busca, valor_aux;

				sscanf(aux_str, "%u", &busca);
				sscanf(valor, "%u", &valor_aux);

				if(busca <= valor_aux)
				{
					printf("%s", str_aux2);
				}

			}

		}			

		//Se o dado for uma string
		else if( !(strcmp(tipo_coluna_escolhida, "%s")))
		{

			while( fgets(str_aux, 500, tabela) != NULL)
			{
				strcpy(str_aux2, str_aux);

				cont=0;
				char *aux_str = strtok(str_aux, " ");
				while(aux_str != NULL)
				{

					if(cont == ordem_coluna)
					{
						break;
					}

					aux_str = strtok(NULL, " ");
					cont++;
				}

				if(strcmp(valor, aux_str) <= 0)
				{
					printf("%s", str_aux2);
				}
			}
				
		}

		//Se o dado for um inteiro
		else if( !(strcmp(tipo_coluna_escolhida, "%d")))
		{

			while( fgets(str_aux, 500, tabela) != NULL)
			{
				strcpy(str_aux2, str_aux);

				cont=0;
				char *aux_str = strtok(str_aux, " ");
				while(aux_str != NULL)
				{

					if(cont == ordem_coluna)
					{
						break;
					}

					aux_str = strtok(NULL, " ");
					cont++;
				}


				if(atoi(aux_str) <= atoi(valor))
				{
					printf("%s", str_aux2);
				}

			}

		}


		//Se o dado for um float
		else if( !strcmp(tipo_coluna_escolhida, "%f"))
		{

			while( fgets(str_aux, 500, tabela) != NULL)
			{
				strcpy(str_aux2, str_aux);

				cont=0;
				char *aux_str = strtok(str_aux, " ");
				while(aux_str != NULL)
				{

					if(cont == ordem_coluna)
					{
						break;
					}

					aux_str = strtok(NULL, " ");
					cont++;
				}


				if(atof(aux_str) <= atof(valor))
				{
					printf("%s", str_aux);
				}

			}
		
		}


		//Se o dado for um double
		else if( !(strcmp(tipo_coluna_escolhida, "%lf")))
		{

			while( fgets(str_aux, 500, tabela) != NULL)
			{
				strcpy(str_aux2, str_aux);

				cont=0;
				char *aux_str = strtok(str_aux, " ");
				while(aux_str != NULL)
				{

					if(cont == ordem_coluna)
					{
						break;
					}

					aux_str = strtok(NULL, " ");
					cont++;
				}

				double busca, valor_aux;

				sscanf(valor, "%lf", &valor_aux);
				sscanf(aux_str, "%lf", &busca);

				if( busca <= valor_aux)
				{
					printf("%s", str_aux2);
				}

			}

		}


		//Se o dado for um char
		else if( !(strcmp(tipo_coluna_escolhida, "%c")))
		{

			while( fgets(str_aux, 500, tabela) != NULL)
			{
				strcpy(str_aux2, str_aux);

				cont=0;
				char *aux_str = strtok(str_aux, " ");
				while(aux_str != NULL)
				{

					if(cont == ordem_coluna)
					{
						break;
					}

					aux_str = strtok(NULL, " ");
					cont++;
				}

				char busca, valor_aux;

				sscanf(valor, "%c", &valor_aux);
				sscanf(aux_str, "%c", &busca);

				if( busca <= valor_aux)
				{
					printf("%s", str_aux2);
				}

			}

		}		
	}
		
	fclose(tabela);


	for (int i = 0; i < 2*qtd_colunas; ++i)
	{
		free(tipos_coluna[i]);
	}
		free(tipos_coluna);

	return 0;
}