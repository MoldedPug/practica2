#ifndef TAULER_H
#define TAULER_H

// Les constants del joc
#define MIDA 10
#define AIGUA 0
#define VAIXELL 1
#define AIGUA_TOCADA 2

// Les funcions del tauler
void inicialitzar_tauler(int tauler[MIDA][MIDA]);
void mostrar_tauler(int tauler[MIDA][MIDA], int mostrar_vaixells);
void copiar_tauler(int origen[MIDA][MIDA], int desti[MIDA][MIDA]);

#endif