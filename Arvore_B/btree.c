#include "btree.h"

unsigned long long int maiorMenor=0;
int aux=0;

Pagina* CreateBTree(){
  return NULL;
}

//Cap 18: pÃ¡gina 355 / adaptaÃ§Ã£o para disco
void Pesquisa(Pagina *p, Record *r,unsigned long long int *path, int *x){ 
  short i = 1;

  if(p == NULL){
   // printf("\n MaiorMenor: %lld ",maiorMenor);
    *path = maiorMenor;
    PesquisaArquivo(maiorMenor,*r,x);
    return;
  }
 

  while (i < p->n && r->key > p->r[i-1].key){ 
    //printf("\nDentro do loop: %lld\n",p->r[i-1].key);
    if(p->r[i-1].key >= maiorMenor && p->r[i-1].key < r->key)
      maiorMenor = p->r[i-1].key;
    i++;}

  if(p->r[i-1].key >= maiorMenor && p->r[i-1].key < r->key)
    maiorMenor = p->r[i-1].key;


  
  //printf("\nFora apos loop: %lld \n",p->r[i-1].key);

  if (r->key == p->r[i-1].key){ 
    maiorMenor = p->r[i-1].key;
    *path = maiorMenor;
    PesquisaArquivo(maiorMenor,*r,x);
    *r = p->r[i-1];
    return;
  }

  if (r->key < p->r[i-1].key) {  
    Pesquisa(p->p[i-1], r,path,x);
  }

  else 
    Pesquisa(p->p[i], r,path,x); 
} 


void InsereNaPagina(Pagina *p, Pagina *pdir, Record r){ 
  short IsNotPosition;
  int k;
  
  //printf("Insere na página: %lld\n",r.key);

  k = p->n;  
  IsNotPosition = (k > 0);
  
  while (IsNotPosition){ 
    
    if (r.key >= p->r[k-1].key){ 
      IsNotPosition = FALSE;
      break;
    }
    
    p->r[k]   = p->r[k-1];
    p->p[k+1] = p->p[k];
    k--;
      
    if (k < 1) 
      IsNotPosition = FALSE;
  }
  
  p->r[k] = r; 
  p->p[k+1] = pdir;
  p->n++;

} 

void InsertFixUp(Pagina **p, Pagina **pr, Record r, Record *rr, short *Overflow){ 
  long i=1, j; 
  Pagina *paux;

  if (*p == NULL){ 
    *Overflow = TRUE; 
    *rr = r; 
    *pr = NULL;
    return;
  }

  while (i < (*p)->n && r.key > (*p)->r[i-1].key)  i++;

  if (r.key == (*p)->r[i-1].key){ 
    printf("[ERROR]: Record already exists\n"); 
    *Overflow = FALSE;
    return;
  }

  if (r.key < (*p)->r[i-1].key) i--; 

  /* caminha nas sub-Ã¡rvores a esquerda e/ou direita da B Tree*/
  InsertFixUp(&(*p)->p[i], pr, r, rr, Overflow);
  
  /* na chamada (linha 101) esse if valida o registro jÃ¡ existente*/
  if (!*Overflow) return;

  if ((*p)->n < MM){ /* pÃ¡gina com espaÃ§o */ 
      InsereNaPagina(*p, *pr, *rr);
      *Overflow = FALSE;
      return;
  }
  
  /* Overflow: Pagina tem que ser dividida */
  paux = (Pagina*)malloc(sizeof(Pagina));
  paux->n = 0;  
  paux->p[0] = NULL;

  if (i < M + 1){ 
    InsereNaPagina(paux, (*p)->p[MM], (*p)->r[MM-1]);
    (*p)->n--;
    InsereNaPagina(*p, *pr, *rr);
  }else 
    InsereNaPagina(paux, *pr, *rr);
  
  for (j=M+2; j<=MM; j++) 
    InsereNaPagina(paux, (*p)->p[j], (*p)->r[j-1]);

  (*p)->n = M;  
  paux->p[0] = (*p)->p[M+1];
  *rr = (*p)->r[M];  
  *pr = paux;
}


