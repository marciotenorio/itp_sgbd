#include "gere.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	

/*
Autor: Márcio Tenório Júnior\n
Versão: 1.0\n
Data: 29/11/2018\n
*/

/*
Funções para o gerenciamento do SGBD. Tais como criação, exclusão de tabelas, inserção, remoção, de dados em campos ou em linhas, remoção de colunas e o que mais possa vir a necessitar posteriormente.


1 - Padrão para funções

    Funções que retornarem 1 não foram executadas como o esperado, já se o retorno for 0 foram executadas perfeitamente. 

2 - Formatação do código

    Usaremos como padrão formatação do plugin do Sublime "Easy Clang Complete".

3- Diretórios e arquivos auxiliares

    Como parte da modularização os headers e os outros arquivos necessarios para os cabeçalhos estão salvos na pasta "sgbd_itp/funcoes".

    O diretorio "sgbd_itp/colunas_tabelas" é onde fica salvo o arquivo de texto que contém os nomes das colunas e seus respectivos tipos, sendo dessa forma por exemplo:

    "nome_da_tabela.txt coluna1 coluna2 %u %s \n"

    O diretorio "sgbd_itp/urls_tabelas" é onde fica salvo as tabelas existentes seguidas da quantidade de colunas que ela possui, por exemplo:
    
    "nome_da_tabela.txt 2\n"
*/




int criar_tabela()
{

	char tabela_url[50]; /* Nome da tabela */
	printf("Qual o nome da tabela? (Com o fim .txt)\n");
		scanf("%s", tabela_url);
	/*
	Validando a existência de urls_tabelas.txt, se não cria e insere "tabela_url" no arquivo.
	*/
	FILE *urls_tabelas = fopen("urls_tabelas/urls_tabelas.txt", "r"); 

		if(urls_tabelas == NULL) /* Caso o arquivo urls_tabelas.txt ainda não exista *urls_tabelas retornara NULL */
		{
			urls_tabelas = fopen("urls_tabelas/urls_tabelas.txt", "w"); /* Criando o arquivo urls_tabelas.txt */
			fprintf(urls_tabelas, "%s ", tabela_url); /* Gravando o nome da tabela em urls_tabelas.txt */
		}

		else
		{	
			/* Como urls_tabelas.txt já existe, verificaremos se o nome da tabela recebida já existe neste mesmo arquivo */
			char urls_comparar[50];
			/* Recebendo os nomes das tabelas existentes até encontrar a recebida ou o fim do arquivo (EOF) for retornado */
			while((fscanf(urls_tabelas, "%s\n", urls_comparar)) != EOF) 
			{
				/* Comparando as tabelas existentes recebidas de urls_tabelas.txt com o nome da tabela_url (tabela recebida a ser criada) */
				if(strcmp(urls_comparar,tabela_url) == 0){
					printf("ERRO: A tabela ja existe.\n");
					return 1;
				}				
			}

			fclose(urls_tabelas);
			/* Constatado que a tabela ainda não existe, insere-se o nome (tabela_url) em urls_tabelas.txt*/
			urls_tabelas = fopen("urls_tabelas/urls_tabelas.txt", "a+");
			fprintf(urls_tabelas, "%s ", tabela_url);
		}
	
	/*
	Inserindo "tabela_url", nomes das colunas e seus respectivos tipos em colunas_tabelas.txt. Adicionando o numero de colunas em urls_tabelas.txt
	*/
	FILE *colunas = fopen("colunas_tabelas/colunas_tabelas.txt", "a+");

		printf("Em seguida digite as colunas, sendo que a primeira digitada por padrao sera a chave primaria do tipo: unsigned int.\n");

		char nome_colunas[50];	
		char op='s';
		int cont=0;

		fprintf(colunas, "%s ", tabela_url);

		while(op != 'n')
		{	
			printf("Qual o nome da coluna?\n");
				scanf("%s", nome_colunas);		
			fprintf(colunas,"%s ", nome_colunas);
			printf("Vai continuar a adicionar colunas? Digite 's' para continuar e 'n' para sair.\n");
				scanf(" %c", &op);
			cont++;
		}
			fprintf(urls_tabelas, "%d\n", cont);
			fclose(urls_tabelas);

		printf("Digite na mesma ordem que as colunas os tipos que iram ser usados, lembrando que o primeiro e por padrao unsigned int.\n");

		char nome_tipos[5];
		for (int i = 0; i < cont; ++i)
		{
			printf("Qual o tipo?\n");
				scanf("%s", nome_tipos);
			fprintf(colunas, "%s ", nome_tipos);
		}
			fprintf(colunas, "\n");

	fclose(colunas);
	/*
	Apenas criando a tabela sem inserir os dados
	*/
	FILE *cria_tabela = fopen(tabela_url, "w");
	fclose(cria_tabela);	

	return 0;
}

	

