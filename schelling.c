#include <stdlib.h>
#include <stdio.h>

#include "schelling.h"


Schelling *schellingInit(int height, int width, double probRed, double probBlue, double satisRatio) {
    // Implementation de schellingInit

    Schelling *schelling = malloc(sizeof(Schelling));
    if(!schelling)
        return NULL;

    CellType **grille = malloc(height * sizeof(CellType*));
    if(!grille)
        return NULL;
    for(int t = 0; t < height; t++){
        grille[t] = malloc(width * sizeof(CellType));
        if(!grille[t]){
            return NULL;
        }
    }

    schelling->height = height;
    schelling->width = width;
    schelling->satisRatio = satisRatio;
    schelling->grid = grille;

    double aleatoire;
    int vide = 0;

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            aleatoire = ((double) rand())/ (double) RAND_MAX;
            if(aleatoire < probBlue){
                schelling->grid[i][j] = BLUE;
            }
            else if(aleatoire < (probBlue + probRed)){
                schelling->grid[i][j] = RED;
            }
            else{
                schelling->grid[i][j] = EMPTY;
                vide++;
            }
        }
    }

    schelling->nbEmpty = vide;

    return schelling;
}


int schellingIsUnsatisfied(Schelling* schelling, int h, int w) {
    // Implementation de schellingIsUnsatisfied

    if(h < 0 || h >= (schelling->height) || w < 0 || w >= (schelling->width) || schelling->grid[h][w] == EMPTY)
        return -1;

    int voisin = 0;
    int voisin_section = 0;

    for(int i = h - 1; i <= h + 1; i++){
        if(i < 0 || i >= (schelling->height))
            continue;
        for(int j = w - 1; j <= w + 1; j++){
            if(j < 0 || j >= (schelling->width))
                continue;
            else if(i == h && j == w)
                continue;
            else if((schelling->grid)[i][j] != EMPTY){
                voisin++;
                if(schelling->grid[h][w] == schelling->grid[i][j]){
                    voisin_section++;
                }
            }
        }
    }
    if(voisin == 0){
        return 0;
    }

    if((double) voisin_section/(double) voisin < (schelling->satisRatio)){
        return 1;
    }

    return 0;
}


// Complexity : O(N*M)
int schellingOneStep(Schelling *schelling) {
    // Implementation de schellingOneStep

    //SI il n'y a pas de cases vides
    if(schelling->nbEmpty == 0)
        return 0;

    int tableau_insatisfait[((schelling->height)*(schelling->width)-(schelling->nbEmpty))][2];
    int tableau_vide[schelling->nbEmpty][2];
    
    int compteur_vide = 0;
    int nb = 0;

    for(int i = 0; i < schelling->height; i++){
        for(int j = 0; j < schelling->width; j++){
            if(schellingIsUnsatisfied(schelling, i, j) == 1){
                tableau_insatisfait[nb][0] = i;
                tableau_insatisfait[nb][1] = j;
                nb++;
            }
            if(schelling->grid[i][j] == EMPTY){
                tableau_vide[compteur_vide][0] = i;
                tableau_vide[compteur_vide][1] = j;
                compteur_vide++;
            }
        }
    }

    for(int a = 0; a < nb; a++){
        //(1) tirer un étudiant insatisfait aléatoirement parmi les étudiants non encore considérés,
        int au_hazard_insatisfait = rand() % (nb - a);
        
        //(2) tirer un case vide parmi toutes les cases vides,
        int au_hazard_vide = rand() % schelling->nbEmpty;

        //(3) échanger la case vide et l’étudiant dans la grille
        int h_1 = tableau_insatisfait[au_hazard_insatisfait][0];
        int w_1 = tableau_insatisfait[au_hazard_insatisfait][1];
        int h_2 = tableau_vide[au_hazard_vide][0];
        int w_2 = tableau_vide[au_hazard_vide][1];
        CellType tmp = schelling->grid[h_1][w_1];
        schelling->grid[h_1][w_1] = schelling->grid[h_2][w_2];
        schelling->grid[h_2][w_2] = tmp;

        //(3) remplacer la case vide dans la liste des cases vides par la case précédemment occupée par l’étudiant,
        tableau_vide[au_hazard_vide][0] = h_1;
        tableau_vide[au_hazard_vide][1] = w_1;

        // (4) retirer l’étudiant insatisfait de la liste des étudiants.
        tableau_insatisfait[au_hazard_insatisfait][0] = tableau_insatisfait[nb - 1 - a][0];
        tableau_insatisfait[au_hazard_insatisfait][1] = tableau_insatisfait[nb - 1 - a][1];
    }

    return nb;
}


void matrix_free(Schelling *);

void matrix_free(Schelling *schelling){
    for(int t = 0; t < (schelling->height); t++){
        free(schelling->grid[t]);
    }
    free(schelling->grid);
    free(schelling);
}


void schellingFree(Schelling *schelling) {
    // Implementation de schelling Free

    matrix_free(schelling);
}
