#ifndef LABSOURCE_H_INCLUDED
#define LABSOURCE_H_INCLUDED

typedef struct {
    int N; // Dimens�o do labirinto, lmebre-se que o mesmo � N x N
    int x; // Coordenada x da entrada
    int y; // Coordenada y da entrada
    int sx; // Coordenada x da espada
    int sy; // Coordenada y da espada
    int **mapa; // vari�vel para armazenar o mapa (matriz)
} Labirinto;

Labirinto* LeLabirinto(char * entrada);
int CaminhaLabirintoRecursivo(Labirinto* lab, int x, int y, int ** sol);
int CaminhaLabirintoIterativo(Labirinto* lab, int ** sol);
#endif // LABSOURCE_H_INCLUDED
