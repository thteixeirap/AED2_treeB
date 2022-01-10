<h1 align="center"> 
 Tree B
</h1>
<h4 align="center">	
  Este trabalho consiste na implementação da estrutura da árvore vermelho-preto, bem como, sua comparação com as árvores binária e AVL.
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
 
![1](https://user-images.githubusercontent.com/78819692/148830027-5b6faf0f-1ebd-46b8-b0ca-189d82577ff6.png)
 
> :exclamation: Caso for do interesse pesquisar outros valores de CPF, basta modificar o vetor que contem esses valores.
 
:point_right: Opção 2:
 
 <p> A opção Remover CPF já vem pre-setadas com os mesmos 3 valores da função Pesquisar. A função RemoveCPF inicia pesquisando se o CPF a ser removido se encontra em algum arquivo de algum registro da árvore, caso encontrando inicia-se o processo de remoção, caso esse CPF não esteja cadastrado nos arquivos, a função retorna. A saída da funçaõ, sabendo que os 3 dados se encontra nos registros, ficaria dessa forma: <p>
 
 ![remove](https://user-images.githubusercontent.com/78819692/148831743-6be8704b-6403-4f98-8757-6d60fa950c4a.png)

  <p> Logo após a remoção desses 3 dados, podemos confirmar a remoção tanto verificando através do código, quanto atraves da visualização abrindo manualmente os arquivos no quais estavam esses dados<p>
 
 > Saída do código após a chamada da função Pesquisar logo apos a remoção dos dados: 
   
 ![remoçaõ2](https://user-images.githubusercontent.com/78819692/148832275-48e7cf63-5e33-4150-86b6-65213a458712.png)

 
 
 
 
