# Compte Rendu — Complexité et Structures de Données Abstraites
**Filières : IDRS — Semestre 2**

---

## Table des matières
1. [Introduction](#introduction)
2. [Structure du projet](#structure-du-projet)
3. [TD1 — Structures](#td1--structures)
4. [TD2 — Complexité et Récursivité](#td2--complexité-et-récursivité)
5. [TD3 — Listes, Piles, Files](#td3--listes-piles-files)
6. [TD4 — Arbres Binaires de Recherche](#td4--arbres-binaires-de-recherche)
7. [Compilation et Exécution](#compilation-et-exécution)
8. [Résultats des tests](#résultats-des-tests)
9. [Tableau récapitulatif des complexités](#tableau-récapitulatif-des-complexités)

---

## Introduction

Ce projet regroupe l'implémentation complète en **langage C** des quatre séries de travaux dirigés (TD) portant sur les structures de données abstraites et la complexité algorithmique. Chaque TD a été implémenté dans un fichier source séparé, compilable indépendamment ou via le `Makefile` fourni.

---

## Structure du projet

```
projet_sda/
├── Makefile
├── README.md
├── TD1/
│   └── td1_structures.c       # Structures Point et Heure
├── TD2/
│   └── td2_complexite.c       # Complexité, récursivité
├── TD3/
│   └── td3_listes_piles_files.c  # Listes chaînées, piles, files
└── TD4/
    └── td4_abr.c              # Arbres binaires de recherche
```

---

## TD1 — Structures

**Fichier :** `TD1/td1_structures.c`

### Exercice 1 — Structure `Point`

La structure `Point` représente un point du plan avec deux coordonnées entières.

```c
typedef struct {
    int abs;
    int ord;
} Point;
```

**Fonctions implémentées :**

| Fonction | Description | Complexité |
|---|---|---|
| `SaisirPoint()` | Lecture clavier d'un point | O(1) |
| `AfficherPoint(p)` | Affichage au format `(x, y)` | O(1) |
| `DistTransVal(p)` | Distance à l'origine par valeur | O(1) |
| `DistTransAdr(p*)` | Distance à l'origine par adresse | O(1) |
| `tritab(t[], n)` | Tri par distances croissantes (tri par sélection) | O(n²) |

**Tableaux :** une version statique (`Point T[TMAX]`) et une version dynamique (`Point *T = malloc(...)`) sont toutes deux démontrées dans le `main`.

### Exercice 2 — Structure `Heure`

La structure `Heure` représente une heure au format `hh:mm:ss`.

```c
typedef struct { int hh; int mm; int ss; } Heure;
```

**Fonctions implémentées :**

| Fonction | Description |
|---|---|
| `HeureEnSecondes(h)` | Conversion Heure → entier (secondes) |
| `SecondesEnHeure(sec)` | Conversion entier → Heure |
| `AddHeures(h1, h2)` | Addition de deux heures |
| `DiffHeures(h1, h2)` | Différence (temps écoulé) entre deux heures |

**Exemple de sortie :**
```
H1 = 01:30:45
H2 = 00:45:30
H1 + H2 = 02:16:15
H1 - H2 = 00:45:15
```

---

## TD2 — Complexité et Récursivité

**Fichier :** `TD2/td2_complexite.c`

### Exercice 1 — Indice du premier minimum

Algorithme itératif qui parcourt le tableau une seule fois en maintenant l'indice du minimum courant.

- **Complexité :** T(n) = 4n − 2 → **O(n)**

```
Tableau : 5 2 4 2 1 7 9 4 1 1
Indice du premier minimum : 4  ✓
```

### Exercice 2 — MiniMax d'une matrice

Pour chaque ligne on cherche le maximum, puis on garde le minimum de ces maxima.

- **Complexité :** T(n, m) = 4·n·m + 3n − 2 → **O(n·m)**

### Exercice 3 — Puissance récursive et exponentiation rapide

| Méthode | Principe | Complexité |
|---|---|---|
| `puissance(a, n)` | `a^n = a * a^(n-1)` | **O(n)** |
| `expRapide(a, n)` | `a^n = (a^(n/2))²` si n pair | **O(log n)** |
| `somme(a, n)` | Somme de `a^0 + ... + a^n` | **O(n²)** |

L'exponentiation rapide divise le problème par 2 à chaque appel, d'où la complexité logarithmique.

### Exercice 4 — rec1 vs rec2

Les deux fonctions calculent **2ⁿ**, mais avec des complexités radicalement différentes :

| Fonction | Principe | Complexité |
|---|---|---|
| `rec1(n)` | `2 * rec1(n-1)` — un seul appel récursif | **O(n)** |
| `rec2(n)` | `rec2(n-1) + rec2(n-1)` — deux appels récursifs | **O(2ⁿ)** |

`rec2` est exponentiellement plus lente car elle recalcule deux fois le même sous-problème. C'est le cas typique où la mémoïsation ou la formulation itérative s'impose.

---

## TD3 — Listes, Piles, Files

**Fichier :** `TD3/td3_listes_piles_files.c`

### Structure de base : liste chaînée simple

```c
struct Element {
    int val;
    struct Element *suivant;
};
typedef struct Element LISTE;
```

### Exercice 1 — Création de liste

Insertion en tête en O(1) : on alloue un nœud et on fait pointer son `suivant` vers l'ancienne tête.

- **Complexité :** O(1) par insertion, O(n) pour créer une liste de n éléments.

### Exercice 2 — Recherche de valeur

Parcours séquentiel jusqu'à trouver la valeur ou atteindre la fin.

- **Complexité :** O(n) dans le pire cas.

### Exercice 3 — Suppression du minimum

Algorithme en deux passes : trouver le minimum et son prédécesseur, puis le supprimer.

- **Complexité :** O(n)

### Exercice 4 — Fusion de deux listes

Entrelacement des deux listes élément par élément, puis ajout du reste de la plus longue.

```
A : [ 10 20 30 40 ]
B : [ 5  10 15 ]
C : [ 10 5 20 10 30 15 40 ]
```

- **Complexité :** O(min(m, n)) pour l'entrelacement + O(|m−n|) pour le reste.

### Exercice 5 — Destruction de liste

Libération de chaque nœud en parcourant la liste, puis mise de `*L` à NULL.

### Exercice 6 — Piles et PairImpair

**Structures :** pile implémentée comme une liste chaînée (LIFO).

**`push`** : insertion en tête — O(1)  
**`pop`** : suppression en tête — O(1)

**`PairImpair(P1)`** : dépile P1, envoie les pairs dans P2 et les impairs dans P3 temporaire, puis empile P3 dans P2.

```
P1 : [ 9 8 7 6 5 4 3 2 1 ]
P2 : [ 9 7 5 3 1 2 4 6 8 ]  ← impairs au-dessus, pairs en dessous
```

### Exercice 7 — Files et Palindrome

**Algorithme `EstPalindrome` :**
1. Enfiler tous les caractères dans une file.
2. Défiler la première moitié et l'empiler dans une pile.
3. Ignorer le caractère central si longueur impaire.
4. Comparer chaque caractère défilé avec le sommet de la pile.

```
"radar"   → PALINDROME   ✓
"kayak"   → PALINDROME   ✓
"bonjour" → non palindrome ✓
```

---

## TD4 — Arbres Binaires de Recherche

**Fichier :** `TD4/td4_abr.c`

### Structure

```c
typedef struct tree_node {
    int element;
    struct tree_node *left;
    struct tree_node *right;
} *SEARCH_TREE;
```

### Exercice 1 — Fonctions de base

| Fonction | Description | Complexité |
|---|---|---|
| `insert(x, T)` | Insertion récursive | O(h) |
| `RechercherElement(A, e)` | Recherche récursive | O(h) |
| `NombreOccurences(A, e, n)` | Parcours complet | O(n) |
| `ParcoursInfixe(A)` | Affichage trié | O(n) |
| `ConstListeTriee(A, L)` | ABR → liste triée | O(n) |
| `ArbreAPartirDeListe(L)` | Liste → ABR | O(n·h) |
| `TrierListe(L)` | Tri par ABR interposé | O(n log n) moy. |

*h = hauteur de l'arbre. Pour un ABR équilibré, h = O(log n). Dans le pire cas (liste triée insérée), h = O(n).*

**Exemple de parcours infixé (forcément trié) :**
```
Infixe : 0 1 2 3 3 4 4 8 10 17
```

### Exercice 2 — Vérification ABR

Stratégie : extraire la liste infixée et vérifier qu'elle est triée en ordre croissant.

- **Complexité :** O(n)

```
A (construit par insertions) → ABR : OUI  ✓
B (violant la propriété)     → ABR : NON  ✓
```

### Exercice 3 — Plus petit élément

Descendre récursivement dans le sous-arbre gauche jusqu'à la feuille la plus à gauche.

- **Complexité :** O(h)

---

## Compilation et Exécution

### Prérequis
- GCC (GNU Compiler Collection)
- `make`
- Bibliothèque mathématique `-lm` (incluse dans le Makefile)

### Commandes

```bash
# Cloner le dépôt
git clone https://github.com/<votre-username>/structures-de-donnees-c.git
cd structures-de-donnees-c

# Compiler tous les TDs
make all

# Exécuter un TD spécifique
./TD1/td1
./TD2/td2
./TD3/td3
./TD4/td4

# Nettoyer les binaires
make clean
```

---

## Résultats des tests

Tous les programmes compilent **sans erreur ni avertissement** avec `gcc -Wall -Wextra`.

### TD1
```
Points apres tri par distance croissante :
(3, 37)   dist=37.12
(30, 24)  dist=38.42
(43, 0)   dist=43.00
(61, 42)  dist=74.06
(24, 88)  dist=91.21
H1 + H2 = 02:16:15  |  H1 - H2 = 00:45:15
```

### TD2
```
Indice premier minimum : 4  (tableau : 5 2 4 2 1 7 9 4 1 1)
MiniMax = 4
puissance(2,8) = expRapide(2,8) = 256
somme(2,4) = 31
rec1(5) = rec2(5) = 32
```

### TD3
```
Palindromes : "radar" ✓  "kayak" ✓  "bonjour" ✗
PairImpair  : impairs empilés au-dessus des pairs ✓
```

### TD4
```
Parcours infixé trié ✓
Tri de liste par ABR : [ 0 1 9 10 17 23 25 27 ] ✓
EstCeQueABR : OUI / NON selon construction ✓
LePlusPetit : minimum correct ✓
```

---

## Tableau récapitulatif des complexités

| TD | Algorithme | Complexité |
|---|---|---|
| TD2 Ex1 | Indice du minimum | O(n) |
| TD2 Ex2 | MiniMax matrice | O(n·m) |
| TD2 Ex3 | `puissance` récursive | O(n) |
| TD2 Ex3 | `expRapide` | O(log n) |
| TD2 Ex3 | `somme` | O(n²) |
| TD2 Ex4 | `rec1` | O(n) |
| TD2 Ex4 | `rec2` | O(2ⁿ) |
| TD3 Ex1 | Insertion en tête | O(1) |
| TD3 Ex2 | Recherche dans liste | O(n) |
| TD3 Ex3 | Suppression du min | O(n) |
| TD3 Ex6 | push / pop | O(1) |
| TD4 Ex1 | Insertion ABR | O(h) |
| TD4 Ex1 | Recherche ABR | O(h) |
| TD4 Ex1 | Parcours infixé | O(n) |
| TD4 Ex1 | Tri par ABR | O(n log n) moy. |
| TD4 Ex2 | Vérification ABR | O(n) |
| TD4 Ex3 | Plus petit élément | O(h) |

---

*Implémentation réalisée en langage C — gcc 12+*
