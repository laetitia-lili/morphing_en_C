#include <stdio.h>
#include <stdlib.h>
#include "../include/image.h"

//Prototype de la fonction d'interpolation
Pixel interpoler_pixel(Point P, ImageTriangulee *img_inter,CouplesPoints *cp, Image *img_depart, Image *img_arrivee,double alpha); 
                      

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: %s image1.ppm image2.ppm points.txt N\n", argv[0]);
        printf("Exemple: %s images_ppm/petit1.ppm images_ppm/petit2.ppm data/points.txt 10\n", argv[0]);
        printf("  N = nombre d'images intermédiaires à générer\n");
        return 1;
    }
    
    const char *nom_img1 = argv[1];
    const char *nom_img2 = argv[2];
    const char *nom_fichier_points = argv[3];
    int N = atoi(argv[4]);
    
    if (N < 1 || N > 100) {
        fprintf(stderr, "Erreur: N doit être entre 1 et 100\n");
        return 1;
    }
    
    printf("=== Génération du morphing ===\n\n");
    
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
    
    //charger les couples de points
    printf("Chargement des points: %s\n", nom_fichier_points);
    CouplesPoints *cp = charger_couples(nom_fichier_points);
    if (!cp) {
        fprintf(stderr, "Erreur: impossible de charger les points\n");
        liberer_image(img1);
        liberer_image(img2);
        return 1;
    }
    
    printf("\n=== Génération de %d images intermédiaires ===\n\n", N);
    
    //générer les images intermédiaires
    for (int k = 0; k <= N; k++) {
        double alpha = (double)k / (double)N;
        
        printf("Image %d/%d (alpha=%.2f)...\n", k, N, alpha);
        
        //calculer les points intermédiaires
        Point *points_inter = calculer_points_intermediaires(cp, alpha);
        if (!points_inter) {
            fprintf(stderr, "Erreur: calcul points intermédiaires échoué\n");
            continue;
        }
        
        //créer l'image intermédiaire
        ImageTriangulee *img_inter = creer_image_triangulee(img1->largeur, img1->hauteur, cp->nb_points);
        if (!img_inter) {
            free(points_inter);
            continue;
        }
        
        //copier les points calculés
        for (int i = 0; i < cp->nb_points; i++) {
            img_inter->points_base[i] = points_inter[i];
        }
        free(points_inter);
        
        //trianguler
        trianguler_image(img_inter);
        
        // Calculer la couleur de chaque pixel avec la vraie méthode (section 4.3)
        for (int y = 0; y < img1->hauteur; y++) {
            for (int x = 0; x < img1->largeur; x++) {
                Point P = {x, y};
                img_inter->image->pixels[y][x] = interpoler_pixel(P, img_inter, cp, img1, img2, alpha);
            }
        }
        
        //sauvegarder l'image
        char nom_sortie[256];
        snprintf(nom_sortie, sizeof(nom_sortie), "images_out/morphing_%02d.ppm", k);
        ecrire_ppm(nom_sortie, img_inter->image);
        
        liberer_image_triangulee(img_inter);
    }
    
    printf("\n✓ Morphing terminé ! %d images générées dans images_out/\n", N + 1);
    
    //libérer la mémoire
    liberer_couples_points(cp);
    liberer_image(img1);
    liberer_image(img2);
    
    return 0;
}