int inserir_linha()
{

	/* 
	Verificando se a tabela existe em urls_tabelas.txt para criar uma linha
	*/
	printf("Digite o nome da tabela para inserir a linha (com o fim .txt):\n");
	char tabela_url[50];
		scanf("%s", tabela_url);

	FILE *urls_tabelas = fopen("urls_tabelas/urls_tabelas.txt", "r");

	char urls_comparar[50];
	int aux, tabela_existe=0;
	while((fscanf(urls_tabelas, "%s %d\n", urls_comparar, &aux)) != EOF)
	{
		if(strcmp(urls_comparar, tabela_url) == 0)
		{
			tabela_existe = 1;
		}
	}

	if(tabela_existe == 0)
	{
		printf("ERRO: A tabela não existe!\n");
			return 1; 
	}

	fclose(urls_tabelas);

	/*
	Inserção dos dados em tabela_url
	*/

	/*
	Recebendo a quantidade de colunas da tabela em urls_tabelas.txt
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

	/*
	Validando a chave primaria
	*/
	unsigned int chave_primaria;
	printf("Digite a chave primaria:\n");
		scanf("%u", &chave_primaria);



	FILE *tabela = fopen(tabela_url, "r");
	char str_aux[80];

	unsigned int chave_primaria_comparar;
	while((fgets(str_aux, 80, tabela)) != NULL)
	{
		sscanf(str_aux, "%u\n", &chave_primaria_comparar);
		if(chave_primaria_comparar == chave_primaria)
		{
			printf("ERRO: Chave primaria ja existente.\n");
				return 1;
		}
	}

	fclose(tabela);


	/*
	Recebendo os nomes das colunas e seus respectivos tipos de colunas_tabelas.txt
	*/
	char **tipos_coluna; 
	tipos_coluna = malloc(sizeof(char*)*(2*qtd_colunas));		/*Matriz alocada dinamicamente*/
	for (int i = 0; i < 2*qtd_colunas; ++i)
	{
		tipos_coluna[i] = malloc(sizeof(char)*20);
	}

	FILE *colunas_tabelas = fopen("colunas_tabelas/colunas_tabelas.txt", "r");

	/* Validar vai recebendo os nomes das tabelas existentes até encontrar tabela_url, apartir dai armazena-se os nomes e tipos em **tipos_coluna */	
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
	Exibindo as colunas disponiveis
	*/
	for (int i = 0; i < qtd_colunas; ++i)
	{
		printf("%s ", tipos_coluna[i]);
	}
		printf("\n");
	for (int i = qtd_colunas; i < 2*qtd_colunas; ++i)
	{
		printf("%s ", tipos_coluna[i]);
	}
		printf("\n");

	printf("Digite os valores da tabela na mesma ordem de descricao das colunas.\nLembrando que por padrao a primeira coluna e a chave primaria.\n");
	
	/*
	Inserindo dados na tabela, validando os mesmos com os tipos recebidos em tipos_coluna
	*/
	tabela = fopen(tabela_url, "a+");

	for (int i = qtd_colunas; i < 2*qtd_colunas; ++i)
	{	

		if( !(strcmp(tipos_coluna[i], "%u")))
		{
			unsigned int cp;
			printf("Esta coluna e um inteiro sem sinal (chave primaria):\n");
				scanf("%u", &cp);
			fprintf(tabela, "%u ", cp);
		}

		if( !(strcmp(tipos_coluna[i], "%d")))
		{
			int inteiro;
			printf("Esta coluna e um inteiro:\n");
				scanf("%d", &inteiro);
			fprintf(tabela, "%d ", inteiro);
		}

		if( !(strcmp(tipos_coluna[i], "%f")))
		{
			float real;
			printf("Esta coluna e um float:\n");
				scanf("%f", &real);
			fprintf(tabela, "%f ", real);
		}

		if( !(strcmp(tipos_coluna[i], "%lf")))
		{
			double real_dupla;
			printf("Esta coluna e um double:\n");
				scanf("%lf", &real_dupla);
			fprintf(tabela, "%lf ", real_dupla);
		}

		if( !(strcmp(tipos_coluna[i], "%c")))
		{
			char carac;
			printf("Esta coluna e um char:\n");
				scanf(" %c", &carac);
			fprintf(tabela, "%c ", carac);
		}

		if( !(strcmp(tipos_coluna[i], "%s")))
		{
			char string[50];
			printf("Esta coluna e uma string:\n");
				scanf("%s", string);
			fprintf(tabela, "%s ", string);
		}

	}
		fprintf(tabela,"\n");

	fclose(tabela);

	/*
	Desalocando a memória
	*/
	for (int i = 0; i < 2*qtd_colunas; ++i)
	{
		free(tipos_coluna[i]);
	}

	free(tipos_coluna);

	return 0;
	
}

