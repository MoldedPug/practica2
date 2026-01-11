#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vaixells.h"

// Retorna la configuració d'una flota segons el tipus (1, 2 o 3)
void obtenir_configuracio_flota(int tipus, Flota *flota) {
    if (tipus == 1){
        flota->portaavions = 1; 
        flota->cuirassats = 1; 
        flota->destructors = 2; 
        flota->fragates = 2; 
        flota->submarins = 3; 

    } else if (tipus == 2){
        flota->portaavions = 0; 
        flota->cuirassats = 1; 
        flota->destructors = 2; 
        flota->fragates = 3; 
        flota->submarins = 4; 

    } else if (tipus == 3){
        flota->portaavions = 0; 
        flota->cuirassats = 0 ; 
        flota->destructors = 2; 
        flota->fragates = 3; 
        flota->submarins = 4; 
    } else {
        // Configuració per defecte (tot a 0)
        flota->portaavions = 0;
        flota->cuirassats = 0;
        flota->destructors = 0;
        flota->fragates = 0;
        flota->submarins = 0;
        return -1;
    }
}

// Comprova si un vaixell es pot col·locar en aquesta posició
int es_posicio_valida(int tauler[MIDA][MIDA], int fila, int col, int mida, int orientacio) {
    // 1. Comprovar que no es surt del tauler
    if (orientacio == HORITZONTAL) { // Basicament es surt per la dreta?
        if (col + mida > MIDA) return 0;
    } else {  // VERTICAL
        if (fila + mida > MIDA) return 0; 
    }
    
    // 2 i 3. Comprovar que les caselles del vaixell i voltant estan lliures
    for (int i = 0; i < mida; i++) {
        int f, c;
        
        // Calcular fila i columna segons orientació
        if (orientacio == VERTICAL) {
            f = fila + i;
            c = col;
        } else {  // HORITZONTAL
            f = fila;
            c = col + i;
        }
        
        // Comprovar casella del vaixell
        if (tauler[f][c] != AIGUA) return 0; // Hi ha un altre vaixell aquí?
        
        // Comprovar les 8 caselles adjacents
        for (int df = -1; df <= 1; df++) {
            for (int dc = -1; dc <= 1; dc++) {
                int nf = f + df;
                int nc = c + dc;

                /*
                "Els vaixells es poden col·locar en horitzontal o en vertical,
                 i no es poden tocar en cap casella (ni en diagonal)" pg: 1

                [-1,-1] [-1,0] [-1,+1]    ←  Fila de dalt
                [ 0,-1] [ F,C] [ 0,+1]    ←  Fila actual (la nostra casella)
                [+1,-1] [+1,0] [+1,+1]    ←  Fila de baix
                
                Recordem que aquesta funció és només per la generació del tauler:
                    Vaixells no es toquen → es_posicio_valida comprova voltant

                Durant el joc: Quan s'enfonsa → omplir_aigua_voltant posa 2 (aigua tocada)
                */
                
                // Si està dins dels límits del tauler
                if (nf >= 0 && nf < MIDA && nc >= 0 && nc < MIDA) {
                    // Si NO és aigua → posició no vàlida
                    if (tauler[nf][nc] != AIGUA) return 0;
                }
            }
        }
    }
    
    return 1;  // Tot OK, posició vàlida
}
// Col·loca un vaixell al tauler
void col·locar_vaixell(int tauler[MIDA][MIDA], int fila, int col, int mida, int orientacio) {
    int i;
    
    if (orientacio == HORITZONTAL) {
        // Recórrer columnes: col, col+1, col+2, ..., col+mida-1
        for (i = 0; i < mida; i++) {
            tauler[fila][col + i] = VAIXELL;
        }
    } else { // VERTICAL
        // Recórrer files: fila, fila+1, fila+2, ..., fila+mida-1
        for (i = 0; i < mida; i++) {
            tauler[fila + i][col] = VAIXELL;
        }
    }
}

// Omple d'aigua (2) les caselles al voltant d'un vaixell enfonsat
void omplir_aigua_voltant(int tauler[MIDA][MIDA], int fila_inici, int col_inici, int mida, int orientacio) {
    // Per cada casella del vaixell:
    //   Omplir les 8 caselles adjacents amb AIGUA_TOCADA (2)
    //   (només si estan dins del tauler i són AIGUA (0))
}

// Genera tots els vaixells d'una flota aleatòriament
void generar_flota(int tauler[MIDA][MIDA], int tipus_flota) {
    Flota flota;
    obtenir_configuracio_flota(tipus_flota, &flota);
    
    srand(time(NULL)); // Inicialitzar aleatorietat
    
    // Per cada tipus de vaixell (del més gran al més petit):
    //   - Portaavions (mida 5): repetir flota.portaavions vegades
    //   - Cuirassat (mida 4): repetir flota.cuirassats vegades
    //   - etc.
    
    // Per cada vaixell:
    //   int col·locat = 0;
    //   while (!col·locat) {
    //     int fila = rand() % MIDA;
    //     int col = rand() % MIDA;
    //     int orientacio = rand() % 2; // 0 o 1
    //     
    //     if (es_posicio_valida(tauler, fila, col, mida_vaixell, orientacio)) {
    //       col·locar_vaixell(tauler, fila, col, mida_vaixell, orientacio);
    //       col·locat = 1;
    //     }
    //   }
}