//Cap 18. pÃ¡gina 357
void Insere(Pagina **p, Record r){ 
 
  short Overflow;
  Record rr;
  Pagina *pr, *paux;

  //p = raiz
  //pr = ponteiro de ligaÃ§Ã£o quando estoura
  //r = novo dado
  //rr = dado a ser deslocado
  //Overflow = bit para indicar estouro de pÃ¡ginas
  InsertFixUp(p, &pr, r, &rr, &Overflow);

  if (Overflow){ /* cresce na altura */ 
    paux = (Pagina *)malloc(sizeof(Pagina));
    paux->n = 1;  
    paux->r[0] = rr;
    paux->p[0] = *p;  
    paux->p[1] = pr;
    *p = paux;
  }

}

void RemoveFixUp(Pagina *p, Pagina *pai, int PosPai, int *underflow){ 
  Pagina *aux; 
  long disp, j;
  
  if (PosPai < pai->n){ 
    aux = pai->p[PosPai + 1];  
    disp = (aux->n - M + 1) / 2;
    p->r[p->n] = pai->r[PosPai];
    p->p[p->n + 1] = aux->p[0];  
    p->n++;
    
    if (disp > 0){ 
      for (j = 1; j < disp; j++)
        InsereNaPagina(p, aux->p[j], aux->r[j-1]);
      
      pai->r[PosPai] = aux->r[disp-1];  
      aux->n -= disp;
      
      for (j = 0; j < aux->n; j++) 
        aux->r[j] = aux->r[j + disp];
      for (j = 0; j <= aux->n; j++) 
        aux->p[j] = aux->p[j + disp];
      *underflow = FALSE;
    
    }else{ /* intercala aux em p e libera aux */ 
      
      for (j = 1; j <= M; j++)
        InsereNaPagina(p, aux->p[j], aux->r[j-1]);
      free(aux);
        
      for (j = PosPai + 1; j < pai->n; j++){ 
        pai->r[j-1] = pai->r[j];
        pai->p[j] = pai->p[j+1];
      }
      
      pai->n--;
      if (pai->n >= M) 
        *underflow = FALSE;
    }

  }else{ /* aux = Pagina a esquerda de p */ 
    aux = pai->p[PosPai-1]; 
    disp = (aux->n - M + 1) / 2;
    
    for (j = p->n; j >= 1; j--) 
      p->r[j] = p->r[j-1];
    
    p->r[0] = pai->r[PosPai-1];
    
    for (j = p->n; j >= 0; j--) 
      p->p[j+1] = p->p[j];
    
    p->n++;
    if (disp > 0){ /* Existe folga: transf. de aux para p */ 
      for (j = 1; j < disp; j++)
          InsereNaPagina(p, aux->p[aux->n - j + 1], aux->r[aux->n - j]);

      p->p[0] = aux->p[aux->n - disp + 1];
      pai->r[PosPai-1] = aux->r[aux->n - disp];
      aux->n -= disp;  
      *underflow = FALSE;

    }else{ /* intercala p em aux e libera p */ 
      
      for (j = 1; j <= M; j++)
            InsereNaPagina(aux, p->p[j], p->r[j-1]);
      
      free(p);  
      pai->n--;
      
      if (pai->n >= M)  
        *underflow = FALSE;
    }
  }
}

void Antecessor(Pagina *p, int i, Pagina *pai, int *underflow){ 

  if (pai->p[pai->n] != NULL){ 
    Antecessor(p, i, pai->p[pai->n], underflow);
    if (*underflow) 
      RemoveFixUp(pai->p[pai->n], pai, pai->n, underflow);
    return;
  }
  
  p->r[i-1] = pai->r[pai->n - 1]; 
  pai->n--;  
  *underflow = (pai->n < M);

}