int editar_valor()
{

	char str_aux[500];

	printf("Digite o nome da tabela que ira ter um valor editado (fim .txt):\n");
	char tabela_url[50];
		scanf("%s", tabela_url);

	printf("Digite a chave primaria da linha:\n");
	unsigned int chave_primaria;
		scanf("%u", &chave_primaria);

	/*
	Validando a chave primaria no arquivo
	*/
	FILE *tabela = fopen(tabela_url, "r");

	int tabela_existe=0;
	while(tabela_existe == 0)
	{	
		fclose(tabela);
		tabela = fopen(tabela_url, "r");
		while((fgets(str_aux, 500, tabela)) != NULL) //
		{
			unsigned int chave_primaria_comparar;
			sscanf(str_aux, "%u\n", &chave_primaria_comparar);

			if(chave_primaria_comparar == chave_primaria)
			{
				tabela_existe = 1;
				break;
			}
		}

		if(tabela_existe == 1){
			break;
		}

		printf("Chave primaria invalida! Digite uma nova chave primaria:\n");
			scanf("%u", &chave_primaria);
	}

	fclose(tabela);

	/*
	Recebendo a quantidade de colunas da tabela;
	*/
	FILE *urls_tabelas = fopen("urls_tabelas/urls_tabelas.txt", "r");

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
	tipos_coluna = malloc(sizeof(char*)*(2*qtd_colunas));		/*Matriz alocada dinamicamente*/
	for (int i = 0; i < 2*qtd_colunas; ++i)
	{
		tipos_coluna[i] = malloc(sizeof(char)*20);
	}

	/*
	Recebendo nome e tipos das colunas
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
	Recebendo a quantidade de linhas, linha na qual a informação está e todo o texto da tabela
	*/
	tabela = fopen(tabela_url, "r");

	int linha_info=0, qtd_linhas=0, ret=0;
	unsigned int chave_primaria_comparar=0;
	while( (fgets(str_aux, 500, tabela)) != NULL)
	{
		sscanf(str_aux, "%u", &chave_primaria_comparar);

		if(chave_primaria == chave_primaria_comparar)
		{	

			if(ret == 0)
			{
				linha_info = qtd_linhas;
			}

			ret++;
		}

		qtd_linhas++;
	}



	char **toda_tabela = malloc(sizeof(char*)*(qtd_linhas));		/*Matriz alocada dinamicamente*/
	for (int i = 0; i < (qtd_linhas); ++i)
	{
		toda_tabela[i] = malloc(sizeof(char)*500);
	}

	fclose(tabela);


	tabela = fopen(tabela_url, "r");

	
	for (int i = 0; i < qtd_linhas; ++i)
	{
		fgets(toda_tabela[i], 500, tabela);
	}

	
	fclose(tabela);



	/*
	Alterando a linha
	*/
	tabela = fopen(tabela_url, "w");

	for (int i = 0; i < qtd_linhas; ++i)
	{	
		if(i == linha_info)
		{	
		}

		else
		{
			fprintf(tabela, "%s", toda_tabela[i]);			
		}	

	}

	fclose(tabela);

	printf("A seguir digite os valores das colunas com seus respectivos tipos(exceto a chave primaria, pois e unica):\n");

	for (int i = 0; i < qtd_colunas; ++i)
	{
		printf("%s ", tipos_coluna[i]);
	}
		printf("\n");
	for (int i = qtd_colunas; i < 2*qtd_colunas; ++i)
	{
		printf("%s ", tipos_coluna[i]);
	}
		printf("\n");

	/*
	Validando a entrada dos dados com os tipos armazenados em "tipos_coluna"
	*/
	tabela = fopen(tabela_url, "a+");

	for (int i = qtd_colunas; i < 2*qtd_colunas; ++i)
	{	
		if( !(strcmp(tipos_coluna[i], "%u")))
		{

			fprintf(tabela, "%u ", chave_primaria);
		}

		if( !(strcmp(tipos_coluna[i], "%d")))
		{
			int inteiro;
			printf("Esta coluna e um inteiro:\n");
				scanf("%d", &inteiro);
			fprintf(tabela, "%d ", inteiro);
		}

		if( !(strcmp(tipos_coluna[i], "%f")))
		{
			float real;
			printf("Esta coluna e um float:\n");
				scanf("%f", &real);
			fprintf(tabela, "%f ", real);
		}

		if( !(strcmp(tipos_coluna[i], "%lf")))
		{
			double real_dupla;
			printf("Esta coluna e um double:\n");
				scanf("%lf", &real_dupla);
			fprintf(tabela, "%lf ", real_dupla);
		}

		if( !(strcmp(tipos_coluna[i], "%c")))
		{
			char carac;
			printf("Esta coluna e um char:\n");
				scanf("%c", &carac);
			fprintf(tabela, "%c ", carac);
		}

		if( !(strcmp(tipos_coluna[i], "%s")))
		{
			char string[50];
			printf("Esta coluna e uma string:\n");
				scanf("%s", string);
			fprintf(tabela, "%s ", string);
		}

	}
		fprintf(tabela, "\n");

	fclose(tabela);

	/*
	Desalocando as matrizes
	*/
	for (int i = 0; i < 2*qtd_colunas; ++i)
	{
		free(tipos_coluna[i]);
	}

	free(tipos_coluna);

	for (int i = 0; i < qtd_linhas; ++i)
	{
		free(toda_tabela[i]);
	}

	free(toda_tabela);

	return 0;
}


