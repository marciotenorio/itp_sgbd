#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gere.h"
#include "info.h"
#include "menu.h"
/*
Autor: Márcio Tenório Júnior
Versão: 1.0
Data: 29/11/2018
*/

/*
	Tela principal do programa, contendo as funções dos headers incluidos de forma a melhor a experiência na utilização das ferramentas
*/

/**
Função que serve de interface para o programa.\n
*/

void main_menu()
{
		system("clear");
		

	char opcao[20]="";
	char algoparasair[50]="";

	while( (strcmp(opcao, "sair")) && (strcmp(opcao, "Sair")) && (strcmp(opcao, "SAIR")) )
	{

		printf("\t--------------------| SGBD ITP |--------------------\n");
		printf("\t\t\t\t\tby Marcio Tenorio - 27/11/2018\n");
		printf("\n\n\n");

		printf("\t--- | Digite o numero correspondente a acao desejada | ---\n\n");
		printf("\t1.  Criar uma nova tabela\n");
		printf("\t2.  Mostrar tabelas existentes\n");
		printf("\t3.  Inserir uma nova linha\n");
		printf("\t4.  Mostrar dados de uma tabela\n");
		printf("\t5.  Editar uma linha\n");
		printf("\t6.  Pesquisar dados em uma tabela\n");
		printf("\t7.  Criar uma nova coluna em uma tabela\n");
		printf("\t8.  Apagar a linha de uma tabela\n");
		printf("\t9.  Apagar uma tabela\n");
		printf("\t10. Informacoes sobre o software\n\n");
		printf("\t    Para sair, digite: \"sair\" sem as aspas.\n");
			printf("\n\n");


		scanf("%s", opcao);	

		if( (atoi(opcao)) == 1)
		{
			system("clear");
			criar_tabela();
			system("clear");
		}

		if( (atoi(opcao)) == 2)
		{
			system("clear");
			mostrar_tabelas();
			printf("\n\n");
			printf("Digite algo para sair:\n");
				scanf("%s", algoparasair);
			system("clear");
		}
		if( (atoi(opcao)) == 3)
		{
			system("clear");
			inserir_linha();
			system("clear");
		}

		if( (atoi(opcao)) == 4)
		{
			system("clear");
			listar_dados();
			printf("\n\n");
			printf("Digite algo para sair:\n");
				scanf("%s", algoparasair);
			system("clear");
		}
		if( (atoi(opcao)) == 5)
		{
			system("clear");
			editar_valor();
			system("clear");
		}

		if( (atoi(opcao)) == 6)
		{
			system("clear");
			pesquisar_valor();
			printf("\n\n");
			printf("Digite algo para sair:\n");
				scanf("%s", algoparasair);
			system("clear");
		}
		if( (atoi(opcao)) == 7)
		{
			system("clear");
			criar_nova_coluna();
			system("clear");
		}

		if( (atoi(opcao)) == 8)
		{
			system("clear");
			apagar_valor();
			system("clear");
		}
		if( (atoi(opcao)) == 9)
		{
			system("clear");
			apagar_tabela();
			system("clear");
		}

		if( (atoi(opcao)) == 10)
		{
			system("clear");
			printf("\tSoftware desenvolvido pelo aluno Marcio Tenorio Junior na disciplina de ITP/PTP,\n orientado pelo Prof. Dr. Julio Cesar Paulino de Melo.");
			printf("Projeto com o intuito de\n consolidar todos os conhecimentos adquiridos ao longo da disciplina, tanto em logica\n");
			printf("quanto em C, que foi a linguagem usada no curso. Meu primeiro software <3\n\n");
			printf("Digite algo para sair\n");

				scanf("%s", algoparasair);
			system("clear");
		}				
	}

}
