#include <stdio.h>
#include "geometrie2d.h"

int main() {
    Point A = {1.0, 0.0};
    Point B = {5.0, 3.0};

    // Création d'un vecteur
    Vecteur u = creer_vecteur(A, B);
    printf("Vecteur AB: (%.2f, %.2f)\n", u.x, u.y);

    // Norme d'un vecteur
    printf("Norme du vecteur AB: %.2f\n", norme_vecteur(u));

    // Produit scalaire
    Vecteur v = {1.0, 0.0};
    printf("Produit scalaire de AB et (1,0): %.2f\n", produit_scalaire(u, v));

    // Somme de deux points
    Point C = add_point(A, B);
    printf("Somme de A et B: (%.2f, %.2f)\n", C.x, C.y);

    // Distance entre deux points
    printf("Distance entre A et B: %.2f\n", distance_points(A, B));

    // Multiplication d'un vecteur par un scalaire
    Vecteur w = multiplier_vecteur(u, 2.0);
    printf("Vecteur AB multiplié par 2: (%.2f, %.2f)\n", w.x, w.y);

    return 0;
}
