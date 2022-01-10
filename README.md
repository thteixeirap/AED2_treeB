<h1 align="center"> 
 Tree B
</h1>
<h4 align="center">	
  Conforme observamos em sala de aula, uma das funções da estrutura em árvore B é prover capacidade de manipulação de inúmeros arquivos, muitas vezes grandes, sob uma hierarquia de sub-conjuntos de entradas menores, cada qual representado por um nó da estrutura. Sua função é simular um banco de dados. Nesse, teremos apenas uma única tabela, composta por nome, idade, cpf que chamaremos de clientes. Nossa tabela deve ter dados aleatórios, o quais podem vir de um banco qualquer da internet ou produzido por vocês a partir de um processo randômico. Teremos nesta tabela 1.000 entradas e cada página da árvore B (i.e., arquivo separado dessa tabela)  sendo representada por 10 dessas entradas de forma ordenada. 

Aplicação: A aplicação de vocês deve ser capaz de mapear esses arquivos com 10 entradas sob o conceito que trabalhamos em sala. Para tanto, considere que cada arquivo seja mapeado por um código que consiga identificar o range de cpfs que estão salvos nele. Nossa árvore tem fator de crescimento m = 2, logo, cada página guardará de 1 a 3 códigos desses. Sua função é prover um menu que consiga: Inserir, Remover e Pesquisar pessoas nesse grupo de arquivos, mantendo sempre a integridade da estrutura e tamanho máximo do arquivo. 
</h4>
<h1></h1>

#### Execução

- Usado o "C/C++ Makefile Project" extensão do VsCode

- Programa criado no Windowns 10, VisualCode
  
  Mudar no arquivo Makefile SRCDIR = "endereço da pasta"
  
  
 Modo de execução:
  
- Abrir pasta do arquivo  ./Arvore_B
- Make
- ArvoreB.exe

<h1></h1>

### Menu 

