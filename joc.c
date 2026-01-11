#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "joc.h"
#include "vaixells.h"

// Processa les coordenades introduïdes per l'usuari (ex: "A5")
int processar_coordenades(char *entrada, int *fila, int *col) {
    int len = strlen(entrada);
    
    // 1. Comprovar longitud (ha de ser 2 o 3 caràcters: A5 o A10)
    if (len < 2 || len > 3) {
        return 0;
    }
    
    // 2. Primer caràcter ha de ser lletra A-J (majúscula o minúscula)
    char lletra = toupper(entrada[0]);
    if (lletra < 'A' || lletra > 'J') {
        return 0;
    }
    *col = lletra - 'A'; // Convertir A=0, B=1, ..., J=9
    
    // 3. Resta de caràcters han de ser número 1-10
    int num = atoi(&entrada[1]);
    if (num < 1 || num > 10) {
        return 0;
    }
    *fila = num - 1; // Convertir 1-10 a 0-9
    
    // 4. Validar que fila i col estan dins 0-9
    if (*fila < 0 || *fila >= MIDA || *col < 0 || *col >= MIDA) {
        return 0;
    }
    
    return 1; // OK
}

// Processa un tir i retorna el resultat
int processar_tir(int tauler[MIDA][MIDA], int tauler_jugador[MIDA][MIDA], int fila, int col) {
    // Si ja s'ha disparat aquí (tauler_jugador != 0):
    if (tauler_jugador[fila][col] != AIGUA) {
        return RESULTAT_INVALID;
    }
    
    // Si és AIGUA (tauler[fila][col] == 0):
    if (tauler[fila][col] == AIGUA) {
        tauler_jugador[fila][col] = AIGUA_TOCADA; // 2
        return RESULTAT_AIGUA;
    }
    
    // Si és VAIXELL (tauler[fila][col] == 1):
    if (tauler[fila][col] == VAIXELL) {
        tauler_jugador[fila][col] = VAIXELL; // 1
        
        // Comprovar si s'ha enfonsat
        if (comprovar_enfonsat(tauler, tauler_jugador, fila, col)) {
            return RESULTAT_ENFONSAT;
        } else {
            return RESULTAT_TOCAT;
        }
    }
    
    return RESULTAT_INVALID; // No hauria de passar mai
}

// Comprova si s'ha enfonsat un vaixell complet
int comprovar_enfonsat(int tauler[MIDA][MIDA], int tauler_jugador[MIDA][MIDA], int fila, int col) {
    int orientacio = -1; // -1=desconeguda, 0=horitzontal, 1=vertical
    int fila_inici, col_inici, mida;
    int i;
    
    // 1. Determinar l'orientació del vaixell (buscar adjacents)
    // Mirar esquerra/dreta
    if ((col > 0 && tauler[fila][col - 1] == VAIXELL) || 
        (col < MIDA - 1 && tauler[fila][col + 1] == VAIXELL)) {
        orientacio = HORITZONTAL;
    }
    // Mirar dalt/baix
    else if ((fila > 0 && tauler[fila - 1][col] == VAIXELL) || 
             (fila < MIDA - 1 && tauler[fila + 1][col] == VAIXELL)) {
        orientacio = VERTICAL;
    }
    // Si no hi ha adjacents, és un vaixell de mida 1
    else {
        orientacio = HORITZONTAL; // Pot ser qualsevol, és mida 1
    }
    
    // 2. Trobar l'inici i final del vaixell
    if (orientacio == HORITZONTAL) {
        // Trobar inici (anar cap a l'esquerra)
        col_inici = col;
        while (col_inici > 0 && tauler[fila][col_inici - 1] == VAIXELL) {
            col_inici--;
        }
        fila_inici = fila;
        
        // Calcular mida (anar cap a la dreta)
        mida = 0;
        i = col_inici;
        while (i < MIDA && tauler[fila][i] == VAIXELL) {
            mida++;
            i++;
        }
    } else { // VERTICAL
        // Trobar inici (anar cap a dalt)
        fila_inici = fila;
        while (fila_inici > 0 && tauler[fila_inici - 1][col] == VAIXELL) {
            fila_inici--;
        }
        col_inici = col;
        
        // Calcular mida (anar cap a baix)
        mida = 0;
        i = fila_inici;
        while (i < MIDA && tauler[i][col] == VAIXELL) {
            mida++;
            i++;
        }
    }
    
    // 3. Comprovar que TOTES les caselles del vaixell estan tocades
    int totes_tocades = 1;
    for (i = 0; i < mida; i++) {
        int f, c;
        if (orientacio == HORITZONTAL) {
            f = fila_inici;
            c = col_inici + i;
        } else { // VERTICAL
            f = fila_inici + i;
            c = col_inici;
        }
        
        if (tauler_jugador[f][c] != VAIXELL) {
            totes_tocades = 0;
            break;
        }
    }
    
    // 4. Si totes tocades → omplir aigua i retornar 1
    if (totes_tocades) {
        omplir_aigua_voltant(tauler_jugador, fila_inici, col_inici, mida, orientacio);
        return 1;
    }
    
    // 5. Si no → retornar 0
    return 0;
}

// Comprova si s'han enfonsat tots els vaixells
int comprovar_victoria(int tauler[MIDA][MIDA], int tauler_jugador[MIDA][MIDA]) {
    int f, c;
    
    // Recórrer tot el tauler
    for (f = 0; f < MIDA; f++) {
        for (c = 0; c < MIDA; c++) {
            // Si el tauler original té VAIXELL però el jugador no l'ha tocat
            if (tauler[f][c] == VAIXELL && tauler_jugador[f][c] != VAIXELL) {
                return 0; // Encara queden vaixells sense enfonsar
            }
        }
    }
    
    // Si arriba aquí, tots els vaixells han estat tocats
    return 1; // VICTÒRIA! 🎉
}

// Llegeix una opció S/N
char llegir_opcio_SN() {
    char opcio;
    int valid = 0;
    
    while (!valid) {
        scanf(" %c", &opcio);
        while (getchar() != '\n'); // Netejar buffer
        
        opcio = toupper(opcio);
        if (opcio == 'S' || opcio == 'N') {
            valid = 1;
        } else {
            printf("Opció invàlida. Introdueix S o N: ");
        }
    }
    return opcio;
}

// Llegeix un número dins d'un rang
int llegir_opcio_numero(int min, int max) {
    int num;
    int valid = 0;
    
    while (!valid) {
        if (scanf("%d", &num) != 1) {
            while (getchar() != '\n'); // Netejar buffer
            printf("Entrada invàlida. Introdueix un número entre %d i %d: ", min, max);
        } else if (num < min || num > max) {
            printf("Número fora de rang. Introdueix entre %d i %d: ", min, max);
        } else {
            valid = 1;
        }
    }
    return num;
}