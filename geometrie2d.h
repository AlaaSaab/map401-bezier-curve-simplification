#ifndef _GEOMETRIE2D_H_
#define _GEOMETRIE2D_H_

#include <math.h>

typedef struct Vecteur_
{
    double x,y; // les coordonnees du vecteur.
}Vecteur;

typedef struct Point_
{
    double x,y; // les coordonnees du point.
}Point;

Vecteur creer_vecteur(Point A, Point B);

// Cree le point de coordonnée (x,y)
Point set_point(double x, double y);

// somme P1+P2
Point add_point(Point P1, Point P2);

// somme de deux vecteurs
Vecteur add_vecteurs(Vecteur u, Vecteur v);

// Vecteur correspondant au bipoint AB
Vecteur vect_bipoint(Point A, Point B);

// Distance entre deux points A et B
double distance_points(Point A, Point B);

// Norme d'un vecteur
double norme_vecteur(Vecteur v);

// Produit scalaire de deux vecteurs
double produit_scalaire(Vecteur u, Vecteur v);

// Multiplication d'un point par un scalaire
Point multiplier_point(Point A, double k);

// Multiplication d'un vecteur par un scalaire
Vecteur multiplier_vecteur(Vecteur v, double k);

Point div_point(Point A, double k);

Point sub_point(Point P1, Point P2);

// Calculer la distance entre un point P et un segment AB
double distance_point_segments(Point P, Point A, Point B);

double distance(Point A, Point B);

#endif