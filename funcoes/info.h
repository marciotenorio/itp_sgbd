/*
Autor: Márcio Tenório Júnior
Versão: 1.0
Data: 29/11/2018
*/

/*
Funções para retornar buscas de todos os tipos, extração de informações
em geral do BD e exposição dos dados
*/

/**
 Lista todas as tabelas existentes, que estão em urls_tabelas.txt\n
*/
void mostrar_tabelas();

/**
 Valida a existência de tabela_url (tabela recebida). Verifica se tabela_url existe em urls_tabelas.txt\n
 return 1, se tabela_url (tabela recebida) não existe em urls_tabelas.txt\n
 Lista todos os dados de tabela_url\n
 return 0, se tabela_url existe em urls_tabelas.txt e todos os dados foram listados com sucesso\n
*/
int listar_dados();

/**
 Valida a existência de tabela_url (tabela recebida) em urls_tabelas.txt\n
 return 1, se tabela_url não existe em urls_tabelas.txt\n
 **tipos_coluna é uma matriz de strings que armazena os nomes das colunas e seus respectivos tipos de tabela_url\n
 Recebe a coluna a ser pesquisada em coluna_escolhida\n
 tipo_coluna_escolhida armazena o tipo da coluna_escolhida, neste processo também armazena a ordem da coluna a ser pesquisa em ordem_coluna com base em tipos_coluna, por exemplo\n
   \ttipos_coluna[0] = "mat"\n
   \ttipos_coluna[1] = "nome"\n
   \ttipos_coluna[2] = "%u"\n
   \ttipos_coluna[3] = "%s"\n
   \tAssim se a coluna a ser pesquisa for "nome", descubro que a ordem é 1 (começa do 0) e essa sera a quantidade de vezes que strtok sera executada\n
 Sabendo a coluna_escolhida, tipo_coluna_escolhida e ordem_coluna.\n
 Recebe valor, que sera o valor a ser pesquisado\n
 Filtra a pesquisa pelos tipos ">", ">=", "==", "<" e "<=". Que seram armazenados em tipo_pesquisa\n
 Filtra pelo tipo da coluna a ser pesquisada,  para que cada valor seja comparado adequadamente %s com %s, %u com %u, etc\n
 Apos passar pelos filtros, str_aux recebe toda a linha, copia o valor de str_aux para str_aux2. Processa o strtok, ordem_coluna vezes para garantir obter a coluna pretendida e fazer a comparação necessária. Se a comparação retornar true, imprimi na tela str_aux2.\n
 return 0, se os dados foram listados adequadamente\n
*/
int pesquisar_valor();
