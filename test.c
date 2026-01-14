#include <stdio.h>
#include <string.h>
#include "tauler.h"
#include "vaixells.h"
#include "joc.h"

int tests_passed = 0;
int tests_failed = 0;

void test_result(char *nom_test, int resultat_esperat, int resultat_obtingut) {
    if (resultat_esperat == resultat_obtingut) {
        printf("PASS: %s\n", nom_test);
        tests_passed++;
    } else {
        printf("FAIL: %s (esperat: %d, obtingut: %d)\n", nom_test, resultat_esperat, resultat_obtingut);
        tests_failed++;
    }
}

void test_header(char *nom_modul) {
    printf("\n========================================\n");
    printf("  TEST: %s\n", nom_modul);
    printf("========================================\n");
}

// TESTS DE TAULER.C
void test_tauler() {
    test_header("MODUL TAULER");
    
    int tauler[MIDA][MIDA];
    int tauler2[MIDA][MIDA];
    int i, j;
    
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
    
    tauler[0][0] = VAIXELL;
    tauler[5][5] = AIGUA_TOCADA;
    copiar_tauler(tauler, tauler2);
    int copia_correcta = (tauler2[0][0] == VAIXELL && tauler2[5][5] == AIGUA_TOCADA);
    test_result("copiar_tauler() copia correctament", 1, copia_correcta);
    
    printf("\n--- Test visual de mostrar_tauler ---\n");
    inicialitzar_tauler(tauler);
    tauler[0][0] = VAIXELL;
    tauler[1][1] = AIGUA_TOCADA;
    mostrar_tauler(tauler, 1);
    printf("--- Fi del test visual ---\n\n");
}

// TESTS DE VAIXELLS.C
void test_vaixells() {
    test_header("MODUL VAIXELLS");
    
    int tauler[MIDA][MIDA];
    Flota flota;
    int i, j;
    
    obtenir_configuracio_flota(1, &flota);
    int flota1_ok = (flota.portaavions == 1 && flota.cuirassats == 1 && 
                     flota.destructors == 2 && flota.fragates == 2 && flota.submarins == 3);
    test_result("obtenir_configuracio_flota(1)", 1, flota1_ok);
    
    obtenir_configuracio_flota(2, &flota);
    int flota2_ok = (flota.portaavions == 0 && flota.cuirassats == 1 && 
                     flota.destructors == 2 && flota.fragates == 3 && flota.submarins == 4);
    test_result("obtenir_configuracio_flota(2)", 1, flota2_ok);
    
    obtenir_configuracio_flota(3, &flota);
    int flota3_ok = (flota.portaavions == 0 && flota.cuirassats == 0 && 
                     flota.destructors == 2 && flota.fragates == 3 && flota.submarins == 4);
    test_result("obtenir_configuracio_flota(3)", 1, flota3_ok);
    
    inicialitzar_tauler(tauler);
    int valid = es_posicio_valida(tauler, 0, 0, 3, HORITZONTAL);
    test_result("es_posicio_valida() - posicio valida", 1, valid);
    
    valid = es_posicio_valida(tauler, 0, 8, 3, HORITZONTAL);
    test_result("es_posicio_valida() - fora de limits", 0, valid);
    
    col_locar_vaixell(tauler, 0, 0, 3, HORITZONTAL);
    valid = es_posicio_valida(tauler, 0, 2, 2, VERTICAL);
    test_result("es_posicio_valida() - sobre altre vaixell", 0, valid);
    
    inicialitzar_tauler(tauler);
    col_locar_vaixell(tauler, 5, 3, 4, HORITZONTAL);
    int vaixell_h_ok = (tauler[5][3] == VAIXELL && tauler[5][4] == VAIXELL && 
                        tauler[5][5] == VAIXELL && tauler[5][6] == VAIXELL);
    test_result("col_locar_vaixell() - horitzontal", 1, vaixell_h_ok);
    
    inicialitzar_tauler(tauler);
    col_locar_vaixell(tauler, 2, 7, 3, VERTICAL);
    int vaixell_v_ok = (tauler[2][7] == VAIXELL && tauler[3][7] == VAIXELL && 
                        tauler[4][7] == VAIXELL);
    test_result("col_locar_vaixell() - vertical", 1, vaixell_v_ok);
    
    inicialitzar_tauler(tauler);
    col_locar_vaixell(tauler, 5, 5, 2, HORITZONTAL);
    omplir_aigua_voltant(tauler, 5, 5, 2, HORITZONTAL);
    int aigua_ok = (tauler[4][4] == AIGUA_TOCADA && tauler[4][5] == AIGUA_TOCADA && 
                    tauler[4][6] == AIGUA_TOCADA && tauler[6][4] == AIGUA_TOCADA);
    test_result("omplir_aigua_voltant()", 1, aigua_ok);
    
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
    test_result("generar_flota(1) - 22 caselles de vaixells", 22, num_vaixells);
    
    printf("\n--- Tauler generat ---\n");
    mostrar_tauler(tauler, 1);
}

