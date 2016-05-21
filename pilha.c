#include<stdlib.h>
#include<stdio.h>
#include"pilha.h"

/*------------------------------------------------------------
Protótipo: void criaPilha(Pilha **P);
Função: cria uma nova pilha vazia
Entrada: estrutura Pilha
Saída: void
------------------------------------------------------------*/
void criaPilha(Pilha **P){
      (*P) = NULL;
}
/*------------------------------------------------------------
Protótipo: void Push(Pilha **P, Ponto q);
Função: insere um novo elemento q na pilha P. Neste caso, um
ponto da matriz.
Entrada: Pilha P, ponto q de coordenadas x, y;
Saída: void
------------------------------------------------------------*/
void Push(Pilha** P, Ponto q){
      if(!(*P)){
          (*P) = malloc(sizeof(Pilha));
          (*P)->coord = q;
          (*P)->prox = NULL;
          return;
      }
      Pilha* aux = malloc(sizeof(Pilha));
      aux->coord = q;
      aux->prox = (*P);
      (*P) = aux;
}
/*------------------------------------------------------------
Protótipo: void Pop(Pilha **P);
Função: remove o último elemento da pilha P
Entrada: Pilha P
Saída: void
------------------------------------------------------------*/
void Pop(Pilha** P){
      if((*P)){
          Pilha* aux = (*P)->prox;
          free((*P));
          (*P) = aux;
      }
}
/*------------------------------------------------------------
Protótipo: Ponto Peek(Pilha **P);
Função: retira o último elemento da pilha P
Entrada: Pilha P
Saída: Ponto
------------------------------------------------------------*/
Ponto Peek(Pilha** P){
      return (*P)->coord;
}
/*------------------------------------------------------------
Protótipo: void freePilha(Pilha *P);
Função: desaloca a memória usada pela estrutura no fim do programa
Entrada: Pilha P
Saída: void
------------------------------------------------------------*/
void freePilha(Pilha **P){
      while(*P){
          Pop(P);
    }
}
