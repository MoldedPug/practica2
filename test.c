#include <stdio.h>
#include <string.h>
#include "tauler.h"
#include "vaixells.h"
#include "joc.h"

// Colors per terminal (opcional)
#define COLOR_RESET   "\033[0m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_RED     "\033[31m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"

// Comptadors de tests
int tests_passed = 0;
int tests_failed = 0;

// Funció auxiliar per imprimir resultats
void test_result(char *nom_test, int resultat_esperat, int resultat_obtingut) {
    if (resultat_esperat == resultat_obtingut) {
        printf("%s✓ PASS%s: %s\n", COLOR_GREEN, COLOR_RESET, nom_test);
        tests_passed++;
    } else {
        printf("%s✗ FAIL%s: %s (esperat: %d, obtingut: %d)\n", 
               COLOR_RED, COLOR_RESET, nom_test, resultat_esperat, resultat_obtingut);
        tests_failed++;
    }
}

void test_header(char *nom_modul) {
    printf("\n%s========================================%s\n", COLOR_BLUE, COLOR_RESET);
    printf("%s  TEST: %s%s\n", COLOR_BLUE, nom_modul, COLOR_RESET);
    printf("%s========================================%s\n", COLOR_BLUE, COLOR_RESET);
}

// ============================================
// TESTS DE TAULER.C
// ============================================

void test_tauler() {
    test_header("MÒDUL TAULER");
    
    int tauler[MIDA][MIDA];
    int tauler2[MIDA][MIDA];
    int i, j;
    
    // TEST 1: inicialitzar_tauler
    inicialitzar_tauler(tauler);
    int tot_aigua = 1;
    for (i = 0; i < MIDA; i++) {
        for (j = 0; j < MIDA; j++) {
            if (tauler[i][j] != AIGUA) {
                tot_aigua = 0;
            }
        }
    }
    test_result("inicialitzar_tauler() omple tot d'aigua", 1, tot_aigua);
    
    // TEST 2: copiar_tauler
    tauler[0][0] = VAIXELL;
    tauler[5][5] = AIGUA_TOCADA;
    copiar_tauler(tauler, tauler2);
    int copia_correcta = (tauler2[0][0] == VAIXELL && tauler2[5][5] == AIGUA_TOCADA);
    test_result("copiar_tauler() copia correctament", 1, copia_correcta);
    
    // TEST 3: mostrar_tauler (només comprovem que no peta)
    printf("\n--- Test visual de mostrar_tauler (hauria de mostrar-se bé) ---\n");
    inicialitzar_tauler(tauler);
    tauler[0][0] = VAIXELL;
    tauler[1][1] = AIGUA_TOCADA;
    mostrar_tauler(tauler, 1);
    printf("--- Fi del test visual ---\n\n");
}

// ============================================
// TESTS DE VAIXELLS.C
// ============================================