void Remove(Pagina **p, unsigned long long int key, int *underflow){ 
  long j, i = 1;
  Pagina *aux;

  if (*p == NULL){ 
    printf("[ERROR]: Record not found!\n"); 
    *underflow = FALSE;
    return;
  }

  aux = *p;
  while (i < aux->n && key > aux->r[i-1].key) i++;

  if (key == aux->r[i-1].key){ 
    if (aux->p[i-1] == NULL){ 
      aux->n--;
      *underflow = (aux->n < M);
      for (j = i; j <= aux->n; j++){ 
        aux->r[j-1] = aux->r[j];  
        aux->p[j] = aux->p[j+1]; 
      }
      return;
    }

    Antecessor(*p, i, aux->p[i-1], underflow);
    if (*underflow) 
      RemoveFixUp(aux->p[i-1], *p, i - 1, underflow);
    return;
  }

  if (key > aux->r[i-1].key) i++;
  
  Remove(&aux->p[i-1], key, underflow);
  
  if (*underflow) 
    RemoveFixUp(aux->p[i-1], *p, i - 1, underflow);
} 

void Retira(Pagina **p, int key){ 
  int underflow;
  Pagina *aux;

  Remove(p, key, &underflow);
  
  if (underflow && (*p)->n == 0){ /* Arvore diminui na altura */
    aux = *p;   
    *p = aux->p[0]; 
    free(aux);
  }

}    

void Imprime(Pagina **p, int level){ 
  long i;

  if (*p == NULL) return;
  
  printf("Nivel %d: ", level);
  for (i = 0; i < (*p)->n; i++)
    printf("%lld ",(*p)->r[i].key);
    
  putchar('\n');
  level++;

  for (i = 0; i <= (*p)->n; i++)
    Imprime(&(*p)->p[i], level);
}

void IniciaEntradas(Pagina **p,Record r){

    FILE *fp;
    FILE *fc;
    char linha[100];
    char aux[100];
    char *result;
    int i=1;
    char *pt;
    char path[20];

    fp = fopen("./database.txt","r");
   

    if(fp == NULL){
        printf("Problemas na abertura do arquivo");
        return;                                                                                                                                                                         
    }

    //ABRE O ARQUIVO DATABASE
    while(!feof(fp)){
     
      //DIVIDE A LEITURA EM 10 EM 10
      while(i<=10){
         
        //QUANDO LER O PRIMEIRO CPF QUE TERÁ O ARQUIVO A SER CRIADO
        result = fgets(linha,80,fp);
        strcpy(aux,linha);

        if(i==1){        
          pt = strtok(result,"    ,");
          strcpy(path,"./");
          strcat(path,pt);
          strcat(path,".txt");

          //CRIA UM ARQUIVO COM O NOME DO PRIMEIRO CPF NELE CADASTRADO
          fc=fopen(path,"w");
          
          if(fc == NULL){
            printf("Problemas na abertura do arquivo FC");
            return;                                                                                                                                                                         
          }else{
            /*- TRANSFORMA O PRIMEIRO CPF EM INT E INSERE NA ÁRVORE 
              - SOMENTE O PRIMEIRO CPF DE CADA ARQUIVO IRÁ IR PARA A ÁRVORE
              - SENDO QUE ESSE SERÁ O NOME DO ARQUIVO */            
            r.key = atof(pt);
            Insere(p,r);
          }
        }

        //APOS CRIADO ESCREVE 10 CPF's NO ARQUIVO
        if(result){
          //printf("Linha: %d: %s\n",i,aux);
          fprintf(fc,"%s",aux);
          i++;
        }
        
      }
      //DEPOIS QUE JA ESCRITO OS 10 CPF's FECHA O ARQUIVO
      fclose(fc);
      pt = strtok(NULL, " ");
      i=1;
    }
  //DEPOIS JA FEITO TODOS OS ARQUIVOS SEPARADOS. FECHA O ARQUIVO DATABASE
  //printf("\nARQUIVO FECHADO\n");
  fclose(fp);
  
}

