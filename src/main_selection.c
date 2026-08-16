#include <stdio.h>
#include <stdlib.h>
#include "../include/image.h"

// prototype de la fonction d'interface
CouplesPoints* interface_selection_points(Image *img1, Image *img2);

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s image1.ppm image2.ppm fichier_points.txt\n", argv[0]);
        printf("Exemple: %s images_ppm/petit1.ppm images_ppm/petit2.ppm data/points.txt\n", argv[0]);
        return 1;
    }
    
    const char *nom_img1 = argv[1];
    const char *nom_img2 = argv[2];
    const char *nom_fichier_points = argv[3];
    
    printf("=== Sélection des points de base ===\n\n");
    
    //charger les images
    printf("Chargement de l'image 1: %s\n", nom_img1);
    Image *img1 = lire_ppm(nom_img1);
    if (!img1) {
        fprintf(stderr, "Erreur: impossible de charger l'image 1\n");
        return 1;
    }
    
    printf("Chargement de l'image 2: %s\n", nom_img2);
    Image *img2 = lire_ppm(nom_img2);
    if (!img2) {
        fprintf(stderr, "Erreur: impossible de charger l'image 2\n");
        liberer_image(img1);
        return 1;
    }
    
    //lancer l'interface de sélection
    CouplesPoints *cp = interface_selection_points(img1, img2);
    
    if (cp && cp->nb_points > 0) {
        //sauvegarder les points
        if (sauvegarder_couples(nom_fichier_points, cp, img1->largeur, img1->hauteur)) {
            printf("\n✓ Points sauvegardés dans: %s\n", nom_fichier_points);
        }
        
        liberer_couples_points(cp);
    } else {
        printf("\nAucun point sélectionné.\n");
    }
    
    //libérer la mémoire
    liberer_image(img1);
    liberer_image(img2);
    
    printf("\nProgramme terminé.\n");
    return 0;
}