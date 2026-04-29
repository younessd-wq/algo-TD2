/*
 * TD2 - Complexité et Récursivité
 * Filières : IDRS - Semestre 2
 */

#include <stdio.h>
#include <stdlib.h>

#define N 10

/* =============================================
 *  EXERCICE 1 : Indice du premier minimum
 * =============================================
 *  Complexité : O(n)
 */
int indiceMin(int tab[], int n) {
    int i, index = 0;
    for (i = 1; i < n; i++)
        if (tab[i] < tab[index])
            index = i;
    return index;
}

/* =============================================
 *  EXERCICE 2 : MiniMax d'une matrice
 * =============================================
 *  Complexité : O(n*m)
 */
int MiniMax(int tab[][N], int n, int m) {
    int i, j, max, minimax = 0;
    for (i = 0; i < n; i++) {
        max = tab[i][0];
        for (j = 1; j < m; j++)
            if (tab[i][j] > max)
                max = tab[i][j];
        if (i == 0)
            minimax = max;
        else if (minimax > max)
            minimax = max;
    }
    return minimax;
}

/* =============================================
 *  EXERCICE 3 : Puissance et Somme récursives
 * =============================================
 *  puissance simple  : O(n)
 *  expRapide         : O(log n)
 *  somme             : O(n²)
 */

/* Puissance simple récursive */
int puissance(int a, int i) {
    if (i == 0) return 1;
    return a * puissance(a, i - 1);
}

/* Exponentiation rapide : O(log n) */
int expRapide(int a, int i) {
    if (i == 0) return 1;
    if (i % 2 == 0) {
        int half = expRapide(a, i / 2);
        return half * half;
    }
    return a * expRapide(a, i - 1);
}

/* Somme : a^0 + a^1 + ... + a^n  — O(n²) */
int somme(int a, int n) {
    if (n == 0) return 1;
    return puissance(a, n) + somme(a, n - 1);
}

/* =============================================
 *  EXERCICE 4 : rec1 et rec2
 * =============================================
 *  rec1 : calcule 2^n, complexité O(n)
 *  rec2 : calcule 2^n, complexité O(2^n)
 */

int rec1(int n) {
    if (n == 0) return 1;
    return 2 * rec1(n - 1);
}

int rec2(int n) {
    if (n == 0) return 1;
    return rec2(n - 1) + rec2(n - 1);
}

/* =============================================
 *  PROGRAMME PRINCIPAL
 * ============================================= */

int main() {
    printf("========== EXERCICE 1 : Indice du minimum ==========\n");
    int tab[] = {5, 2, 4, 2, 1, 7, 9, 4, 1, 1};
    int n = 10;
    printf("Tableau : ");
    for (int i = 0; i < n; i++) printf("%d ", tab[i]);
    printf("\nIndice du premier minimum : %d\n\n", indiceMin(tab, n));

    printf("========== EXERCICE 2 : MiniMax ==========\n");
    int mat[3][N];
    /* Initialisation manuelle d'une matrice 3x3 */
    int vals[3][3] = {{2, 3, 4}, {5, 1, 7}, {8, 9, 10}};
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            mat[i][j] = vals[i][j];
    printf("MiniMax de la matrice = %d\n\n", MiniMax(mat, 3, 3));

    printf("========== EXERCICE 3 : Puissance ==========\n");
    printf("puissance(2, 8)  = %d\n", puissance(2, 8));
    printf("expRapide(2, 8)  = %d\n", expRapide(2, 8));
    printf("somme(2, 4)      = %d  (attendu: 1+2+4+8+16=31)\n\n", somme(2, 4));

    printf("========== EXERCICE 4 : rec1 vs rec2 ==========\n");
    for (int i = 0; i <= 5; i++)
        printf("rec1(%d)=%d  rec2(%d)=%d\n", i, rec1(i), i, rec2(i));

    return 0;
}
