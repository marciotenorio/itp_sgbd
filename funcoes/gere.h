/**
Autor: Márcio Tenório Júnior
Versão: 1.0
Data: 29/11/2018
*/

/**
Funções para o gerenciamento do SGBD. Tais como criação, exclusão de tabelas, inserção, remoção, de dados em campos ou em linhas, remoção de colunas e o que mais possa vir a necessitar posteriormente
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


/**
 Grava tabela_url (nome da tabela recebida com fim .txt) e cont (quantidade de colunas) em urls_tabelas.txt\n
 Grava tabela_url (nome da tabela recebida com fim .txt), nome_colunas (colunas recebidas) e nome_tipos (tipos das colunas recebidas) em colunas_tabelas.txt\n
 Cria o arquivo tabela_url (nome da tabela recebida com fim .txt) vazio\n
 return 1, se tabela_url já existir em urls_tabelas.txt\n
 return 0, se a tabela não existir em urls_tabelas.txt e todos os dados forem gravados com sucesso\n
*/ 
int criar_tabela();

/**
 Verifica a existência de tabela_url (nome da tabela recebida) em urls_tabelas.txt\n
 return 1, se tabela_url não existe em urls_tabelas.txt\n
 Recebe a quantidade de colunas que a tabela suporta (qtd_colunas) de urls_tabelas.txt\n
 Valida o recebimento da chave primária \n
 return 1, se a chave primária já existe\n
 **tipos_coluna é uma matriz de strings de tamanho 2*qtd_colunas (pois armazenas os nomes das colunas e seus respectivos tipos), recebidos do arquivo colunas_tabelas.txt\n
 Valida os tipos de dados a serem recebidos apartir da comparação com os tipos armazenados em **tipos_coluna\n
 Recebe e grava os dados em tabela_url\n
 return 0, se todos os dados foram gravados com sucesso\n   
*/
int inserir_linha();

/**
 Processa o recebimento de uma chave primaria valida (que exista em tabela_url)\n
 **tipos_coluna recebe os nomes das colunas e seus respectivos tipos (2*qtd_colunas)\n
 qtd_linhas recebe o total de linhas que existe em tabela_url (tabela recebida)\n
 linha_info guarda a posição que a linha a ser modificada se encontra\n
 **toda_tabela recebe todas as informações de tabela_url (tabela recbida)\n
 Reescrevo tabela_url inserindo os dados recebidos por **toda_tabela, exceto em linha_info, linha que o dado a ser modificado se encontra\n
 Recebo os novos dados e os gravo sendo validados pelos tipos armazenados em **tipos_coluna no fim de tabela_url\n
*/
int editar_valor();

/**
  Valido a existencia de tabela_url (tabela recebida), se a mesma consta em urls_tabelas.txt\n
 return 1, se tabela_url (tabela recebida) não consta em urls_tabelas.txt\n
 **tipos coluna é uma matriz de strings que armazena os nomes e os seus respectivos tipos de tabela_url (tabela recebida)\n
 nova_coluna_nome recebe uma nova coluna e seu respectivo tipo\n
 Valida a unicidade da coluna recebida\n
 Atualiza os dados de colunas_tabelas.txt
 qtd_linhas recebe a quantidade de linhas de colunas_tabelas.txt\n
 linha_info recebe a linha onde a informação está gravada\n
 **toda_tabela recebe todos os dados de colunas_tabelas.txt\n
 Reescreve colunas_tabelas.txt com as informações de **toda_tabela exceto em linha_info\n
 Grava no fim de colunas_tabelas.txt as novas colunas (antigas + nova_coluna_nome[0]) e seus respectivos tipos (antigos + nova_coluna_nome[1])\n
 Atualiza os dados de urls_tabelas.txt\n
 qtd_linhas recebe a quantidade de linhas de urls_tabelas.txt\n
 linha_info recebe a linha onde a informação está gravada\n
 **toda_tabela recebe todos os dados de urls_tabelas.txt\n
 Reescreve urls_tabelas.txt com as informações de **toda_tabela exceto em linha_info\n
 Grava no fim de urls_tabelas.txt o nome da tabela com seu valor de colunas atualizado (qtd_colunas+1)\n
 return 0, se tudo foi executado com sucesso\n
*/
int criar_nova_coluna();

/**
 Validando a existência de tabela_url (tabela recebida) em urls_tabelas.txt\n
 Recebe chave_primaria (chave primaria da linha). Apartir da chave primaria, gravo a linha da chave primaria em linha_info e a quantidade total de linhas de tabela_url (tabela recebida) em qtd_linhas\n
 **toda_tabela é uma matriz de strings que recebe todos os dados de tabela_url (tabela recebida)\n
 Reescreve tabela_url com os dados de **toda_tabela exceto na linha_info (linha da chave primaria) \n
 return 0, se tudo foi executado com sucesso \n
*/
int apagar_valor();

/**
 Chama a função "remove" que tem como argumento tabela_url (tabela recebida) para apaga-la. Se conseguir apaga la retorna 0 e prossegue com o processamento\n
 Reescreve as informações de urls_tabelas.txt, exceto na linha que tabela_url se encontrava\n
 Reescreve as informações de colunas_tabelas.txt, exceto na linha que tabela_url se encontrava\n
 return 0, se conseguir remover o arquivo tabela_url e retirar suas informações de colunas_tabelas.txt e urls_tabelas.txt\n
 return 1, se não foi possivel remover tabela_url\n  
*/
int apagar_tabela();
