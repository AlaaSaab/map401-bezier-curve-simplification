#ifndef _SIMPLIFICATION_CONTOURS_H_
#define _SIMPLIFICATION_CONTOURS_H_

#include "geometrie2d.h"
#include "calcul_contour.h"

Liste_Contours calcul_contours_complet_simplification(Image I, double d);

Liste_Point approx_bezier2(Tableau_Point C, int j1, int j2);

double distance_point_bezier3(Point P, Liste_Point B);

Liste_Point simplification_douglas_peucker_bezier2(Tableau_Point C, int j1, int j2, double d);

Liste_Point elevation_degre_bezier2(Liste_Point B2);

Liste_Contours calcul_contours_complet_simplification_bezier2(Image I, double d);

Liste_Point approx_bezier3(Tableau_Point C, int j1, int j2);
Liste_Contours calcul_contours_complet_simplification_bezier3(Image I, double d);

Point calcul_point_bezier3(Liste_Point B, double t);

Liste_Point simplification_douglas_peucker_bezier3(Tableau_Point C, int j1, int j2, double d);


#endif
