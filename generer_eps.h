#ifndef _GENERER_EPS_H_
#define _GENERER_EPS_H_

void generer_eps(char *image_fichier, int mode);

void generer_eps_contours(char *nom_fichier, Liste_Contours contours, unsigned int largeur, unsigned int hauteur, int mode);

void ecrire_eps_bezier2(Image I, Liste_Contours courbes, const char* nom_fichier_eps, int mode);

void ecrire_eps_bezier3(Image I, Liste_Contours courbes, const char* nom_fichier_eps, int mode);
#endif