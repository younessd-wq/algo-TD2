/*
 * TD3 - Listes chaînées, Piles et Files
 * Filières : IDRS - Semestre 2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* =============================================
 *  DÉFINITION DES STRUCTURES
 * ============================================= */

/* --- Liste chaînée --- */
struct Element {
    int val;
    struct Element *suivant;
};
typedef struct Element LISTE;

/* --- Pile --- */
typedef struct stack {
    int data;
    struct stack *next;
} STACK;

/* --- File --- */
struct queue_node {
    struct queue_node *next;
    char data;
};
struct queue {
    struct queue_node *first;
    struct queue_node *last;
};

/* =============================================
 *  EXERCICE 1 : Création d'une liste
 *  Complexité : O(1) par insertion
 * ============================================= */

int InsererElementEnTete(LISTE **L, int valeur) {
    LISTE *element = (LISTE *)malloc(sizeof(LISTE));
    if (!element) { printf("Probleme d'allocation memoire\n"); return 0; }
    element->val     = valeur;
    element->suivant = *L;
    *L = element;
    return 1;
}

int InsererElementEnFin(LISTE **L, int valeur) {
    LISTE *element = (LISTE *)malloc(sizeof(LISTE));
    if (!element) { printf("Probleme d'allocation memoire\n"); return 0; }
    element->val     = valeur;
    element->suivant = NULL;
    if (*L == NULL) { *L = element; return 1; }
    LISTE *ptr = *L;
    while (ptr->suivant) ptr = ptr->suivant;
    ptr->suivant = element;
    return 1;
}

void AfficheListe(LISTE *L) {
    printf("[ ");
    while (L) { printf("%d ", L->val); L = L->suivant; }
    printf("]\n");
}

/* =============================================
 *  EXERCICE 2 : Recherche d'une valeur
 *  Complexité : O(n)
 * ============================================= */

int RechercherValeur(LISTE *L, int valeur) {
    while (L) {
        if (L->val == valeur) return 1;
        L = L->suivant;
    }
    return 0;
}

/* =============================================
 *  EXERCICE 3 : Suppression du minimum
 *  Complexité : O(n)
 * ============================================= */

int SuppressionValeurMin(LISTE **L) {
    LISTE *ptr = *L, *pMin = NULL;
    int minim;

    if (!ptr) return 0;
    if (!ptr->suivant) { *L = NULL; free(ptr); return 1; }

    minim = ptr->val;
    pMin  = NULL;
    while (ptr->suivant) {
        if (minim > ptr->suivant->val) {
            minim = ptr->suivant->val;
            pMin  = ptr;
        }
        ptr = ptr->suivant;
    }
    if (!pMin) {            /* le min est en tête */
        ptr  = *L;
        *L   = (*L)->suivant;
        free(ptr);
    } else {
        ptr              = pMin->suivant;
        pMin->suivant    = pMin->suivant->suivant;
        free(ptr);
    }
    return 1;
}

/* =============================================
 *  EXERCICE 4 : Fusion de deux listes
 *  Complexité : O(min(m,n))
 * ============================================= */

LISTE *FusionDe2Listes(LISTE *L1, LISTE *L2) {
    LISTE *res = NULL;
    LISTE *ptr1 = L1, *ptr2 = L2;
    if (!L1) return L2;
    if (!L2) return L1;

    while (ptr1 && ptr2) {
        InsererElementEnFin(&res, ptr1->val);
        InsererElementEnFin(&res, ptr2->val);
        ptr1 = ptr1->suivant;
        ptr2 = ptr2->suivant;
    }
    while (ptr1) { InsererElementEnFin(&res, ptr1->val); ptr1 = ptr1->suivant; }
    while (ptr2) { InsererElementEnFin(&res, ptr2->val); ptr2 = ptr2->suivant; }
    return res;
}

/* =============================================
 *  EXERCICE 5 : Destruction d'une liste
 * ============================================= */

void DestructionListe(LISTE **L) {
    LISTE *ptr;
    while (*L) {
        ptr  = *L;
        *L   = (*L)->suivant;
        free(ptr);
    }
}

/* =============================================
 *  EXERCICE 6 : Piles — push / pop / PairImpair
 * ============================================= */

void push(STACK **head, int value) {
    STACK *node = (STACK *)malloc(sizeof(STACK));
    if (!node) { fputs("Erreur: pas de memoire\n", stderr); abort(); }
    node->data = value;
    node->next = (*head == NULL) ? NULL : *head;
    *head      = node;
}

int pop(STACK **head) {
    if (!*head) { fputs("Erreur: pile vide\n", stderr); abort(); }
    STACK *top = *head;
    int value  = top->data;
    *head      = top->next;
    free(top);
    return value;
}

void AffichePile(STACK *P) {
    printf("[ ");
    while (P) { printf("%d ", P->data); P = P->next; }
    printf("]\n");
}

