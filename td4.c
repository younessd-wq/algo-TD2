/*
 * TD4 - Arbres Binaires de Recherche (ABR)
 * Filières : IDRS - Semestre 2
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* =============================================
 *  STRUCTURES
 * ============================================= */

typedef int element_type;

typedef struct tree_node *tree_ptr;
struct tree_node {
    element_type element;
    tree_ptr left;
    tree_ptr right;
};
typedef tree_ptr SEARCH_TREE;

/* Liste pour TD4 */
struct Element { int val; struct Element *suivant; };
typedef struct Element LISTE;

/* =============================================
 *  UTILITAIRES LISTE
 * ============================================= */

int InsererElementEnFin(LISTE **L, int valeur) {
    LISTE *e = (LISTE *)malloc(sizeof(LISTE));
    if (!e) return 0;
    e->val = valeur; e->suivant = NULL;
    if (!*L) { *L = e; return 1; }
    LISTE *ptr = *L;
    while (ptr->suivant) ptr = ptr->suivant;
    ptr->suivant = e;
    return 1;
}

int InsererElementEnTete(LISTE **L, int valeur) {
    LISTE *e = (LISTE *)malloc(sizeof(LISTE));
    if (!e) return 0;
    e->val = valeur; e->suivant = *L; *L = e;
    return 1;
}

void AfficheListe(LISTE *L) {
    printf("[ ");
    while (L) { printf("%d ", L->val); L = L->suivant; }
    printf("]\n");
}

/* =============================================
 *  EXERCICE 1 : Fonctions de base ABR
 * ============================================= */

/* 1. Insertion — O(h), h = hauteur */
SEARCH_TREE insert(element_type x, SEARCH_TREE T) {
    if (T == NULL) {
        T = (SEARCH_TREE)malloc(sizeof(struct tree_node));
        if (!T) { printf("Memoire insuffisante!\n"); exit(0); }
        T->element = x;
        T->left = T->right = NULL;
    } else if (x <= T->element)
        T->left  = insert(x, T->left);
    else
        T->right = insert(x, T->right);
    return T;
}

/* 2. Recherche — O(h) */
tree_ptr RechercherElement(SEARCH_TREE A, element_type e) {
    if (!A) return NULL;
    if (e == A->element) return A;
    if (e > A->element)  return RechercherElement(A->right, e);
    return RechercherElement(A->left, e);
}

/* 3. Nombre d'occurrences — O(n) */
void NombreOccurences(SEARCH_TREE A, element_type e, int *nombre) {
    if (A) {
        NombreOccurences(A->left, e, nombre);
        if (A->element == e) (*nombre)++;
        NombreOccurences(A->right, e, nombre);
    }
}

/* 4. Parcours infixé — O(n) */
void ParcoursInfixe(SEARCH_TREE A) {
    if (A) {
        ParcoursInfixe(A->left);
        printf("%d ", A->element);
        ParcoursInfixe(A->right);
    }
}

/* Parcours préfixé (bonus) */
void ParcoursPrefixe(SEARCH_TREE A) {
    if (A) {
        printf("%d ", A->element);
        ParcoursPrefixe(A->left);
        ParcoursPrefixe(A->right);
    }
}

/* 5. Construire une liste triée depuis un ABR — O(n) */
void ConstListeTriee(SEARCH_TREE A, LISTE **L) {
    if (A) {
        ConstListeTriee(A->left, L);
        InsererElementEnFin(L, A->element);
        ConstListeTriee(A->right, L);
    }
}

/* 6. Construire un ABR depuis une liste — O(n*h) */
SEARCH_TREE ArbreAPartirDeListe(LISTE *L) {
    SEARCH_TREE A = NULL;
    while (L) {
        A = insert(L->val, A);
        L = L->suivant;
    }
    return A;
}

/* 7. Trier une liste via ABR — O(n log n) en moyenne */
LISTE *TrierListe(LISTE *L) {
    SEARCH_TREE A = ArbreAPartirDeListe(L);
    LISTE *triee = NULL;
    ConstListeTriee(A, &triee);
    return triee;
}

/* =============================================
 *  EXERCICE 2 : Vérifier si un arbre est ABR
 *  Complexité : O(n)
 * ============================================= */

int EstCeQueABR(SEARCH_TREE A) {
    if (!A) return 0;
    if (!A->left && !A->right) return 1;
    LISTE *L = NULL;
    ConstListeTriee(A, &L);
    while (L && L->suivant) {
        if (L->val > L->suivant->val) return 0;
        L = L->suivant;
    }
    return 1;
}

/* =============================================
 *  EXERCICE 3 : Plus petit élément
 *  Complexité : O(h)
 * ============================================= */

element_type LePlusPetit(SEARCH_TREE A) {
    while (A->left) A = A->left;
    return A->element;
}

/* =============================================
 *  PROGRAMME PRINCIPAL
 * ============================================= */

int main() {
    srand(time(NULL));

    printf("========== Création ABR avec 10 entiers aléatoires ==========\n");
    SEARCH_TREE A = NULL;
    for (int i = 0; i < 10; i++)
        A = insert(rand() % 20, A);

    printf("Parcours infixe  (trié) : "); ParcoursInfixe(A);  printf("\n");
    printf("Parcours préfixe        : "); ParcoursPrefixe(A); printf("\n");

    printf("\n========== Recherche dans l'ABR ==========\n");
    int n;
    printf("Entier a chercher (ex: 5) : ");
    /* En mode non-interactif, on prend 5 */
    n = 5;
    printf("%d\n", n);
    tree_ptr res = RechercherElement(A, n);
    if (res) {
        int nbre = 0;
        NombreOccurences(A, n, &nbre);
        printf("%d trouve dans l'arbre, occurrences : %d\n", n, nbre);
    } else
        printf("%d ne figure pas dans l'arbre\n", n);

    printf("\n========== Liste triée depuis ABR ==========\n");
    LISTE *LT = NULL;
    ConstListeTriee(A, &LT);
    printf("Liste triée : "); AfficheListe(LT);

    printf("\n========== Tri d'une liste non triée via ABR ==========\n");
    LISTE *L = NULL;
    for (int i = 0; i < 8; i++)
        InsererElementEnTete(&L, rand() % 30);
    printf("Avant tri : "); AfficheListe(L);
    L = TrierListe(L);
    printf("Après tri : "); AfficheListe(L);

    printf("\n========== EX2 : Est-ce un ABR ? ==========\n");
    printf("A est un ABR : %s\n", EstCeQueABR(A) ? "OUI" : "NON");

    /* Arbre non ABR (construit manuellement) */
    SEARCH_TREE B = (SEARCH_TREE)malloc(sizeof(struct tree_node));
    B->element = 5;
    B->left    = (SEARCH_TREE)malloc(sizeof(struct tree_node));
    B->right   = (SEARCH_TREE)malloc(sizeof(struct tree_node));
    B->left->element  = 10;  /* violation ABR */
    B->left->left = B->left->right = NULL;
    B->right->element = 3;   /* violation ABR */
    B->right->left = B->right->right = NULL;
    printf("B (non ABR) est un ABR : %s\n", EstCeQueABR(B) ? "OUI" : "NON");

    printf("\n========== EX3 : Plus petit élément ==========\n");
    printf("Minimum de A : %d\n", LePlusPetit(A));

    return 0;
}
