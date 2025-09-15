#include "image.h"
#include "calcul_contour.h"
#include "generer_eps.h"
#include "geometrie2d.h"


void generer_eps(char *image_fichier, int mode){
    Image I = lire_fichier_image(image_fichier);
    Image masque = creer_masque(I);
    Point depart = trouver_pixel_depart(I);
    Liste_Point contour = calcul_contours(I, masque, depart);
    Tableau_Point points = sequence_points_liste_vers_tableau(contour);
    char nom_fichier_eps[256];
    strcpy(nom_fichier_eps, image_fichier);
    char *ext = strrchr(nom_fichier_eps, '.');
    if(ext){
        *ext = '\0';
    }
    strcat(nom_fichier_eps, ".eps");

    FILE *f = fopen(nom_fichier_eps, "w");
    if(f == NULL){
        return;
    }
    fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f, "%%%%BoundingBox: 0 0 %u %u\n", largeur_image(I), hauteur_image(I));
    if(contour.taille > 0){
        fprintf(f, "%f %f moveto\n", points.tab[0].x, hauteur_image(I) - points.tab[0].y);
        for (int i = 1; i < contour.taille; i++) {
            fprintf(f, "%f %f lineto\n", points.tab[i].x, hauteur_image(I) - points.tab[i].y);
        }
        if (mode == 0) {
            fprintf(f, "0 setlinewidth\n");
            fprintf(f, "stroke\n");
        } else {
            fprintf(f, "fill\n");
        }
    }
    fprintf(f, "showpage\n");
    fclose(f);

    printf("Fichier EPS créé : %s\n", nom_fichier_eps);
}

void generer_eps_contours(char *nom_fichier, Liste_Contours contours, unsigned int largeur, unsigned int hauteur, int mode) {
    char nom_fichier_eps[256];
    strcpy(nom_fichier_eps, nom_fichier);
    char *ext = strrchr(nom_fichier_eps, '.');
    if(ext){
        *ext = '\0';
    }
    strcat(nom_fichier_eps, ".eps");
    FILE *f = fopen(nom_fichier_eps, "w");
    if (f == NULL) {
        printf("Erreur: Impossible de créer le fichier EPS %s\n", nom_fichier);
        return;
    }

    fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f, "%%%%BoundingBox: 0 0 %u %u\n", largeur, hauteur);

    Cellule_Liste_Contours *cellule = contours.first;
    while (cellule != NULL) {
        Liste_Point contour = cellule->contour;
        if (contour.taille > 0) {
            Tableau_Point points = sequence_points_liste_vers_tableau(contour);
            fprintf(f, "%f %f moveto\n", points.tab[0].x, hauteur - points.tab[0].y);
            for (int i = 1; i < contour.taille; i++) {
                fprintf(f, "%f %f lineto\n", points.tab[i].x, hauteur - points.tab[i].y);
            }
        }
        cellule = cellule->suiv;
    }

    if (mode == 0) {
        fprintf(f, "0 setlinewidth\n");
        fprintf(f, "stroke\n");
    } else {
        fprintf(f, "fill\n");
    }
    fprintf(f, "showpage\n");
    fclose(f);

    printf("Fichier EPS créé : %s\n", nom_fichier_eps);
}

void ecrire_eps_bezier2(Image I, Liste_Contours courbes, const char* nom_fichier_eps, int mode) {
    FILE* f = fopen(nom_fichier_eps, "w");
    if (!f) {
        printf("Erreur ouverture fichier EPS\n");
        return;
    }

    fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f, "%%%%BoundingBox: 0 0 %u %u\n", largeur_image(I), hauteur_image(I));
    fprintf(f, "0 setlinewidth\n");

    Cellule_Liste_Contours* cell_contour = courbes.first;
    while (cell_contour != NULL) {
        Liste_Point B = cell_contour->contour;
        Cellule_Liste_Point* p = B.first;

        if (B.taille >= 3) {
            int first = 1;
            while (p && p->suiv && p->suiv->suiv) {
                Point C0 = p->data; p = p->suiv;
                
                if (first == 1) {
                    fprintf(f, "%f %f moveto\n", C0.x, hauteur_image(I) - C0.y);
                    first = 0;
                }
                Point C1 = p->data; p = p->suiv;
                Point C2 = p->data; p = p->suiv;

                Point D1 = add_point(multiplier_point(C0, 1.0/3.0), multiplier_point(C1, 2.0/3.0));
                Point D2 = add_point(multiplier_point(C1, 2.0/3.0), multiplier_point(C2, 1.0/3.0));

                fprintf(f, "%f %f %f %f %f %f curveto\n",
                        D1.x, hauteur_image(I) - D1.y,
                        D2.x, hauteur_image(I) - D2.y,
                        C2.x, hauteur_image(I) - C2.y);
            }
        }

        cell_contour = cell_contour->suiv;
    }
    if (mode == 0) {
        fprintf(f, "0 setlinewidth\n");
        fprintf(f, "stroke\n");
    } else {
        fprintf(f, "fill\n");
    }
    fprintf(f, "showpage\n");
    fclose(f);
    printf("EPS généré : %s\n", nom_fichier_eps);
}

void ecrire_eps_bezier3(Image I, Liste_Contours courbes, const char* nom_fichier_eps, int mode) {
    FILE* f = fopen(nom_fichier_eps, "w");
    if (!f) {
        printf("Erreur ouverture fichier EPS\n");
        return;
    }

    fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f, "%%%%BoundingBox: 0 0 %u %u\n", largeur_image(I), hauteur_image(I));
    fprintf(f, "0 setlinewidth\n");

    Cellule_Liste_Contours* cell_contour = courbes.first;
    while (cell_contour != NULL) {
        Liste_Point B = cell_contour->contour;
        Cellule_Liste_Point* p = B.first;

        if (B.taille >= 4) {
            int first = 1;
            while (p && p->suiv && p->suiv->suiv) {
                Point C0 = p->data; p = p->suiv;
                
                if (first == 1){
                    fprintf(f, "%f %f moveto\n", C0.x, hauteur_image(I) - C0.y);
                    first = 0;
                }
                Point C1 = p->data; p = p->suiv;
                Point C2 = p->data; p = p->suiv;
                Point C3 = p->data; p = p->suiv;

                fprintf(f, "%f %f %f %f %f %f curveto\n",
                        C1.x, hauteur_image(I) - C1.y,
                        C2.x, hauteur_image(I) - C2.y,
                        C3.x, hauteur_image(I) - C3.y);
            }
            
        }

        cell_contour = cell_contour->suiv;
    }
    if (mode == 0) {
        fprintf(f, "0 setlinewidth\n");
        fprintf(f, "stroke\n");
    } else {
        fprintf(f, "fill\n");
    }
    fprintf(f, "showpage\n");
    fclose(f);
    printf("EPS généré : %s\n", nom_fichier_eps);
}