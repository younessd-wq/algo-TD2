/*
 * TD1 - Structures de données : Point et Heure
 * Filières : IDRS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define TMAX 20

/* =============================================
 *  EXERCICE 1 : Structure Point
 * ============================================= */

typedef struct {
    int abs;
    int ord;
} Point;

/* Saisir un point */
Point SaisirPoint() {
    Point p;
    printf("Donner les coordonnees du point (x y) : ");
    scanf("%d %d", &p.abs, &p.ord);
    return p;
}

/* Afficher un point au format (x,y) */
void AfficherPoint(Point p) {
    printf("(%d, %d)\n", p.abs, p.ord);
}

/* Distance par valeur */
float DistTransVal(Point p) {
    return sqrt((float)(p.abs * p.abs + p.ord * p.ord));
}

/* Distance par adresse */
float DistTransAdr(Point *p) {
    return sqrt((float)(p->abs * p->abs + p->ord * p->ord));
}

/* Tri par ordre croissant des distances (tri à bulles) */
void tritab(Point t[], int taille) {
    int i, j;
    Point aux;
    for (i = 0; i < taille - 1; i++)
        for (j = i + 1; j < taille; j++)
            if (DistTransVal(t[i]) > DistTransVal(t[j])) {
                aux  = t[i];
                t[i] = t[j];
                t[j] = aux;
            }
}

/* =============================================
 *  EXERCICE 2 : Structure Heure
 * ============================================= */

typedef struct {
    int hh;
    int mm;
    int ss;
} Heure;

/* Heure → secondes */
int HeureEnSecondes(Heure h) {
    return (h.hh * 3600 + h.mm * 60 + h.ss);
}

/* Secondes → Heure */
Heure SecondesEnHeure(int sec) {
    Heure h;
    h.hh = sec / 3600;
    sec  = sec % 3600;
    h.mm = sec / 60;
    sec  = sec % 60;
    h.ss = sec;
    return h;
}

/* Addition de deux heures */
Heure AddHeures(Heure h1, Heure h2) {
    return SecondesEnHeure(HeureEnSecondes(h1) + HeureEnSecondes(h2));
}

/* Différence entre deux heures */
Heure DiffHeures(Heure h1, Heure h2) {
    int diff = abs(HeureEnSecondes(h1) - HeureEnSecondes(h2));
    return SecondesEnHeure(diff);
}

void AfficherHeure(Heure h) {
    printf("%02d:%02d:%02d\n", h.hh, h.mm, h.ss);
}

/* =============================================
 *  PROGRAMME PRINCIPAL
 * ============================================= */

int main() {
    printf("========== EXERCICE 1 : Points ==========\n\n");

    /* Tableau statique */
    Point TStat[TMAX];
    int taille, i;

    printf("Donner la taille du tableau (<= %d) : ", TMAX);
    scanf("%d", &taille);
    if (taille > TMAX) taille = TMAX;

    /* Remplissage aléatoire */
    srand(time(NULL));
    for (i = 0; i < taille; i++) {
        TStat[i].abs = rand() % 100;
        TStat[i].ord = rand() % 100;
    }

    printf("\nPoints avant tri :\n");
    for (i = 0; i < taille; i++) AfficherPoint(TStat[i]);

    printf("\nDistances avant tri :\n");
    for (i = 0; i < taille; i++)
        printf("  dist[%d] = %.2f\n", i, DistTransVal(TStat[i]));

    tritab(TStat, taille);

    printf("\nPoints apres tri par distance croissante :\n");
    for (i = 0; i < taille; i++) {
        AfficherPoint(TStat[i]);
    }

    /* Tableau dynamique */
    printf("\n--- Tableau dynamique ---\n");
    Point *TDyn = (Point *)malloc(taille * sizeof(Point));
    if (!TDyn) { fprintf(stderr, "Erreur malloc\n"); return 1; }

    for (i = 0; i < taille; i++) {
        TDyn[i].abs = rand() % 100;
        TDyn[i].ord = rand() % 100;
    }
    printf("Points dynamiques :\n");
    for (i = 0; i < taille; i++) AfficherPoint(TDyn[i]);
    free(TDyn);

    printf("\n========== EXERCICE 2 : Heures ==========\n\n");

    Heure h1 = {1, 30, 45};
    Heure h2 = {0, 45, 30};

    printf("H1 = "); AfficherHeure(h1);
    printf("H2 = "); AfficherHeure(h2);

    printf("H1 en secondes : %d\n", HeureEnSecondes(h1));
    printf("3600 secondes  : "); AfficherHeure(SecondesEnHeure(3600));

    printf("H1 + H2 = "); AfficherHeure(AddHeures(h1, h2));
    printf("H1 - H2 = "); AfficherHeure(DiffHeures(h1, h2));

    return 0;
}