int criar_nova_coluna() 
{
	char str_aux[500], str_aux2[500];
	int cont=0, aux=0;


	/*
	Validando a existencia da tabela
	*/
	char tabela_url[50];
	printf("Qual o nome da tabela para adicionar uma coluna? (Com o fim .txt)\n");
		scanf("%s", tabela_url);

	//Validando a existência da tabela
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
	Recebendo colunas e tipos da tabela
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
	Recebendo nova coluna e seu tipo. Validando a existência da coluna.
	*/
	printf("Digite o nome da coluna e seu tipo para ser adicionada:\n");

	char nova_coluna_nome_tipo[2][50];
	for (int i = 0; i < 2; ++i)
	{
		scanf("%s", nova_coluna_nome_tipo[i]);
	}


	aux=cont=0;
	for (int i = 0; i < qtd_colunas; ++i)
	{
		if( !(strcmp(nova_coluna_nome_tipo[0], tipos_coluna[i])) )
		{
			printf("Coluna ja existente, digite uma nova coluna e seu tipo para ser adicionada:\n");

			for (int i = 0; i < 2; ++i)
			{
				scanf("%s", nova_coluna_nome_tipo[i]);
			}

			i=0;
		}
	}


	
	/*
	Reescrevendo as novas informações em urls_tabelas.txt e colunas_tabelas.txt
	*/  
	colunas_tabelas = fopen("colunas_tabelas/colunas_tabelas.txt", "r");

	int ret=0, linha_info=0, qtd_linhas=0;
	while( (fgets(str_aux, 500, colunas_tabelas)) != NULL)
	{
		sscanf(str_aux, "%s", str_aux2);

		if( !(strcmp(str_aux2, tabela_url)))
		{	

			if(ret == 0)
			{
				linha_info = qtd_linhas;
			}

			ret++;
		}

		qtd_linhas++;
	}

	fclose(colunas_tabelas);

	char **toda_tabela = malloc(sizeof(char*)*(qtd_linhas-1));		/*Matriz alocada dinamicamente*/
	for (int i = 0; i < (qtd_linhas-1); ++i)
	{
		toda_tabela[i] = malloc(sizeof(char)*500);
	}



	colunas_tabelas = fopen("colunas_tabelas/colunas_tabelas.txt", "r");

	for (int i = 0; i < qtd_linhas; ++i)
	{
		fgets(toda_tabela[i], 500, colunas_tabelas);
	}

	
	fclose(colunas_tabelas);



	/*
	Alterando a linha
	*/
	colunas_tabelas = fopen("colunas_tabelas/colunas_tabelas.txt", "w");

	for (int i = 0; i < qtd_linhas; ++i)
	{	
		if(i == linha_info)
		{	
		}

		else
		{
			fprintf(colunas_tabelas, "%s", toda_tabela[i]);			
		}	

	}

	fclose(colunas_tabelas);

	colunas_tabelas = fopen("colunas_tabelas/colunas_tabelas.txt", "a+");

	fprintf(colunas_tabelas, "%s", tabela_url);
	for (int i = 0; i < qtd_colunas; ++i)
	{
	 	fprintf(colunas_tabelas, " %s", tipos_coluna[i]);
	}

	fprintf(colunas_tabelas, " %s", nova_coluna_nome_tipo[0]);

	for (int i = qtd_colunas; i < 2*qtd_colunas; ++i)
	{
		fprintf(colunas_tabelas, " %s", tipos_coluna[i]);
	}

	fprintf(colunas_tabelas, " %s \n", nova_coluna_nome_tipo[1]);

	fclose(colunas_tabelas);


	/*
	Fazendo o mesmo procedimento de reescrita em urls_tabelas.txt para atualizar o valor da quantidade de colunas
	*/
	urls_tabelas = fopen("urls_tabelas/urls_tabelas.txt", "r");

	ret=0, linha_info=0, qtd_linhas=0;
	while( (fgets(str_aux, 500, urls_tabelas)) != NULL)
	{
		sscanf(str_aux, "%s", str_aux2);

		if( !(strcmp(str_aux2, tabela_url)))
		{	

			if(ret == 0)
			{
				linha_info = qtd_linhas;
			}

			ret++;
		}

		qtd_linhas++;
	}

	fclose(urls_tabelas);

	char **toda_tabela2 = malloc(sizeof(char*)*(qtd_linhas-1));		/*Matriz alocada dinamicamente*/
	for (int i = 0; i < (qtd_linhas-1); ++i)
	{
		toda_tabela2[i] = malloc(sizeof(char)*500);
	}



	urls_tabelas = fopen("urls_tabelas/urls_tabelas.txt", "r");

	for (int i = 0; i < qtd_linhas-1; ++i)
	{
		fgets(toda_tabela2[i], 500, urls_tabelas);
	}

	
	fclose(urls_tabelas);



	/*
	Alterando a linha
	*/
	urls_tabelas = fopen("urls_tabelas/urls_tabelas.txt", "w");

	for (int i = 0; i < qtd_linhas-1; ++i)
	{	
		if(i == linha_info)
		{	
		}

		else
		{
			fprintf(urls_tabelas, "%s", toda_tabela2[i]);			
		}	

	}


	fprintf(urls_tabelas, "%s %d\n", tabela_url, qtd_colunas+1);

	fclose(urls_tabelas);	


	/*
	Desalocando memoria
	*/
	for (int i = 0; i < 2*qtd_colunas; ++i)
	{
		free(tipos_coluna[i]);
	}
	free(tipos_coluna);

	for (int i = 0; i < (qtd_linhas-1); ++i)
	{
		free(toda_tabela[i]);
	}
	free(toda_tabela);

	for (int i = 0; i < (qtd_linhas-1); ++i)
	{
		free(toda_tabela2[i]);
	}
	free(toda_tabela2);


	return 0;
}



