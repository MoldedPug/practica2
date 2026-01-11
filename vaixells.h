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

#endif