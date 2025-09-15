#include "geometrie2d.h"
#include <math.h>

// Cree le point de coordonnée (x,y)
Point set_point(double x, double y){
    Point p = {x,y};
    return p;
}

// Cree un vecteur a partir de deux points
Vecteur creer_vecteur(Point A, Point B){
    Vecteur v;
    v.x = B.x - A.x;
    v.y = B.y - A.y;
    return v;
}

// somme P1+P2
Point add_point(Point P1, Point P2){
    return set_point(P1.x + P2.x, P1.y + P2.y);
}

// somme de deux vecteurs
Vecteur add_vecteurs(Vecteur u, Vecteur v){
    Vecteur w;
    w.x = u.x + v.x;
    w.y = u.y + v.y;
    return w;
}

// Vecteur correspondant au bipoint AB
Vecteur vect_bipoint(Point A, Point B){
    Vecteur v = {B.x - A.x, B.y - A.y};
    return v;
}

// Distance entre deux points A et B
double distance_points(Point A, Point B){
    return sqrt((B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y));
}

// Norme d'un vecteur
double norme_vecteur(Vecteur v){
    return sqrt((v.x * v.x) + (v.y * v.y));
}

// Produit scalaire de deux vecteurs
double produit_scalaire(Vecteur u, Vecteur v){
    return (u.x * v.x + u.y * v.y);
}

// Multiplication d'un point par un scalaire
Point multiplier_point(Point A, double k){
    Point B; 
    B.x = A.x * k;
    B.y = A.y * k;
    return B;
}


double distance(Point A, Point B) {
    double dx = A.x - B.x;
    double dy = A.y - B.y;
    return sqrt(dx * dx + dy * dy);
}


// Multiplication d'un vecteur par un scalaire
Vecteur multiplier_vecteur(Vecteur v, double k){
    Vecteur w; 
    w.x = v.x * k;
    w.y = v.y * k;
    return w;
}

Point div_point(Point A, double k) {
    if (k == 0) {
        return A;
    }
    Point B;
    B.x = A.x / k;
    B.y = A.y / k;
    return B;
}
Point sub_point(Point P1, Point P2){
    return set_point(P1.x - P2.x, P1.y - P2.y);
}

double distance_point_segments(Point P, Point A, Point B){
    double dp;
    Vecteur v;
    if(A.x == B.x && A.y == B.y){
        v = vect_bipoint(A, P);
        dp = norme_vecteur(v);
        return dp;
    }
    // On calcul lambda
    Vecteur AP, AB, BP;
    AP = vect_bipoint(A, P);
    AB = vect_bipoint(A, B);
    BP = vect_bipoint(B, P);
    double lambda = produit_scalaire(AP, AB) / produit_scalaire(AB, AB);
    if(lambda < 0){
        dp = norme_vecteur(AP);
    }
    else if(lambda > 1){
        dp = norme_vecteur(BP);
    }
    else{
        Point Q;
        Q.x = A.x + lambda * (B.x - A.x);
        Q.y = A.y + lambda * (B.y - A.y);
        dp = norme_vecteur(vect_bipoint(Q, P));
    }
    return dp;
}