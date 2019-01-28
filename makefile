#Makefile do projeto SGBD ITP

all:	
	@echo "Compilando o main.c..."
	@gcc main.c funcoes/gere.c funcoes/info.c funcoes/menu.c -o executavel
	@echo "Para executar, digite \"make run\""

clean:
	@rm -f *.o
	@rm -f executavel 

run:

	./executavel

gdb:	
	@echo "Compilando e inicializando o gdb com a flag -ggdb"
	@gcc main.c funcoes/gere.c funcoes/info.c funcoes/menu.c -o executavel -ggdb
	@gdb executavel

valgrind:
	@echo "Compilando e inicializando o Valgrind com a flag -ggdb"
	@gcc main.c funcoes/gere.c funcoes/info.c funcoes/menu.c -o executavel -ggdb
	@valgrind ./executavel


