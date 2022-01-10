#include "menu.h"


void menu(int *op){  
	
    int bt;


		printf("\n\t\tMENU TESTE: \n\n");

		printf(" 1 - Pesquisar CPF (Valores pre-setados)\n");
		printf(" 2 - Remover CPF (Valores pre-setados)\n");
        printf(" 3 - Adicionar CPF (Valores pre-setados)\n");
        printf(" 4 - imprimir Arvore\n");
		printf(" 5 - Sair\n");
        scanf("%d",&bt);
		

	

    *op = bt;

	
}