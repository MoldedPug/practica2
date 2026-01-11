#ifndef JOC_H
#define JOC_H

#include "tauler.h"

// Codis de resultat de tir
#define RESULTAT_AIGUA 0
#define RESULTAT_TOCAT 1
#define RESULTAT_ENFONSAT 2
#define RESULTAT_INVALID -1

// Funcions del joc
int processar_coordenades(char *entrada, int *fila, int *col);
int processar_tir(int tauler[MIDA][MIDA], int tauler_jugador[MIDA][MIDA], int fila, int col);
int comprovar_enfonsat(int tauler[MIDA][MIDA], int tauler_jugador[MIDA][MIDA], int fila, int col);
int comprovar_victoria(int tauler[MIDA][MIDA], int tauler_jugador[MIDA][MIDA]);
char llegir_opcio_SN();
int llegir_opcio_numero(int min, int max);

#endif