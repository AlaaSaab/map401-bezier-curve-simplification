#include "simplification_contours.h"

Liste_Point simplification_douglas_peucker(Tableau_Point tab_contour, int j1, int j2, double d){
    Liste_Point L, L1, L2;
    L = creer_liste_Point_vide();

    int k;

    Point Pj,Pj1,Pj2;

    double dmax,dj;

    Pj1 = tab_contour.tab[j1];
    Pj2 = tab_contour.tab[j2];

    dmax = 0;
    k = j1;

    for(int j = j1+1; j < j2; j++){
        Pj = tab_contour.tab[j];
        dj = distance_point_segments(Pj, Pj1, Pj2);
        if(dmax < dj){
            dmax = dj;
            k = j;
        }
    }

    if(dmax <= d){
        L = ajouter_element_liste_Point(L, Pj1);
        L = ajouter_element_liste_Point(L, Pj2);
        return L;
    }

    L1 = simplification_douglas_peucker(tab_contour, j1, k, d);
    L2 = simplification_douglas_peucker(tab_contour, k, j2, d);
    L2 = supprimer_premier_element_liste_Point(L2);
    L = concatener_liste_Point(L1, L2);
    return L;
}

Liste_Contours calcul_contours_complet_simplification(Image I, double d){
    Liste_Contours contours = creer_liste_Contours_vide();
    Image masque = creer_masque(I);
    while(est_blanc(masque) == 0){
        Point depart = trouver_pixel_depart(masque);
        Liste_Point L = calcul_contours(I, masque, depart);
        Tableau_Point tab_contour = sequence_points_liste_vers_tableau(L);
        L = simplification_douglas_peucker(tab_contour, 0, L.taille - 1, d);
        //ecrire_contour(L);
        contours = ajouter_element_liste_Contours(contours, L);
    }
    supprimer_image(&masque);
    return contours;
}


Liste_Point approx_bezier2(Tableau_Point C, int j1, int j2) {
    Liste_Point bezier = creer_liste_Point_vide();
    int n = j2 - j1;
    Point C0 = C.tab[j1];
    Point C2 = C.tab[j2];
    Point C1;

    if (n == 1) {
        C1.x = (C0.x + C2.x) / 2.0;
        C1.y = (C0.y + C2.y) / 2.0;
    } else {
        double a = (3.0 * n) / ((n * n) - 1.0); 
        double b  = (1.0 - 2.0 * n) / (2.0 * (n + 1));
        Point somme = set_point(0.0, 0.0);
        for (int i = 1; i < n; i++) {
            somme = add_point(somme, C.tab[j1 + i]);
        }
        
        C1 = add_point(multiplier_point(somme, a), multiplier_point(add_point(C0, C2),b));
    }

    bezier = ajouter_element_liste_Point(bezier, C0);
    bezier = ajouter_element_liste_Point(bezier, C1);
    bezier = ajouter_element_liste_Point(bezier, C2);

    return bezier;
}


Liste_Point simplification_douglas_peucker_bezier2(Tableau_Point C, int j1, int j2, double d) {
    Liste_Point L = creer_liste_Point_vide();
    int n = j2 - j1;
    
    
    
    if (n <= 1) {
        return approx_bezier2(C, j1, j2);
    }

    Liste_Point B = approx_bezier2(C, j1, j2);
    double dmax = 0.0;
    int k = j1;

    for (int j = j1 + 1; j < j2; j++) {
        double t = (double)(j - j1) / (double)n;
        Point Pj = C.tab[j];
        Point B0 = B.first->data;
        Point B1 = B.first->suiv->data;
        Point B2 = B.first->suiv->suiv->data;
        
        double u = 1 - t;
        Point Bt = set_point(
            u*u*B0.x + 2*t*u*B1.x + t*t*B2.x,
            u*u*B0.y + 2*t*u*B1.y + t*t*B2.y
        );
        
        double dj = distance(Pj, Bt);
        if (dj > dmax) {
            dmax = dj;
            k = j;
        }
    }


    if (dmax <= d) {
        L = B;
    } else {
        Liste_Point L1 = simplification_douglas_peucker_bezier2(C, j1, k, d);
        Liste_Point L2 = simplification_douglas_peucker_bezier2(C, k, j2, d);
        L = concatener_liste_Point(L1, L2);
    }

    return L;
}


Liste_Contours calcul_contours_complet_simplification_bezier2(Image I, double d){
    Liste_Contours contours = creer_liste_Contours_vide();
    Image masque = creer_masque(I);
    while(est_blanc(masque) == 0){
        Point depart = trouver_pixel_depart(masque);
        Liste_Point L = calcul_contours(I, masque, depart);
        Tableau_Point tab_contour = sequence_points_liste_vers_tableau(L);
        L = simplification_douglas_peucker_bezier2(tab_contour, 0, L.taille - 1, d);
        //ecrire_contour(L);
        contours = ajouter_element_liste_Contours(contours, L);
    }
    supprimer_image(&masque);
    return contours;
}


