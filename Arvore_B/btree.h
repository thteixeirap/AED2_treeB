#ifndef BTREE_H 
#define BTREE_H

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#define M 1
#define MM 3

#define FALSE 0
#define TRUE  1

#define LEN 1001

typedef struct Record Record;
typedef struct Pagina Pagina;
typedef struct Control Control;

struct Record {
  unsigned long long int key;
};

struct Pagina {
  short n;
  Record r[MM];
  Pagina *p[MM + 1];
};

//unsigned long long int elementoEntre[1];

Pagina* CreateBTree();

void Pesquisa(Pagina *p, Record *r,unsigned long long int *path,int *x);
void InsereNaPagina(Pagina *p, Pagina *pdir, Record r);
void InsertFixUp(Pagina **p, Pagina **pr, Record r, Record *rr, short *Overflow);
void Insere(Pagina **p, Record r);

void RemoveFixUp(Pagina *p, Pagina *pai, int PosPai, int *underflow);
void Antecessor(Pagina *p, int i, Pagina *pai, int *underflow);
void Remove(Pagina **p,unsigned long long int key, int *underflow);

void Imprime(Pagina **p, int level);

void IniciaEntradas(Pagina **p,Record r);
void PesquisaArquivo(unsigned long long int cpf,Record r,int *x);
void RemoveCPF(Pagina *btree,Record r);
void insereCPF(Pagina *btree,Record *r,char nome[20],int idade);

#endif