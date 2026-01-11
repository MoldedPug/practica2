#include <stdio.h>
#include "tauler.h"
#include "vaixells.h"
#include "joc.h"

int main() {
    int tauler[MIDA][MIDA];
    int tauler_jugador[MIDA][MIDA];
    int jugar = 1;
    
    // Bucle principal: jugar múltiples partides
    while (jugar) {
        // 1. PRESENTACIÓ
        printf("************************\n");
        printf("** ENFONSAR LA FLOTA! **\n");
        printf("************************\n\n");
        
        // 2. ESCOLLIR FLOTA
        printf("Escull una flota:\n");
        printf("1: L'Armada Vencible\n");
        printf("2: Els Brivalls\n");
        printf("3: La Flotilla\n");
        printf("Introdueix el número de la flota (1-3): ");
        int tipus_flota = llegir_opcio_numero(1, 3);
        
        // 3. GENERAR TAULER
        int tauler_generat = 0;
        while (!tauler_generat) {
            printf("\nPreparant tauler de la flota %d...\n", tipus_flota);
            inicialitzar_tauler(tauler);
            inicialitzar_tauler(tauler_jugador);
            generar_flota(tauler, tipus_flota);
            printf("Tauler generat.\n");
            
            // Opció de veure el tauler (trampes)
            printf("Vols fer trampes i veure el tauler generat? (S/N): ");
            if (llegir_opcio_SN() == 'S') {
                mostrar_tauler(tauler, 1); // Mostrar amb vaixells
            }
            
            // Opció de regenerar
            printf("\nVols generar un nou tauler? (S/N): ");
            if (llegir_opcio_SN() == 'N') {
                tauler_generat = 1;
            }
        }
        
        // 4. BUCLE DE JOC
        printf("\nComença la partida...\n\n");
        int partida_acabada = 0;
        int num_tirs = 0;
        
        while (!partida_acabada) {
            // Demanar coordenades
            char entrada[10];
            int fila, col;
            int coordenades_valides = 0;
            
            while (!coordenades_valides) {
                printf("Introdueix coordenades (ex: A5): ");
                scanf("%s", entrada);
                
                if (processar_coordenades(entrada, &fila, &col)) {
                    coordenades_valides = 1;
                } else {
                    printf("Coordenades invàlides. Usa format A-J i 1-10.\n");
                }
            }
            
            // Processar tir
            int resultat = processar_tir(tauler, tauler_jugador, fila, col);
            num_tirs++;
            
            if (resultat == RESULTAT_INVALID) {
                printf("Ja has disparat aquí!\n");
                num_tirs--; // No comptar tir invàlid
            } else if (resultat == RESULTAT_AIGUA) {
                printf("Aigua!\n");
            } else if (resultat == RESULTAT_TOCAT) {
                printf("Tocat!\n");
            } else if (resultat == RESULTAT_ENFONSAT) {
                printf("Tocat i enfonsat!\n");
            }
            
            // Mostrar tauler actualitzat
            mostrar_tauler(tauler_jugador, 0);
            
            // Comprovar victòria
            if (comprovar_victoria(tauler, tauler_jugador)) {
                printf("\nFelicitats! Has enfonsat tota la flota en %d tirades!\n", num_tirs);
                mostrar_tauler(tauler_jugador, 1); // Mostrar tauler final complet
                partida_acabada = 1;
            }
        }
        
        // 5. PREGUNTAR NOVA PARTIDA
        printf("\nVols jugar una nova partida? (S/N): ");
        if (llegir_opcio_SN() == 'N') {
            jugar = 0;
        }
        printf("\n");
    }
    
    printf("Gràcies per jugar!\n");
    return 0;
}