void PesquisaArquivo(unsigned long long int cpf,Record r,int *x){

  char path[15];
  char aux[50];
  sprintf(path,"%lld",cpf);
  strcat(path,".txt");
  FILE *fp;
  char linha[50];
  char *result;
  char *pt;
  int cont=0;

  fp = fopen(path,"r");

  if(fp == NULL){
    printf("\nProblemas na abertura do arquivo: %s",path);
    return;                                                                                                                                                                         
  }

  while(!feof(fp)){  

    if(cont == 9)
      break;
    
    result = fgets(linha,80,fp);
    strcpy(aux,linha);
    pt = strtok(result,"    ,");
    if (atof(pt) == r.key){
      printf("\nCPF ENCONTRADO: \n");
      printf("%s\n",aux);
      *x = TRUE;
      fclose(fp);
      return;
    } 
    cont++;
    pt = strtok(NULL, " ");
  }
  fclose(fp);
  *x = FALSE;
  printf("\nERRO:[CPF: %lld NAO ENCONTRADO]\n",r.key);

}

void RemoveCPF(Pagina *btree,Record r){

  unsigned long long int path = 0;
  char pathTXT[80];
  int cont = 0;
  char *result;
  char linha[80];
  char aux[80];
  char *pt;
  int x;
  int underflow;
  unsigned long long int new;

  Pesquisa(btree,&r,&path,&x);
  if(x == FALSE){
    printf("CPF NAO LISTADO\n");
    return;
  }
    
  sprintf(pathTXT,"%lld",path); 
  strcat(pathTXT,".txt");
  rename(pathTXT,"./process.txt");

  FILE *fp;
  FILE *fc;
  //int i=0;
  fp = fopen("./process.txt","rw");
  char pathAux[20];

  if(fp == NULL){
    printf("\nProblemas na abertura do arquivo");
    return;                                                                                                                                                                         
  }
  
  while(!feof(fp)){  
    
    result = fgets(linha,80,fp);
    strcpy(aux,linha);  
    pt = strtok(result,"    ,");
  
    if(cont == 10)
      break;
    /*
        O PRIMEIRO CPF (QUE É O NOME DO ARQUIVO), CASO NAO FOR CPF PARA REMOÇÃO, SERÁ O NOME DO NOVO ARQUIVO, 
        NO QUE VAI CRIAR E DEPOIS ABRIR E ESCREVER A PRIMEIRA LINHA.
    */
    if(cont == 0 && atof(pt) != r.key){
     // printf("AQUI 1\n");
      strcpy(pathAux,"./");
      strcat(pathAux,pt);
      strcat(pathAux,".txt");
      new = atof(pt);

      fc = fopen(pathAux,"w");
      fprintf(fc,"%s",aux);

    }
    /*
        CASO O PRIMEIRO CPF(QUE É O NOME DO ARQUIVO), FOR O CPF PARA A REMOÇÃO, JA CHAMAMOS A SEGUNDA LINHA DO ARQUIVO,
        TOKENIZAMOS E CRIAMOS UM ARQUIVO COM ESSE CPF E ABRIMOS E ESCREVEMOS.
    */
    else if(cont == 0 && atof(pt) == r.key){
   
      result = fgets(linha,80,fp);
      strcpy(aux,linha);  
      pt = strtok(result,"    ,");
      cont++;
      strcpy(pathAux,"./");
      strcat(pathAux,pt);
      strcat(pathAux,".txt");
      new = atof(pt);
    
      fc = fopen(pathAux,"w");
      fprintf(fc,"%s",aux);

    }else if(atof(pt) != r.key && cont != 0){  
      fprintf(fc,"%s",aux);
    }
    cont++;
    pt = strtok(NULL, " ");
  }

  /*
    QUANDO O WHILE ACABAR, TEREMOS UM ARQUIVO "PROCESS" E SUA NOVA COPIA,COPIA ESSA COM A REMOÇÃO DO CPF
    ENTAO EXCLUIREMOS O ARQUIVO "PROCESS", COM A FUNÇÃO "remove" E EXCLUIREMOS DA ÁRVORE SEU ANTIGO VALOR DE SENTINELA
    ENTÃO, ADICIONAREMOS O NOVO NOME DO ARQUIVO(VALOR)  DO NOVO ARQUIVO NA ÁRVORE
  */
  fclose(fc);
  fclose(fp);
  printf("CPF REMOVIDO\n");
  
  remove("./process.txt");
  Remove(&btree,path,&underflow);
  Record rr;
  rr.key = new;
  Insere(&btree,rr);
}