/* Séparer pairs (sous) et impairs (dessus) dans P2 */
STACK *PairImpair(STACK *P1) {
    STACK *P2 = NULL, *P3 = NULL;
    while (P1) {
        int val = pop(&P1);
        if (val % 2 == 0) push(&P2, val);
        else               push(&P3, val);
    }
    /* Mettre les impairs au-dessus des pairs */
    while (P3) push(&P2, pop(&P3));
    return P2;
}

/* =============================================
 *  EXERCICE 7 : Files — Palindrome
 * ============================================= */

/* Pile de caractères */
typedef struct cstack { char data; struct cstack *next; } CSTACK;

void cpush(CSTACK **head, char value) {
    CSTACK *node = (CSTACK *)malloc(sizeof(CSTACK));
    if (!node) abort();
    node->data = value;
    node->next = (*head) ? *head : NULL;
    *head = node;
}

char cpop(CSTACK **head) {
    if (!*head) abort();
    CSTACK *top = *head;
    char v = top->data;
    *head = top->next;
    free(top);
    return v;
}

int enqueue(struct queue *q, char value) {
    struct queue_node *node = (struct queue_node *)malloc(sizeof(struct queue_node));
    if (!node) return 1;
    node->data = value;
    node->next = NULL;
    if (!q->first) q->first = q->last = node;
    else { q->last->next = node; q->last = node; }
    return 0;
}

int dequeue(struct queue *q, char *value) {
    if (!q->first) { *value = 0; return 1; }
    *value = q->first->data;
    struct queue_node *tmp = q->first;
    if (q->first == q->last) q->first = q->last = NULL;
    else q->first = q->first->next;
    free(tmp);
    return 0;
}

struct queue *EcrireMessage(const char *chaine) {
    struct queue *q = (struct queue *)malloc(sizeof(struct queue));
    if (!q) { printf("Prob allocation"); exit(0); }
    q->first = q->last = NULL;
    for (int i = 0; i < (int)strlen(chaine); i++)
        enqueue(q, chaine[i]);
    return q;
}

int EstPalindrome(const char *chaine) {
    int len = strlen(chaine);
    int t1  = len % 2;
    int t2  = len / 2;
    char val, c1, c2;
    CSTACK *p = NULL;
    struct queue *Q = EcrireMessage(chaine);

    for (int i = 0; i < t2; i++) { dequeue(Q, &val); cpush(&p, val); }
    if (t1 != 0) dequeue(Q, &val);   /* ignorer le caractère central */
    for (int i = 0; i < t2; i++) {
        dequeue(Q, &c1);
        c2 = cpop(&p);
        if (c1 != c2) return 0;
    }
    return 1;
}

/* =============================================
 *  PROGRAMME PRINCIPAL
 * ============================================= */

int main() {
    srand(time(NULL));

    printf("========== EX1 : Création d'une liste de 10 entiers ==========\n");
    LISTE *L = NULL;
    for (int i = 0; i < 10; i++)
        InsererElementEnTete(&L, rand() % 100);
    AfficheListe(L);

    printf("\n========== EX2 : Recherche ==========\n");
    int val = L->val;   /* on cherche la tête (existe forcément) */
    printf("Recherche de %d : %s\n", val, RechercherValeur(L, val) ? "trouvé" : "non trouvé");
    printf("Recherche de 999 : %s\n", RechercherValeur(L, 999) ? "trouvé" : "non trouvé");

    printf("\n========== EX3 : Suppression du minimum ==========\n");
    printf("Avant : "); AfficheListe(L);
    SuppressionValeurMin(&L);
    printf("Après : "); AfficheListe(L);

    printf("\n========== EX4 : Fusion de deux listes ==========\n");
    LISTE *A = NULL, *B = NULL;
    for (int i = 1; i <= 4; i++) InsererElementEnFin(&A, i * 10);
    for (int i = 1; i <= 3; i++) InsererElementEnFin(&B, i * 5);
    printf("A : "); AfficheListe(A);
    printf("B : "); AfficheListe(B);
    LISTE *C = FusionDe2Listes(A, B);
    printf("C : "); AfficheListe(C);

    printf("\n========== EX5 : Destruction ==========\n");
    DestructionListe(&C);
    printf("C après destruction : "); AfficheListe(C);

    printf("\n========== EX6 : Piles - PairImpair ==========\n");
    STACK *P1 = NULL, *P2 = NULL;
    for (int i = 1; i <= 9; i++) push(&P1, i);
    printf("P1 : "); AffichePile(P1);
    P2 = PairImpair(P1);
    printf("P2 (pairs en bas, impairs en haut) : "); AffichePile(P2);

    printf("\n========== EX7 : Palindrome ==========\n");
    const char *mots[] = {"radar", "bonjour", "kayak", "niveau", "hello"};
    for (int i = 0; i < 5; i++)
        printf("\"%s\" -> %s\n", mots[i], EstPalindrome(mots[i]) ? "PALINDROME" : "non palindrome");

    return 0;
}
