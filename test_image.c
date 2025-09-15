#include <stdio.h>
#include <stdlib.h>
#include "image.h"

int main() {
    // Test de la lecture d'une image depuis un fichier PBM
    char nom_fichier[] = "caractere2.pbm";
    printf("Lecture de l'image depuis le fichier '%s'\n", nom_fichier);
    Image image_originale = lire_fichier_image(nom_fichier);

    // Afficher l'image originale
    printf("Image originale :\n");
    ecrire_image(image_originale);

    // Test de la création du négatif
    printf("\nCréation de l'image négative...\n");
    Image image_negative = negatif_image(image_originale);

    // Afficher l'image négative
    printf("Image négative :\n");
    ecrire_image(image_negative);

    // Test de la sauvegarde de l'image négative dans un fichier
    char nom_fichier_negatif[] = "image_negative.pbm";
    FILE *fichier_negatif = fopen(nom_fichier_negatif, "w");
    fprintf(fichier_negatif, "P1\n");
    fprintf(fichier_negatif, "%u %u\n", largeur_image(image_negative), hauteur_image(image_negative));
    for (UINT y = 1; y <= hauteur_image(image_negative); y++) {
        for (UINT x = 1; x <= largeur_image(image_negative); x++) {
            fprintf(fichier_negatif, "%d ", get_pixel_image(image_negative, x, y));
        }
        fprintf(fichier_negatif, "\n");
    }
    fclose(fichier_negatif);

}