Liste_Point elevation_degre_bezier2(Liste_Point B2) {
    Cellule_Liste_Point* p = B2.first;
    Point C0 = p->data; p = p->suiv;
    Point C1 = p->data; p = p->suiv;
    Point C2 = p->data;

    Point D0 = C0;
    Point D1 = add_point(multiplier_point(C0, 1.0/3.0), multiplier_point(C1, 2.0/3.0));
    Point D2 = add_point(multiplier_point(C1, 2.0/3.0), multiplier_point(C2, 1.0/3.0));
    Point D3 = C2;

    Liste_Point B3 = creer_liste_Point_vide();
    B3 = ajouter_element_liste_Point(B3, D0);
    B3 = ajouter_element_liste_Point(B3, D1);
    B3 = ajouter_element_liste_Point(B3, D2);
    B3 = ajouter_element_liste_Point(B3, D3);

    return B3;
}

//tache 7 - 2 

Liste_Point approx_bezier3(Tableau_Point T, int j1, int j2) {
    int n = j2 - j1;
    Liste_Point B = creer_liste_Point_vide();

    if (n < 1) return B; // trop court

    if (n<3){
        Liste_Point B2 = approx_bezier2(T,j1,j2);
        Liste_Point B3 = elevation_degre_bezier2(B2);
        return B3;
    }

    Point C0 = T.tab[j1];
    Point C3 = T.tab[j2];

    double nd = (double)n;
    double alpha = (-15 * pow(nd,3) + 5 * nd * nd + 2 * nd + 4) / (3 * (nd + 2) * (3 * nd * nd + 1));
    double beta  = (10 * pow(nd,3) - 15 * nd * nd + nd + 2) / (3 * (nd + 2) * (3 * nd * nd + 1));
    double lambda = (70 * nd) / (3 * (nd * nd - 1) * (nd * nd - 4) * (3 * nd * nd + 1));

    Point S1 = {0.0, 0.0};
    Point S2 = {0.0, 0.0};

    for (int i = 1; i < n; i++) {
        double k = (double)i;
        double gamma_i = 6*pow(k,4) - 8*nd*pow(k,3) + 6*pow(k,2) - 4*nd*k + pow(nd,4) - pow(nd,2);
        S1.x += gamma_i * T.tab[j1 + i].x;
        S1.y += gamma_i * T.tab[j1 + i].y;

        double gamma_ni = 6*pow((nd - k),4) - 8*nd*pow((nd - k),3) + 6*pow((nd - k),2) - 4*nd*(nd - k) + pow(nd,4) - pow(nd,2);
        S2.x += gamma_ni * T.tab[j1 + i].x;
        S2.y += gamma_ni * T.tab[j1 + i].y;
    }
    Point C1 = set_point(
        alpha * C0.x + lambda * S1.x + beta * C3.x,
        alpha * C0.y + lambda * S1.y + beta * C3.y
    );
    if (isnan(C1.x)){
        printf("C1.x❌");

    }
    if (isnan(C1.y)){
        printf("C1.y❌");

    }
    Point C2 = set_point(
        beta * C0.x + lambda * S2.x + alpha * C3.x,
        beta * C0.y + lambda * S2.y + alpha * C3.y
    );

    B = ajouter_element_liste_Point(B, C0);
    B = ajouter_element_liste_Point(B, C1);
    B = ajouter_element_liste_Point(B, C2);
    B = ajouter_element_liste_Point(B, C3);

    return B;
}

Liste_Point simplification_douglas_peucker_bezier3(Tableau_Point C, int j1, int j2, double d) {
    Liste_Point L = creer_liste_Point_vide();
    int n = j2 - j1;
    if (n <= 1) {
        return approx_bezier3(C, j1, j2);
    }
    
    Liste_Point B = approx_bezier3(C, j1, j2);
    double dmax = 0.0;
    int k = j1;

    for (int j = j1 + 1; j < j2; j++) {
        double t = (double)(j - j1) / (double)n;
        Point Pj = C.tab[j];
        Point B0 = B.first->data;
        Point B1 = B.first->suiv->data;
        Point B2 = B.first->suiv->suiv->data;
        Point B3 = B.first->suiv->suiv->suiv->data;
        
        double u = 1 - t;
        Point Bt = set_point(
            u*u*u*B0.x + 3*t*u*u*B1.x + 3*t*t*u*B2.x + t*t*t*B3.x,
            u*u*u*B0.y + 3*t*u*u*B1.y + 3*t*t*u*B2.y + t*t*t*B3.y
        );
        
        double dj = distance(Pj, Bt);
        if (dj > dmax) {
            dmax = dj;
            k = j;
        }
    }

    if (dmax <= d) {
        L = B;
    } else {
        Liste_Point L1 = simplification_douglas_peucker_bezier3(C, j1, k, d);
        Liste_Point L2 = simplification_douglas_peucker_bezier3(C, k, j2, d);
        L = concatener_liste_Point(L1, L2);
    }

    return L;
}


Liste_Contours calcul_contours_complet_simplification_bezier3(Image I, double d){
    Liste_Contours contours = creer_liste_Contours_vide();
    Image masque = creer_masque(I);
    while(est_blanc(masque) == 0){
        Point depart = trouver_pixel_depart(masque);
        Liste_Point L = calcul_contours(I, masque, depart);
        Tableau_Point tab_contour = sequence_points_liste_vers_tableau(L);
        L = simplification_douglas_peucker_bezier3(tab_contour, 0, L.taille - 1, d);
        //ecrire_contour(L);
        contours = ajouter_element_liste_Contours(contours, L);
    }
    supprimer_image(&masque);
    return contours;
}




