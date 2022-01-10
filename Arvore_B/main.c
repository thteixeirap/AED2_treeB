#include "btree.h"
#include "menu.h"

int main(){
	
	Record r;
  	Pagina *btree = CreateBTree();
	int aux;
	unsigned long long int path=0;
	int op=0;
	int i;
	IniciaEntradas(&btree,r);
	Record rt;

	
	unsigned long long int teste1[] = {27159570809,18848853902,25352811829};
			Record r3;
			r3.key = 12531656880; 
			char nome[] = "Thomas";
			int idade = 23;

	while(op!=5){
		
		menu(&op);
		switch (op){
	
		case 1:
    		// 27159570809,Jessé	26 | 18848853902,Caetano	27 | 25352811829,Dominic	38 | 
			for(i=0;i<3;i++){
				rt.key = teste1[i];
				Pesquisa(btree,&rt,&path,&aux);
				printf("--------------------------------------");
			}
    	break;

		case 2:
			for(i=0;i<3;i++){
				rt.key = teste1[i];
				RemoveCPF(btree,rt);
				printf("--------------------------------------");
			}
		break;

		case 3:
			insereCPF(btree,&r3,nome,idade);
			Pesquisa(btree,&r3,&path,&aux);
		break;

	default:
		printf("FIM DO PROGRAMA\n");
		exit(0);
	break;
}}

	return 0;

}

