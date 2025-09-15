#ifndef _CALCUL_CONTOUR_H_
#define _CALCUL_CONTOUR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sequence_point.h"
#include "image.h"

typedef enum {N,S,E,O} Orientation;

/*Cette fonction va renvoyer le premier pixel candidat*/
Point trouver_pixel_depart(Image I);

/*Avaner le robot de detection du contour*/
Point avancer(Point P, Orientation O);

/*Tourner a droit*/
Orientation droit(Orientation ori);

/*Tourner a gauche*/
Orientation gauche(Orientation ori);

/*Calculer la nouvelle orientation*/
Orientation nouvelle_orientation(Image I, Point P, Orientation ori);

int nb_segment(Liste_Point L);

Liste_Point memoriser_position(Liste_Point L, Point P);

Liste_Point calcul_contours(Image I, Image masque, Point candidat);

Image creer_masque(Image I);

int est_blanc(Image I);

void delete_pixel_masque(Image masque, Point p);

Liste_Contours calcul_contours_complet(Image I);

int nb_segment_contours(Liste_Contours contours);

#endif