![menu](https://user-images.githubusercontent.com/78819692/148828871-2aa827c4-250d-4eba-87da-10f5624fee1e.png)

:point_right: Opção 1:

<p> A opção Pesquisar CPF ja vem com os seguintes valores pré-setados a serem procurados a partir do CPF:<p>
 
```sh
 27159570809,Jessé	26 
 18848853902,Caetano	27 
 25352811829,Dominic	38
```
Como temos essas 3 entradas cadastradas em nosso arquivo, teremos como saída o retorno desses dados com o CPF, nome e idade: 
 
 ![saida 1](https://user-images.githubusercontent.com/78819692/148832592-4d3013ff-e6da-4dcf-b26d-88132732fc29.png)

> :exclamation: Caso for do interesse pesquisar outros valores de CPF, basta modificar o vetor que contem esses valores.
 
:point_right: Opção 2:
 
 <p> A opção Remover CPF já vem pre-setadas com os mesmos 3 valores da função Pesquisar. A função RemoveCPF inicia pesquisando se o CPF a ser removido se encontra em algum arquivo de algum registro da árvore, caso encontrando inicia-se o processo de remoção, caso esse CPF não esteja cadastrado nos arquivos, a função retorna. A saída da funçaõ, sabendo que os 3 dados se encontra nos registros, ficaria dessa forma: <p>
 
 ![remove](https://user-images.githubusercontent.com/78819692/148831743-6be8704b-6403-4f98-8757-6d60fa950c4a.png)

  <p> Logo após a remoção desses 3 dados, podemos confirmar a remoção tanto verificando através do código, quanto atraves da visualização abrindo manualmente os arquivos no quais estavam esses dados<p>
 
 - Saída do código após a chamada da função Pesquisar logo apos a remoção dos dados: 
   
 ![remoçaõ2](https://user-images.githubusercontent.com/78819692/148832275-48e7cf63-5e33-4150-86b6-65213a458712.png)

   
 - Para o processo de remoção, utilizamos um arquivo .txt como auxiliar, no qual transcrevemos todos os dados do arquivo onde encontra o CPF a ser removido para o arquivo auxiliar sem esse CPF.  Após o While de leitura desse arquivo, excluiremos esse antigo artigo e adicionamos o novo reescrito, removendo da árvore o valor sentinela(nome do arquivo) desse antigo artigo, e adicionamos novamente o novo valor sentinela (nome do novo arquivo) na árvore.

- Tal recurso de remover e adicionar na árvore novamente foi para caso o CPF a ser removido fosse o valor sentinela(nome do arquivo). Caso não for o valor sentinela, excluiremos e adicionaremos novamente o mesmo valor.
  
> :exclamation: Parte do trecho do While mais detalhado:  
   
```sh
   
   while(!feof(fp)){  
  
    result = fgets(linha,80,fp);
    strcpy(aux,linha);  
    pt = strtok(result,"    ,");
  
    if(cont == 10)
      break;
   
   /* O PRIMEIRO CPF (QUE É O NOME DO ARQUIVO), CASO NAO FOR CPF PARA REMOÇÃO, SERÁ O NOME DO NOVO ARQUIVO, 
        NO QUE VAI CRIAR E DEPOIS ABRIR E ESCREVER A PRIMEIRA LINHA.*/
   
   if(cont == 0 && atof(pt) != r.key){
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
  }
```
   
:point_right: Opção 3:
   
<p Na opção de Inserir, temos ja o seguinte dado pré-setado a ser inserido> <p>
 
 ```sh
  12531656880,Thomas,23
  ```
 - A chamada InserirCPF ocorre em 2 etapas. Primerio chamamos o Pesquisar para ver se o CPF a ser inserido já esta registrado, sendo isso falso, então iniciamos o processo de inserção desse CPF.
 
 - A função Insere foi programada para funcionar a partir de todos os registros de todas as páginas já estarem no seu limite (10 dados). Sendo assim, sempre que vamos inserir um novo dado um novo arquivo txt é criado com o sentinela (nome do arquivo) o cpf desse novo dado, e seu valor é inserido na árvore.
 
 - O problema encontrado foi caso esse novo CPF estiver entre um range de um determinado arquivo, ao inserir esse valor na árvore, teremos problemas para achar valores acima desse novo CPF, pois ao pesquisar um valor um pouco acima desse CPF, iremos abrir o novo arquivo txt porem não ira conter o arquivo procurado.
 
 - :exclamation: Portanto,sempre que adicionamos um novo valor, abriremos o arquivo txt no qual ele tem a maior probabilidade de estar caso estivesse inserido, adicionamos esse CPF no seu novo arquivo txt e tranferimos todos os valores maiores do arquivo que abrimos para o novo arquivo. Depois disso, removemos todos os valores transferidos do arquivo lido, evitando duplicidade de dados.
 
 > EXEMPLO:
 
 <p> Partindo do dado pré setado da função, de acordo com seu CPF  respeitando a ordem crescente do arquivo, ele estaria entre os CPFS 12429608473 e 12531656899:
  
  ![antes](https://user-images.githubusercontent.com/78819692/148844449-f01180ac-e9ee-4708-9d4b-99606667969d.png)

  
  <p> Portanto, para respeitar a ordem crescente dos arquivos, no qual ajuda a achar esse CPF dentro deles, criamos um arquivo com esse novo CPF e organizamos os dados entre os dois arquivos:<p>
   
 ![depois](https://user-images.githubusercontent.com/78819692/148844864-af18e319-58f8-4148-9f7a-24d577b7f1f0.png)

  . A Saída do código após o comando Inserir CPF:
   
 ![op3](https://user-images.githubusercontent.com/78819692/148845044-8ea73e37-f7ce-4a9f-912d-782526ff0976.png)

   <p> Primeiro verificamos se o CPF a ser inserido realmente não se encontra nos registros, caso realmente não esteja iniciamos a inserção e após sua confirmação realizamos novamente a Pesquisa desse CPF<p>
