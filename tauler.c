#include <stdio.h>
#include "tauler.h"

// Primer comencem per probar que funciona tota la taula
void inicialitzar_tauler(int tauler[MIDA][MIDA]) {
    for (int i = 0; i < MIDA; i++) {  // CANVI: <= per < aquest error l'he repetit varies vegades ja modificat
       for (int j = 0; j < MIDA; j++){  // CANVI: <= per <
            tauler[i][j]= AIGUA;
       }
    }
}

// Mostra el tauler per pantalla
void mostrar_tauler(int tauler[MIDA][MIDA], int mostrar_vaixells) {
    // Imprimir capçalera:  " | A B C D E F G H I J"
    printf("   | A B C D E F G H I J\n");
    printf("---+--------------------\n");

    for (int i = 0; i < MIDA; i++){  // CANVI: <= per <
        printf("%2d | ", i + 1); // Imprimir número de fila, el 2d es per tema espais.
        
        for (int j = 0; j < MIDA; j++){  // CANVI: i++ per j++, <= per <
            
            if (mostrar_vaixells == 1){
                // Mostrar tot
                if (tauler[i][j] == AIGUA) printf("~ ");
                else if (tauler[i][j] == VAIXELL) printf("V ");
                else if (tauler[i][j] == AIGUA_TOCADA) printf("O ");
                else if (tauler[i][j] == VAIXELL_TOCAT) printf("X ");
            }
            if (mostrar_vaixells == 0){
                // Amagar vaixells
                if (tauler[i][j] == AIGUA || tauler[i][j] == VAIXELL) printf("~ ");
                else if (tauler[i][j] == AIGUA_TOCADA) printf("O ");
                else if (tauler[i][j] == VAIXELL_TOCAT) printf("X ");
            }
        }
        printf("\n");  // AFEGIT: salt de línia
    }
}

// Copia un tauler a un altre
void copiar_tauler(int origen[MIDA][MIDA], int desti[MIDA][MIDA]) {
    // Recórrer i copiar cada casella
}