void test_vaixells() {
    test_header("MÒDUL VAIXELLS");
    
    int tauler[MIDA][MIDA];
    Flota flota;
    int i, j;
    
    // TEST 1: obtenir_configuracio_flota - Flota 1
    obtenir_configuracio_flota(1, &flota);
    int flota1_ok = (flota.portaavions == 1 && flota.cuirassats == 1 && 
                     flota.destructors == 2 && flota.fragates == 2 && flota.submarins == 3);
    test_result("obtenir_configuracio_flota(1) - L'Armada Vencible", 1, flota1_ok);
    
    // TEST 2: obtenir_configuracio_flota - Flota 2
    obtenir_configuracio_flota(2, &flota);
    int flota2_ok = (flota.portaavions == 0 && flota.cuirassats == 1 && 
                     flota.destructors == 2 && flota.fragates == 3 && flota.submarins == 4);
    test_result("obtenir_configuracio_flota(2) - Els Brivalls", 1, flota2_ok);
    
    // TEST 3: obtenir_configuracio_flota - Flota 3
    obtenir_configuracio_flota(3, &flota);
    int flota3_ok = (flota.portaavions == 0 && flota.cuirassats == 0 && 
                     flota.destructors == 2 && flota.fragates == 3 && flota.submarins == 4);
    test_result("obtenir_configuracio_flota(3) - La Flotilla", 1, flota3_ok);
    
    // TEST 4: es_posicio_valida - Posició vàlida
    inicialitzar_tauler(tauler);
    int valid = es_posicio_valida(tauler, 0, 0, 3, HORITZONTAL);
    test_result("es_posicio_valida() - posició vàlida (0,0, mida 3, H)", 1, valid);
    
    // TEST 5: es_posicio_valida - Fora de límits
    valid = es_posicio_valida(tauler, 0, 8, 3, HORITZONTAL); // Es surt per la dreta
    test_result("es_posicio_valida() - fora de límits (0,8, mida 3, H)", 0, valid);
    
    // TEST 6: es_posicio_valida - Sobre altre vaixell
    col·locar_vaixell(tauler, 0, 0, 3, HORITZONTAL);
    valid = es_posicio_valida(tauler, 0, 2, 2, VERTICAL); // Toca el vaixell de (0,2)
    test_result("es_posicio_valida() - sobre altre vaixell", 0, valid);
    
    // TEST 7: col·locar_vaixell - Horitzontal
    inicialitzar_tauler(tauler);
    col·locar_vaixell(tauler, 5, 3, 4, HORITZONTAL);
    int vaixell_h_ok = (tauler[5][3] == VAIXELL && tauler[5][4] == VAIXELL && 
                        tauler[5][5] == VAIXELL && tauler[5][6] == VAIXELL);
    test_result("col·locar_vaixell() - horitzontal (5,3, mida 4)", 1, vaixell_h_ok);
    
    // TEST 8: col·locar_vaixell - Vertical
    inicialitzar_tauler(tauler);
    col·locar_vaixell(tauler, 2, 7, 3, VERTICAL);
    int vaixell_v_ok = (tauler[2][7] == VAIXELL && tauler[3][7] == VAIXELL && 
                        tauler[4][7] == VAIXELL);
    test_result("col·locar_vaixell() - vertical (2,7, mida 3)", 1, vaixell_v_ok);
    
    // TEST 9: omplir_aigua_voltant - Horitzontal
    inicialitzar_tauler(tauler);
    col·locar_vaixell(tauler, 5, 5, 2, HORITZONTAL); // Vaixell a (5,5) i (5,6)
    omplir_aigua_voltant(tauler, 5, 5, 2, HORITZONTAL);
    int aigua_ok = (tauler[4][4] == AIGUA_TOCADA && // Dalt-esquerra
                    tauler[4][5] == AIGUA_TOCADA && // Dalt
                    tauler[4][6] == AIGUA_TOCADA && // Dalt-dreta
                    tauler[6][4] == AIGUA_TOCADA);  // Baix-esquerra
    test_result("omplir_aigua_voltant() - horitzontal", 1, aigua_ok);
    
    // TEST 10: generar_flota
    inicialitzar_tauler(tauler);
    generar_flota(tauler, 1);
    int num_vaixells = 0;
    for (i = 0; i < MIDA; i++) {
        for (j = 0; j < MIDA; j++) {
            if (tauler[i][j] == VAIXELL) {
                num_vaixells++;
            }
        }
    }
    // Flota 1: 1*5 + 1*4 + 2*3 + 2*2 + 3*1 = 5+4+6+4+3 = 22 caselles
    test_result("generar_flota(1) - genera 22 caselles de vaixells", 22, num_vaixells);
    
    printf("\n--- Tauler generat (visual) ---\n");
    mostrar_tauler(tauler, 1);
}

// ============================================
// TESTS DE JOC.C
// ============================================

