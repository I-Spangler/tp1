#include<stdlib.h>
#include<stdio.h>
#include"labsource.h"

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
/*------------------------------------------------------------
Protótipo: Labirinto* LeLabirinto(char *entrada);
Função: abre um arquivo, lê os dados do arquivo e os grava em
uma estrutura Labirinto de acordo.
Entrada: uma string correspontente ao nome do arquivo
Saída: um Labirinto com as coordenadas e o mapa dados no arquivo
------------------------------------------------------------*/
Labirinto* LeLabirinto(char *entrada){

      FILE *fp;
      fp = fopen(entrada, "r");
      if(!fp){
          fprintf(stderr, "Erro: arquivo nao aberto\n");
          return NULL;
      }
      Labirinto* lab;
      lab = malloc(sizeof(Labirinto));
      fscanf(fp, "%d %d %d %d %d", &lab->N, &lab->x, &lab->y, &lab->sx, &lab->sy);
      lab->mapa = calloc(lab->N, (sizeof(int*)));
      int i, j;
      for(i=0; i<lab->N; i++){
          lab->mapa[i] = calloc(lab->N, (sizeof(int)));
          for(j=0; j<lab->N; j++){
              fscanf(fp, "%d", &lab->mapa[i][j]);
          }
      }
      fclose(fp);
      return lab;
}
/*------------------------------------------------------------
Protótipo: int CaminhaLabirintoRecursivo(Labirinto* lab, int x, int y, int **sol);
Função: percorre o mapa do labirinto lab recursivamente e
grava sua solução na matriz sol.
Entrada: um Labirinto, coordenadas x e y da posição atual, matriz
solução
Saída: um inteiro 1 ou 0, 1 se o caminho até a espada existir e
0 se não existir.
------------------------------------------------------------*/
int CaminhaLabirintoRecursivo(Labirinto* lab, int x, int y, int ** sol){
      if(x == lab->sx && y == lab->sy){
          sol[x][y] = 1;
      return 1;
      }
      else if(lab->mapa[x][y] == 0 && sol[x][y] == 0){
          sol[x][y] = 1;
      if(y+1 < lab->N && CaminhaLabirintoRecursivo(lab, x, y+1, sol) !=0){
          return 1;
      }
      else if(x+1 < lab->N && CaminhaLabirintoRecursivo(lab, x+1, y, sol) !=0){
          return 1;
      }
      else if(y-1 > 0 && CaminhaLabirintoRecursivo(lab, x, y-1, sol) !=0){
          return 1;
      }
      else if(x-1 > 0 && CaminhaLabirintoRecursivo(lab, x-1, y, sol) !=0){
          return 1;
      }
      sol[x][y] = 0;
        //para preservar a elegância da solução, se o ramo de recursão
        //encontrar um beco sem saída, o caminho volta a ser 0 no mapa
        //da solução
      }
      return 0;
}
/*------------------------------------------------------------
Protótipo: int CaminhaLabirintoIterativo(Labirinto* lab, int **sol);
Função: percorre o mapa do labirinto, gravando cada coordenada
em uma pilha P, com uma pilha auxiliar hold,
 até que se ache ou não um caminho válido
Entrada: um Labirinto lab, uma matriz solução sol
Saída: um inteiro 1 ou 0 indicando se há ou não solução
------------------------------------------------------------*/
int CaminhaLabirintoIterativo(Labirinto* lab, int ** sol){
      Pilha *P; //P é o novelo. a linha salvadora do labirinto
      Pilha *hold; //hold é a Pilha de lugares onde teseu encontra bifurcações
      int ncaminhos; //número de possibilidades a partir de um ponto
    	Ponto q;   //posição de teseu
    	q.x = lab->x; //início
    	q.y = lab->y;
      criaPilha(&P); criaPilha(&hold);
    	Push(&P, q); //teseu prende o fio na entrada do labirinto
      while(q.x != lab->sx || q.y != lab->sy){ //enquanto ele não chegar ao fim
      		q = Peek(&P);  //o ponto onde ele está é a ponta do fio
      		lab->mapa[q.x][q.y] = 1;  //ele marca este ponto como já visitado no mapa original
          ncaminhos = 0;
          if(q.y+1 < lab->N && lab->mapa[q.x][q.y+1] == 0){  //teseu procura um caminho a direita
          		Ponto q1 = q;
          		q1.y = q.y+1;
              Push(&P, q1);
              ncaminhos++;
          }
          if(q.x+1 < lab->N && lab->mapa[q.x+1][q.y] == 0){ //teseu procura um caminho abaixo
          		Ponto q1 = q;
          		q1.x = q.x+1;
              Push(&P, q1);
              ncaminhos++;
          }
          if(q.y-1 > 0 && lab->mapa[q.x][q.y-1] == 0){ //teseu procura um caminho a esquerda
        			Ponto q1 = q;
        			q1.y = q.y-1;
              Push(&P, q1);
              ncaminhos++;
          }
          if(q.x-1 > 0 && lab->mapa[q.x-1][q.y] == 0){ //teseu procura um caminho acima
        			Ponto q1 = q;
        			q1.x = q.x-1;
              Push(&P, q1);
              ncaminhos++;
          }
          if(ncaminhos > 1){ //se for bifurcação, marca o lugar na hold pra visitar depois
              Push(&hold, q);
          }
      		if(!ncaminhos){  //se encontrar um beco sem saída
              if(q.x == lab->sx && q.y == lab->sy)
                  break;
              if(!(hold)){  //e não houver mais encruzilhadas pra visitar
                  freePilha(&hold);
                  freePilha(&P);
          			  return 0; //não há saída. ninguém retornará. ele está preso para sempre.
          		}
              while(P->coord.x != hold->coord.x || P->coord.y != hold->coord.y){  //se houver
                  Pop(&P); //ele enrola o fio de volta no novelo até a encruzilhada mais recente
              }
              Pop(&hold); //desmarca a encruzilhada
          }
      }
      while(P){
          sol[P->coord.x][P->coord.y] = 1; //teseu chegou ao seu destino. o caminho do fio é anotado no mapa da solução
          Pop(&P);
      }
      freePilha(&hold); //hold não é mais necessária
      freePilha(&P); //a utilidade do fio chega ao fim
      return 1;  // 1 homem, o nosso herói, retorna, vitorioso.
}
