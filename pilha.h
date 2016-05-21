#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED

typedef struct {
    int x;
    int y;
}Ponto;

typedef struct Pilha{
    Ponto coord;
    struct Pilha *prox;
}Pilha;

void criaPilha(Pilha **P);
Ponto Peek(Pilha** P);
void Push(Pilha **P, Ponto q);
void Pop(Pilha **P);
void freePilha(Pilha **P);


#endif // PILHA_H_INCLUDED