void test_joc() {
    test_header("MÒDUL JOC");
    
    int tauler[MIDA][MIDA];
    int tauler_jugador[MIDA][MIDA];
    int fila, col;
    
    // TEST 1: processar_coordenades - Entrada vàlida "A1"
    int valid = processar_coordenades("A1", &fila, &col);
    int coord_ok = (valid == 1 && fila == 0 && col == 0);
    test_result("processar_coordenades('A1') → (0,0)", 1, coord_ok);
    
    // TEST 2: processar_coordenades - Entrada vàlida "J10"
    valid = processar_coordenades("J10", &fila, &col);
    coord_ok = (valid == 1 && fila == 9 && col == 9);
    test_result("processar_coordenades('J10') → (9,9)", 1, coord_ok);
    
    // TEST 3: processar_coordenades - Minúscules "e5"
    valid = processar_coordenades("e5", &fila, &col);
    coord_ok = (valid == 1 && fila == 4 && col == 4);
    test_result("processar_coordenades('e5') → (4,4)", 1, coord_ok);
    
    // TEST 4: processar_coordenades - Entrada invàlida "K5"
    valid = processar_coordenades("K5", &fila, &col);
    test_result("processar_coordenades('K5') → invàlid", 0, valid);
    
    // TEST 5: processar_coordenades - Entrada invàlida "A11"
    valid = processar_coordenades("A11", &fila, &col);
    test_result("processar_coordenades('A11') → invàlid", 0, valid);
    
    // TEST 6: processar_coordenades - Entrada invàlida "AA"
    valid = processar_coordenades("AA", &fila, &col);
    test_result("processar_coordenades('AA') → invàlid", 0, valid);
    
    // TEST 7: processar_tir - Aigua
    inicialitzar_tauler(tauler);
    inicialitzar_tauler(tauler_jugador);
    int resultat = processar_tir(tauler, tauler_jugador, 0, 0);
    test_result("processar_tir() - aigua", RESULTAT_AIGUA, resultat);
    
    // TEST 8: processar_tir - Tocat
    inicialitzar_tauler(tauler);
    inicialitzar_tauler(tauler_jugador);
    col·locar_vaixell(tauler, 5, 5, 3, HORITZONTAL);
    resultat = processar_tir(tauler, tauler_jugador, 5, 5);
    test_result("processar_tir() - tocat", RESULTAT_TOCAT, resultat);
    
    // TEST 9: processar_tir - Enfonsat (submari mida 1)
    inicialitzar_tauler(tauler);
    inicialitzar_tauler(tauler_jugador);
    col·locar_vaixell(tauler, 3, 3, 1, HORITZONTAL);
    resultat = processar_tir(tauler, tauler_jugador, 3, 3);
    test_result("processar_tir() - enfonsat (submari)", RESULTAT_ENFONSAT, resultat);
    
    // TEST 10: processar_tir - Ja disparat
    inicialitzar_tauler(tauler);
    inicialitzar_tauler(tauler_jugador);
    processar_tir(tauler, tauler_jugador, 2, 2); // Primer tir
    resultat = processar_tir(tauler, tauler_jugador, 2, 2); // Segon tir a la mateixa casella
    test_result("processar_tir() - ja disparat", RESULTAT_INVALID, resultat);
    
    // TEST 11: comprovar_enfonsat - Vaixell no enfonsat
    inicialitzar_tauler(tauler);
    inicialitzar_tauler(tauler_jugador);
    col·locar_vaixell(tauler, 0, 0, 3, HORITZONTAL);
    tauler_jugador[0][0] = VAIXELL; // Només 1 de 3 tocat
    int enfonsat = comprovar_enfonsat(tauler, tauler_jugador, 0, 0);
    test_result("comprovar_enfonsat() - no enfonsat (1/3)", 0, enfonsat);
    
    // TEST 12: comprovar_enfonsat - Vaixell enfonsat
    tauler_jugador[0][1] = VAIXELL;
    tauler_jugador[0][2] = VAIXELL;
    enfonsat = comprovar_enfonsat(tauler, tauler_jugador, 0, 0);
    test_result("comprovar_enfonsat() - enfonsat (3/3)", 1, enfonsat);
    
    // TEST 13: comprovar_victoria - No victòria
    inicialitzar_tauler(tauler);
    inicialitzar_tauler(tauler_jugador);
    col·locar_vaixell(tauler, 0, 0, 2, HORITZONTAL);
    tauler_jugador[0][0] = VAIXELL; // Només 1 tocat
    int victoria = comprovar_victoria(tauler, tauler_jugador);
    test_result("comprovar_victoria() - no victòria", 0, victoria);
    
    // TEST 14: comprovar_victoria - Victòria
    tauler_jugador[0][1] = VAIXELL; // Tots tocats
    victoria = comprovar_victoria(tauler, tauler_jugador);
    test_result("comprovar_victoria() - victòria", 1, victoria);
}

// ============================================
// MAIN DEL TEST
// ============================================

int main() {
    printf("\n");
    printf("╔════════════════════════════════════════╗\n");
    printf("║  TESTS BATALLA NAVAL - SUITE COMPLET  ║\n");
    printf("╔════════════════════════════════════════╗\n");
    
    // Executar tots els tests
    test_tauler();
    test_vaixells();
    test_joc();
    
    // Resum final
    printf("\n%s========================================%s\n", COLOR_BLUE, COLOR_RESET);
    printf("%s  RESUM FINAL%s\n", COLOR_BLUE, COLOR_RESET);
    printf("%s========================================%s\n", COLOR_BLUE, COLOR_RESET);
    printf("%s✓ Tests passats:%s %d\n", COLOR_GREEN, COLOR_RESET, tests_passed);
    printf("%s✗ Tests fallats:%s %d\n", COLOR_RED, COLOR_RESET, tests_failed);
    printf("%sTotal:%s %d tests\n", COLOR_YELLOW, COLOR_RESET, tests_passed + tests_failed);
    
    if (tests_failed == 0) {
        printf("\n%s🎉 TOTS ELS TESTS HAN PASSAT! 🎉%s\n\n", COLOR_GREEN, COLOR_RESET);
        return 0;
    } else {
        printf("\n%s⚠️  HI HA TESTS FALLATS ⚠️%s\n\n", COLOR_RED, COLOR_RESET);
        return 1;
    }
}