void insereCPF(Pagina *btree,Record *r,char nome[20],int idade){

  unsigned long long int path;
  unsigned long long int sentil;
  int x=0;
  int cont=0;
  char *result;
  char linha[80];
  char aux[80];
  char *pt;
  char pathAux[30];
  char pathNew[30];
  int j=0;
  int confere=0;
  int k=0;
  Record rr;
  rr.key = r->key;

  Pesquisa(btree,r,&path,&x);

  sprintf(pathAux,"%lld",path);
  strcat(pathAux,".txt");

  sprintf(pathNew,"%lld",r->key);
  strcat(pathNew,".txt");

  if(x == TRUE){
    printf("\n[ERRO]: CPF JA CADASTRADO");
    return;
  }
  FILE *fp;
  FILE *fnew;
  fnew = fopen(pathNew,"w");
  if(fnew == NULL){
    printf("\nProblemas na abertura do arquivo FNEW: %s",pathNew);
    return;                                                                                                                                                                         
  }

  /*
    ABRO O ARQUIVO ONDE SERIA O MAIS PROVÁVEL DE O CPF ESTAR.
    SO SERÁ INSERIDO NA LISTA CASO O CPF FOR O MENOR DE TODOS E ESTIVER ESPAÇO NO ARQUIVO
  */
  fp = fopen(pathAux,"r");

  if(fp == NULL){
    printf("\nProblemas na abertura do arquivo FP");
    return;                                                                                                                                                                         
  }

   while(!feof(fp)){  

    result = fgets(linha,80,fp);
    strcpy(aux,linha);  
    pt = strtok(result,"    ,");
  
    if(cont == 10)
      break;

    /*
      QUANDO O CPF A SER INSERIDO FOR MENOR QUE O CPF JÁ LISTADO, EU ENTRO NO IF,
       ADICIONO NO ARQUVIO AUXLIAR O CPF A SER INSERIDO E O RESTANTE ABAXO DELE
       CRIANDO ASSIM UM NOVO ARQUIVO TXT COM O CPF INSERIDO COMO CHAVE(NOME DO ARQUIVO) 
       E OS CPFS MAIORES PRESENTE NESSE ARQUIVO

       O J É PARA QUE NA PRIMEIRA VEZ ENTRADO NO IF, ADICIONAR O CPF A SER INSERIDO;
    */
    if( j==0){
      
      fprintf(fnew,"%lld",r->key);
      fprintf(fnew,"%c",',');
      fprintf(fnew,"%s",nome);
      fprintf(fnew,"%c",',');
      fprintf(fnew,"%d",idade);
      fprintf(fnew,"%c",'\n');
      j++;
    }else if(j!=0 && r->key < atof(pt)){
      if(k==0){
        sentil = atof(pt);
        k++;
      }
      fprintf(fnew,"%s",aux);
      confere++;
    }
    cont++;
  }

    fclose(fnew);
    fclose(fp);
    Insere(&btree,rr);
    printf("\nNOVO CPF INSERIDO\n");
  
    if(confere != 0){
  
      char pathNovo[30];
      strcpy(pathNovo,pathAux);
      rename(pathAux,"./excluir.txt");

      FILE *f;
      f = fopen(pathNovo,"w");

       if(f == NULL){
        printf("\nProblemas na abertura do arquivo F");
        return;                                                                                                                                                                         
      }
      free(fp);
      free(result);
      fp = fopen("./excluir.txt","r");
    
      while(!feof(fp)){  
        
        result = fgets(linha,80,fp);
        strcpy(aux,linha);  
        pt = strtok(result,"    ,");
        if(atof(pt) == sentil){
          break;
        }
        fprintf(f,"%s",aux);     
      }
      fclose(fp);
      fclose(f);
      remove("./excluir.txt");
    }
  fclose(fnew);
  fclose(fp);
}