int apagar_valor()
{
	char str_aux[500];
	int aux=0, cont=0;

	printf("Digite a tabela que tera os valores apagado:\n");
	char tabela_url[50];
		scanf("%s", tabela_url);

	/*
	Validando a existência da tabela
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

	printf("Digite o valor da chave primaria da linha que sera apagada:\n");
	unsigned int chave_primaria;
		scanf("%u", &chave_primaria);


	/*
	Encontrando a linha a ser apagada e o total de linhas
	*/
	FILE *tabela = fopen(tabela_url, "r");

	int linha_info=0, qtd_linhas=0, ret=0;
	unsigned int chave_primaria_comparar=0;
	while( (fgets(str_aux, 500, tabela)) != NULL)
	{
		sscanf(str_aux, "%u", &chave_primaria_comparar);

		if(chave_primaria == chave_primaria_comparar)
		{	

			if(ret == 0)
			{
				linha_info = qtd_linhas;
			}

			ret++;
		}

		qtd_linhas++;
	}



	char **toda_tabela = malloc(sizeof(char*)*(qtd_linhas));		/*Matriz alocada dinamicamente*/
	for (int i = 0; i < (qtd_linhas); ++i)
	{
		toda_tabela[i] = malloc(sizeof(char)*500);
	}

	fclose(tabela);


	tabela = fopen(tabela_url, "r");


	for (int i = 0; i < qtd_linhas; ++i)
	{
		fgets(toda_tabela[i], 500, tabela);
	}

	
	fclose(tabela);



	/*
	Alterando a linha
	*/
	tabela = fopen(tabela_url, "w");

	for (int i = 0; i < qtd_linhas; ++i)
	{	
		if(i == linha_info)
		{	
		}

		else
		{
			fprintf(tabela, "%s", toda_tabela[i]);			
		}	

	}

	fclose(tabela);

	/*
	Desalocando a memoria
	*/
	for (int i = 0; i < qtd_linhas; ++i)
	{
		free(toda_tabela[i]);
	}

	free(toda_tabela);

	return 0;
}