// TESTS DE JOC.C
void test_joc() {
    test_header("MODUL JOC");
    
    int tauler[MIDA][MIDA];
    int tauler_jugador[MIDA][MIDA];
    int fila, col;
    
    int valid = processar_coordenades("A1", &fila, &col);
    int coord_ok = (valid == 1 && fila == 0 && col == 0);
    test_result("processar_coordenades('A1')", 1, coord_ok);
    
    valid = processar_coordenades("J10", &fila, &col);
    coord_ok = (valid == 1 && fila == 9 && col == 9);
    test_result("processar_coordenades('J10')", 1, coord_ok);
    
    valid = processar_coordenades("e5", &fila, &col);
    coord_ok = (valid == 1 && fila == 4 && col == 4);
    test_result("processar_coordenades('e5')", 1, coord_ok);
    
    valid = processar_coordenades("K5", &fila, &col);
    test_result("processar_coordenades('K5') - invalid", 0, valid);
    
    valid = processar_coordenades("A11", &fila, &col);
    test_result("processar_coordenades('A11') - invalid", 0, valid);
    
    valid = processar_coordenades("AA", &fila, &col);
    test_result("processar_coordenades('AA') - invalid", 0, valid);
    
    inicialitzar_tauler(tauler);
    inicialitzar_tauler(tauler_jugador);
    int resultat = processar_tir(tauler, tauler_jugador, 0, 0);
    test_result("processar_tir() - aigua", RESULTAT_AIGUA, resultat);
    
    inicialitzar_tauler(tauler);
    inicialitzar_tauler(tauler_jugador);
    col_locar_vaixell(tauler, 5, 5, 3, HORITZONTAL);
    resultat = processar_tir(tauler, tauler_jugador, 5, 5);
    test_result("processar_tir() - tocat", RESULTAT_TOCAT, resultat);
    
    inicialitzar_tauler(tauler);
    inicialitzar_tauler(tauler_jugador);
    col_locar_vaixell(tauler, 3, 3, 1, HORITZONTAL);
    resultat = processar_tir(tauler, tauler_jugador, 3, 3);
    test_result("processar_tir() - enfonsat", RESULTAT_ENFONSAT, resultat);
    
    inicialitzar_tauler(tauler);
    inicialitzar_tauler(tauler_jugador);
    processar_tir(tauler, tauler_jugador, 2, 2);
    resultat = processar_tir(tauler, tauler_jugador, 2, 2);
    test_result("processar_tir() - ja disparat", RESULTAT_INVALID, resultat);
    
    inicialitzar_tauler(tauler);
    inicialitzar_tauler(tauler_jugador);
    col_locar_vaixell(tauler, 0, 0, 3, HORITZONTAL);
    tauler_jugador[0][0] = VAIXELL;
    int enfonsat = comprovar_enfonsat(tauler, tauler_jugador, 0, 0);
    test_result("comprovar_enfonsat() - no enfonsat", 0, enfonsat);
    
    tauler_jugador[0][1] = VAIXELL;
    tauler_jugador[0][2] = VAIXELL;
    enfonsat = comprovar_enfonsat(tauler, tauler_jugador, 0, 0);
    test_result("comprovar_enfonsat() - enfonsat", 1, enfonsat);
    
    inicialitzar_tauler(tauler);
    inicialitzar_tauler(tauler_jugador);
    col_locar_vaixell(tauler, 0, 0, 2, HORITZONTAL);
    tauler_jugador[0][0] = VAIXELL;
    int victoria = comprovar_victoria(tauler, tauler_jugador);
    test_result("comprovar_victoria() - no victoria", 0, victoria);
    
    tauler_jugador[0][1] = VAIXELL;
    victoria = comprovar_victoria(tauler, tauler_jugador);
    test_result("comprovar_victoria() - victoria", 1, victoria);
}

int main() {
    printf("\n========================================\n");
    printf("  TESTS BATALLA NAVAL\n");
    printf("========================================\n");
    
    test_tauler();
    test_vaixells();
    test_joc();
    
    printf("\n========================================\n");
    printf("  RESUM FINAL\n");
    printf("========================================\n");
    printf("Tests passats: %d\n", tests_passed);
    printf("Tests fallats: %d\n", tests_failed);
    printf("Total: %d tests\n", tests_passed + tests_failed);
    
    if (tests_failed == 0) {
        printf("\nTOTS ELS TESTS HAN PASSAT!\n\n");
        return 0;
    } else {
        printf("\nHI HA TESTS FALLATS\n\n");
        return 1;
    }
}