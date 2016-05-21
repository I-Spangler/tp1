#include <stdlib.h>
#include <stdio.h>
#include "labsource.h"

int main(int argc, char *argv[]){

  Labirinto* lab;
  lab  = LeLabirinto(argv[1]);
  int **sol, i, j; //sol = matriz da solução
  sol = calloc(lab->N, (sizeof(int*)));
  for(i = 0; i<lab->N; i++){
      sol[i] = calloc(lab->N, (sizeof(int)));
      for(j = 0; j<lab->N; j++){
          sol[i][j] = 0;
      }
  }
  FILE *fp;
  fp = fopen(argv[2], "w");
  if(strcmp(argv[3],"0") == 0){
      if(CaminhaLabirintoRecursivo(lab, lab->x, lab->y, sol)){
        for(i = 0; i<lab->N; i++){
              for(j = 0; j<lab->N; j++){
                  fprintf(fp, "%d ", sol[i][j]);
              }
             fprintf(fp, "\n");
           }
      }
      else {
           fprintf(fp, "0");
      }
  }
  else if(strcmp(argv[3], "1") == 0){
      if(CaminhaLabirintoIterativo(lab, sol)){
     for(i = 0; i<lab->N; i++){
           for(j = 0; j<lab->N; j++){
               fprintf(fp, "%d ", sol[i][j]);
           }
          fprintf(fp, "\n");
        }
      }
      else {
        fprintf(fp, "0");
      }
  }
  //libera tudo
  for(i = 0; i<lab->N; i++){
    free(lab->mapa[i]);
    free(sol[i]);
  }
  free(sol); free(lab->mapa); free(lab);
  fclose(fp);
return 0;
}