int apagar_tabela()
{
	char str_aux[500], str_aux2[500];

	printf("Digite o nome da tabela para que seja deletada:\n");
	char tabela_url[50];
		scanf("%s", tabela_url);

	char aux_tabela_url[50];

	strcpy(aux_tabela_url, tabela_url);

	int verificador = remove(aux_tabela_url);

	if(verificador == 0)
	{
		/* Retirando as informações da tabela de urls_tabelas
		colunas_tabelas */
		FILE *colunas_tabelas = fopen("colunas_tabelas/colunas_tabelas.txt", "r");

		int ret=0, linha_info=0, qtd_linhas=0;
		while( (fgets(str_aux, 500, colunas_tabelas)) != NULL)
		{
			sscanf(str_aux, "%s", str_aux2);

			if( !(strcmp(str_aux2, tabela_url)))
			{	

				if(ret == 0)
				{
					linha_info = qtd_linhas;
				}

				ret++;
			}

			qtd_linhas++;
		}

		fclose(colunas_tabelas);

		char **toda_tabela = malloc(sizeof(char*)*(qtd_linhas-1));		/*Matriz alocada dinamicamente*/
		for (int i = 0; i < (qtd_linhas-1); ++i)
		{
			toda_tabela[i] = malloc(sizeof(char)*500);
		}


		colunas_tabelas = fopen("colunas_tabelas/colunas_tabelas.txt", "r");

		for (int i = 0; i < qtd_linhas-1; ++i)
		{
			fgets(toda_tabela[i], 500, colunas_tabelas);
		}

		
		fclose(colunas_tabelas);



		/*
		Alterando a linha
		*/
		colunas_tabelas = fopen("colunas_tabelas/colunas_tabelas.txt", "w");

		for (int i = 0; i < qtd_linhas-1; ++i)
		{	
			if(i == linha_info)
			{	
			}

			else
			{
				fprintf(colunas_tabelas, "%s", toda_tabela[i]);			
			}	

		}

		fclose(colunas_tabelas);

		/*
		Efetuando a mesma reescrita, só que agora de urls_tabelas.txt
		*/
		FILE *urls_tabelas = fopen("urls_tabelas/urls_tabelas.txt", "r");

		ret=0, linha_info=0, qtd_linhas=0;
		while( (fgets(str_aux, 500, urls_tabelas)) != NULL)
		{
			sscanf(str_aux, "%s", str_aux2);

			if( !(strcmp(str_aux2, tabela_url)))
			{	

				if(ret == 0)
				{
					linha_info = qtd_linhas;
				}

				ret++;
			}

			qtd_linhas++;
		}

		fclose(urls_tabelas);


		char **toda_tabela2 = malloc(sizeof(char*)*(qtd_linhas-1));		/*Matriz alocada dinamicamente*/
		for (int i = 0; i < (qtd_linhas-1); ++i)
		{
			toda_tabela2[i] = malloc(sizeof(char)*500);
		}


		urls_tabelas = fopen("urls_tabelas/urls_tabelas.txt", "r");

		for (int i = 0; i < qtd_linhas-1; ++i)
		{
			fgets(toda_tabela2[i], 500, urls_tabelas);
		}

		
		fclose(urls_tabelas);



		/*
		Alterando a linha
		*/
		urls_tabelas = fopen("urls_tabelas/urls_tabelas.txt", "w");

		for (int i = 0; i < qtd_linhas-1; ++i)
		{	
			if(i == linha_info)
			{	
			}

			else
			{
				fprintf(urls_tabelas, "%s", toda_tabela2[i]);			
			}	

		}

		fclose(urls_tabelas);	


		/*
		Desalocando memória
		*/
		for (int i = 0; i < (qtd_linhas-1); ++i)
		{
			free(toda_tabela[i]);
		}
		free(toda_tabela);

		for (int i = 0; i < (qtd_linhas-1); ++i)
		{
			free(toda_tabela2[i]);
		}
		free(toda_tabela2);

		return 0;
	}

	else
	{
		printf("ERRO! Nao foi possivel apagar a tabela.\n");
		return 1;
	}



}










