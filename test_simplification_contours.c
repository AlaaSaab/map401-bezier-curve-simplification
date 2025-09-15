#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "simplification_contours.h"
#include "generer_eps.h"

int compter_beziers(Liste_Contours L, int degre) {
    int nb_beziers = 0;
    if (degre == 2){
        Cellule_Liste_Contours *current = L.first;
        while(current != NULL){
            nb_beziers = nb_beziers + current->contour.taille/3;
            current = current->suiv;
        }
        return nb_beziers;
    }
    if (degre == 3){
        Cellule_Liste_Contours *current = L.first;
        while(current != NULL){
            nb_beziers = nb_beziers + current->contour.taille/4;
            current = current->suiv;
        }
        return nb_beziers;
    }
    return -1;
}


int main(int argc, char **argv) {
    if (argc != 5) {
        printf("Usage: %s <fichier_image.pbm> <type_simplification> <seuil> <mode_rendu>\n", argv[0]);
        printf("type_simplification: 1 pour Douglas-Peucker\n");
        printf("                    2 pour Bézier2\n");
        printf("                    3 pour Bézier3\n");
        printf("seuil: valeur du seuil de simplification (nombre décimal positif)\n");
        printf("mode_rendu: 0 pour stroke (contour)\n");
        printf("           1 pour fill (remplissage)\n");
        return EXIT_FAILURE;
    }

    int type_simplification = atoi(argv[2]);
    if (type_simplification < 1 || type_simplification > 3) {
        printf("Erreur: Le type de simplification doit être 1 (Douglas-Peucker), 2 (Bezier2) ou 3 (Bezier3)\n");
        return EXIT_FAILURE;
    }

    double seuil = atof(argv[3]);
    

    int mode_rendu = atoi(argv[4]);
    if (mode_rendu != 0 && mode_rendu != 1) {
        printf("Erreur: Le mode de rendu doit être 0 (stroke) ou 1 (fill)\n");
        return EXIT_FAILURE;
    }

    Image I = lire_fichier_image(argv[1]);
    
    char nom_fichier_eps[256];
    strcpy(nom_fichier_eps, argv[1]);
    char *ext = strrchr(nom_fichier_eps, '.');
    if(ext) {
        *ext = '\0';
    }
   switch(type_simplification) {
            case 1: {
                // Simplification Douglas-Peucker
                char seuil_str[10];
                sprintf(seuil_str, "_d%d", (int)seuil);
                strcat(nom_fichier_eps, seuil_str);
                strcat(nom_fichier_eps, "_contours.eps");
                Liste_Contours contours = calcul_contours_complet_simplification(I,seuil);
                printf("Nombre de contours: %d\n", contours.taille);
                printf("Nombre de segments: %d\n", nb_segment_contours(contours));
                generer_eps_contours(nom_fichier_eps, contours, largeur_image(I), hauteur_image(I), mode_rendu);
                break;
            }
            case 2: {
                // Simplification Bézier2
                strcat(nom_fichier_eps, "_bezier2_d");
                char seuil_str[10];
                sprintf(seuil_str, "%d", (int)seuil);
                strcat(nom_fichier_eps, seuil_str);
                strcat(nom_fichier_eps, ".eps");
                Liste_Contours B2 = calcul_contours_complet_simplification_bezier2(I, seuil);
                printf("Nombre de courbes Bézier2: %d\n", compter_beziers(B2, 2));
                ecrire_eps_bezier2(I, B2, nom_fichier_eps, mode_rendu);
                break;
            }
            case 3: {
                // Simplification Bézier3
                strcat(nom_fichier_eps, "_bezier3_d");
                char seuil_str[10];
                sprintf(seuil_str, "%d", (int)seuil);
                strcat(nom_fichier_eps, seuil_str);
                strcat(nom_fichier_eps, ".eps");
                Liste_Contours B3 = calcul_contours_complet_simplification_bezier3(I, seuil);
                printf("Nombre de courbes Bézier3: %d\n", compter_beziers(B3, 3));
                ecrire_eps_bezier3(I, B3, nom_fichier_eps, mode_rendu);
                break;
            }
        }
    
    supprimer_image(&I);
    return EXIT_SUCCESS;
}

