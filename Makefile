#############################################################################
# Fichier Makefile 
# UE MAP401 - DLST - UGA - 2024/2025
#############################################################################

#############################################################################
# definition des variables locales
#############################################################################

# compilateur C
CC = clang

# chemin d'acces aux librairies (interfaces)
INCDIR = .

# chemin d'acces aux librairies (binaires)
LIBDIR = .

# options pour l'édition des liens
LDOPTS = -L$(LIBDIR) -lm

# options pour la recherche des fichiers .o et .h
INCLUDEOPTS = -I$(INCDIR)

# options de compilation
COMPILOPTS = -g -Wall $(INCLUDEOPTS)

# liste des executables
EXECUTABLES = test_image test_geometrie test_calcul_contour test_simplification_contours


#############################################################################
# definition des regles
#############################################################################

########################################################
# la règle par défaut
all : $(EXECUTABLES)

########################################################
# regle generique : 
#  remplace les regles de compilation separee de la forme
#	module.o : module.c module.h
#		$(CC) -c $(COMPILOPTS) module.c
%.o : %.c %.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

########################################################
# regles explicites de compilation separee de modules
# n'ayant pas de fichier .h ET/OU dependant d'autres modules
image.o : image.c image.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_image.o : test_image.c image.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

geometrie2d.o : geometrie2d.c geometrie2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module geometrie2d"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_geometrie.o : test_geometrie.c geometrie2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_geometrie"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

sequence_point.o : sequence_point.c sequence_point.h
	$(CC) -c $(COMPILOPTS) $<
	
calcul_contour.o : calcul_contour.c calcul_contour.h image.h sequence_point.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module calcul_contour"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

generer_eps.o : generer_eps.c calcul_contour.h image.h generer_eps.h geometrie2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module generer_eps"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

simplification_contours.o : simplification_contours.c simplification_contours.h geometrie2d.h calcul_contour.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module simplification_contours"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_calcul_contour.o: test_calcul_contour.c calcul_contour.h image.h generer_eps.h geometrie2d.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_calcul_contour"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_simplification_contours.o: test_simplification_contours.c calcul_contour.h image.h sequence_point.h simplification_contours.h geometrie2d.h generer_eps.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_simplification_contoursB2"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<


########################################################
# regles explicites de creation des executables

test_image : test_image.o image.o 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_geometrie : test_geometrie.o geometrie2d.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_calcul_contour : test_calcul_contour.o calcul_contour.o image.o sequence_point.o generer_eps.o geometrie2d.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

test_simplification_contours: test_simplification_contours.o simplification_contours.o calcul_contour.o image.o sequence_point.o geometrie2d.o generer_eps.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@


# regle pour "nettoyer" le répertoire
clean:
	rm -fR $(EXECUTABLES) *.o