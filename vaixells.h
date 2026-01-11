#ifndef VAIXELLS_H
#define VAIXELLS_H

#include "tauler.h"

// Tipus de vaixells
#define PORTAAVIONS 5
#define CUIRASSAT 4
#define DESTRUCTOR 3
#define FRAGATA 2
#define SUBMARI 1

// Orientacions
#define HORITZONTAL 0
#define VERTICAL 1

// Configuracions de flotes
typedef struct {
    int portaavions;
    int cuirassats;
    int destructors;
    int fragates;
    int submarins;
} Flota;

// Funcions de vaixells
/*
    obtenir_configuracio_flota : Per saber quin tipus de flota tindrem passem el nom 
    1: L'Armada Vencible,  2: Els Brivalls,  3: La Flotilla.
*/ 
void obtenir_configuracio_flota(int tipus, Flota *flota);
int es_posicio_valida(int tauler[MIDA][MIDA], int fila, int col, int mida, int orientacio);
// Millor sense dieresi (per compatibilitat)
#endif