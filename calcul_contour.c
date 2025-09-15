#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "calcul_contour.h"

/*Cette fonction va renvoyer le premier pixel candidat*/
Point trouver_pixel_depart(Image I){
    UINT l = largeur_image(I);
    UINT h = hauteur_image(I);

    Point candidat;
    for(int j = 1; j <= h; j ++){
        for(int i = 1; i <= l; i ++){
            if(get_pixel_image(I, i, j) == NOIR && get_pixel_image(I, i, j-1) == BLANC){
                candidat.x = i;
                candidat.y = j;
                return candidat;
            }
        }
    }
    exit(EXIT_FAILURE);
}

/*Avaner le robot de detection du contour*/
Point avancer(Point P, Orientation o){
    Point new_point = P;
    switch (o)
    {
    case N:
        new_point.y--;
        break;
    case S:
        new_point.y++;
        break;
    case E:
        new_point.x++;
        break;
    case O:
        new_point.x--;
        break;
        
    default:
        break;
    }
    return new_point;
}

/*Tourner a droit*/
Orientation droit(Orientation ori){
    Orientation new_ori;
       switch (ori)
    {
    case N:
        new_ori = E;
        break;
    case S:
        new_ori = O;
        break;
    case E:
        new_ori = S;
        break;
    case O:
        new_ori = N;
        break;
        
    default:
        break;
    }
    return new_ori;

}

/*Tourner a gauche*/
Orientation gauche(Orientation ori){
    Orientation new_ori;
    switch (ori)
    {
    case N:
        new_ori = O;
        break;
    case S:
        new_ori = E;
        break;
    case E:
        new_ori = N;
        break;
    case O:
        new_ori = S;
        break;
        
    default:
        break;
    }
    return new_ori;

}

/*Calculer la nouvelle orientation*/
Orientation nouvelle_orientation(Image I, Point P, Orientation ori){
    Pixel pd, pg;
    Orientation new_ori = ori;
    switch (ori)
    {
    case E:
        pg = get_pixel_image(I, P.x + 1, P.y);
        pd = get_pixel_image(I, P.x + 1, P.y + 1);
        break;
    case N:
        pg = get_pixel_image(I, P.x, P.y);
        pd = get_pixel_image(I, P.x + 1, P.y);
        break;
    case O:
        pg = get_pixel_image(I, P.x, P.y + 1);
        pd = get_pixel_image(I, P.x, P.y);
        break;
    case S:
        pg = get_pixel_image(I, P.x + 1, P.y + 1);
        pd = get_pixel_image(I, P.x, P.y + 1);
        break;
    default:
        return ori;
        break;
    }

    if(pg == BLANC && pd == BLANC){
        new_ori = droit(ori);
    }
    else if (pg == NOIR){
        new_ori = gauche(ori);
    }
    return new_ori;
}

int nb_segment(Liste_Point L){
    if(L.taille > 0){
        return L.taille - 1;
    }
    else return 0;
}

Liste_Point memoriser_position(Liste_Point L, Point P){
    L = ajouter_element_liste_Point(L, P);
    return L;
}

Liste_Point calcul_contours(Image I, Image masque, Point candidat){
    Liste_Point L = creer_liste_Point_vide();
    Point pos = {candidat.x-1,candidat.y-1};
    L = ajouter_element_liste_Point(L, pos);
    Orientation orientation = E;
    int boucle = 1;
    while(boucle == 1){
        pos = avancer(pos, orientation);
        L = ajouter_element_liste_Point(L, pos);
        orientation = nouvelle_orientation(I, pos, orientation);
        if(orientation == E){
            set_pixel_image(masque, pos.x+1, pos.y+1, BLANC);
        }
        if(pos.x == candidat.x-1 && pos.y == candidat.y-1 && orientation == E){
            boucle = 0;
        }
    }
    return L;
}

int est_blanc(Image I){
    UINT l = largeur_image(I);
    UINT h = hauteur_image(I);
    for(int i = 1; i <= l; i++){
        for(int j = 1; j <= h; j++){
            if(get_pixel_image(I, i, j) == NOIR){
                return 0;
            }
        }
    }
    return 1;
}

Image creer_masque(Image I){
    UINT h,l;
    h = hauteur_image(I);
    l = largeur_image(I);
    Image masque = creer_image(l, h);
    for(int j = 1; j <= h; j ++){
        for(int i = 1; i <= l; i ++){
            if(get_pixel_image(I, i, j) == NOIR && get_pixel_image(I, i, j-1) == BLANC){
                set_pixel_image(masque, i, j, NOIR);
            }
        }
    }
    return masque;
}

Liste_Contours calcul_contours_complet(Image I){
    Liste_Contours contours = creer_liste_Contours_vide();
    Image masque = creer_masque(I);
    while(est_blanc(masque) == 0){
        Point depart = trouver_pixel_depart(masque);
        Liste_Point L = calcul_contours(I, masque, depart);
        //ecrire_contour(L);
        contours = ajouter_element_liste_Contours(contours, L);
    }
    supprimer_image(&masque);
    return contours;
}

int nb_segment_contours(Liste_Contours contours){
    int nb = 0;
    Cellule_Liste_Contours *cellule = contours.first;
    while (cellule != NULL){
        nb = nb + cellule->contour.taille;
        cellule = cellule->suiv;
    }
    return nb - contours.taille;

}