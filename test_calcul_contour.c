#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "calcul_contour.h"
#include "generer_eps.h"
#include "geometrie2d.h"


int main(int argc, char **argv){
    if (argc != 3) {
        printf("Usage: %s <fichier_image> <mode>\n", argv[0]);
        printf("mode: 0 pour stroke (contour), 1 pour fill (remplissage)\n");
        return EXIT_FAILURE;
    }

    int mode = atoi(argv[2]);
    if (mode != 0 && mode != 1) {
        printf("Erreur: Le mode doit être 0 (stroke) ou 1 (fill)\n");
        return EXIT_FAILURE;
    }

    char nom_fichier_eps[256];
    strcpy(nom_fichier_eps, argv[1]);
    char *ext = strrchr(nom_fichier_eps, '.');
    if(ext){
        *ext = '\0';
    }
    strcat(nom_fichier_eps, ".eps");
    Image I = lire_fichier_image(argv[1]);
    Liste_Contours contours = calcul_contours_complet(I);
    generer_eps_contours(nom_fichier_eps, contours, largeur_image(I), hauteur_image(I), mode);
    supprimer_image(&I);
    return 0;
}
