#include <stdio.h>
#include <stdlib.h>
#include "../include/image.h"

// prototypes des fonctions externes
CouplesPoints* interface_selection_points(Image *img1, Image *img2);
Pixel interpoler_pixel(Point P, ImageTriangulee *img_inter, 
                      CouplesPoints *cp, Image *img_depart, 
                      Image *img_arrivee, double alpha);

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s Image_Depart Image_Arrivee N\n", argv[0]);
        printf("Exemple: %s images_ppm/chat.ppm images_ppm/chien.ppm 30\n", argv[0]);
        printf("\nCe programme va :\n");
        printf("1. Afficher une interface pour sélectionner les points\n");
        printf("2. Générer N+1 images intermédiaires\n");
        printf("3. Créer une vidéo morphing.mp4 de ~10 secondes\n");
        return 1;
    }
    
    const char *image_depart = argv[1];
    const char *image_arrivee = argv[2];
    int N = atoi(argv[3]);
    
    if (N < 1 || N > 200) {
        fprintf(stderr, "Erreur: N doit être entre 1 et 200\n");
        return 1;
    }
    
    printf("=== MORPHING : %s -> %s (%d images) ===\n\n", 
           image_depart, image_arrivee, N+1);
    
    // étape 1 : Charger les images
    printf("Étape 1/5 : Chargement des images...\n");
    Image *img1 = lire_ppm(image_depart);
    if (!img1) {
        fprintf(stderr, "Erreur: impossible de charger %s\n", image_depart);
        return 1;
    }
    
    Image *img2 = lire_ppm(image_arrivee);
    if (!img2) {
        fprintf(stderr, "Erreur: impossible de charger %s\n", image_arrivee);
        liberer_image(img1);
        return 1;
    }
    printf("✓ Images chargées\n\n");
    
    // étape 2 : Sélection interactive des points
    printf("Étape 2/5 : Sélection des points de base...\n");
    printf("(Une fenêtre va s'ouvrir - sélectionnez les points puis cliquez sur SAUVER et QUITTER)\n\n");
    
    CouplesPoints *cp = interface_selection_points(img1, img2);
    if (!cp || cp->nb_points < 1) {
        fprintf(stderr, "Erreur: aucun point sélectionné\n");
        liberer_image(img1);
        liberer_image(img2);
        return 1;
    }
    
    // sauvegarder les points
    sauvegarder_couples("data/points_morphing.txt", cp, img1->largeur, img1->hauteur);
    printf("✓ %d couples de points sélectionnés\n\n", cp->nb_points);
    
    // étape 3 : Générer les images intermédiaires
    printf("Étape 3/5 : Génération de %d images intermédiaires...\n", N+1);
    
    for (int k = 0; k <= N; k++) {
        double alpha = (double)k / (double)N;
        
        if (k % 10 == 0 || k == N) {
            printf("  Image %d/%d (alpha=%.2f)...\n", k, N, alpha);
        }
        
        // calculer points intermédiaires
        Point *points_inter = calculer_points_intermediaires(cp, alpha);
        if (!points_inter) continue;
        
        // créer image intermédiaire
        ImageTriangulee *img_inter = creer_image_triangulee(
            img1->largeur, img1->hauteur, cp->nb_points);
        if (!img_inter) {
            free(points_inter);
            continue;
        }
        
        // copier les points
        for (int i = 0; i < cp->nb_points; i++) {
            img_inter->points_base[i] = points_inter[i];
        }
        free(points_inter);
        
        // trianguler
        trianguler_image(img_inter);
        
        // calculer les couleurs
        for (int y = 0; y < img1->hauteur; y++) {
            for (int x = 0; x < img1->largeur; x++) {
                Point P = {x, y};
                img_inter->image->pixels[y][x] = 
                    interpoler_pixel(P, img_inter, cp, img1, img2, alpha);
            }
        }
        
        // sauvegarder
        char nom_sortie[256];
        snprintf(nom_sortie, sizeof(nom_sortie), 
                 "images_out/morphing_%03d.ppm", k);
        ecrire_ppm(nom_sortie, img_inter->image);
        
        liberer_image_triangulee(img_inter);
    }
    printf("✓ %d images générées dans images_out/\n\n", N+1);
    
    // étape 4 : Créer la vidéo
    printf("Étape 4/5 : Création de la vidéo...\n");
    
    // calculer le FPS pour obtenir ~10 secondes
    int fps = (N + 1) / 10;
    if (fps < 5) fps = 5;
    if (fps > 30) fps = 30;
    
    char commande_ffmpeg[512];
    snprintf(commande_ffmpeg, sizeof(commande_ffmpeg),"ffmpeg -y -framerate %d -i images_out/morphing_%%03d.ppm ""-vf \"scale=trunc(iw/2)*2:trunc(ih/2)*2\" " "-c:v libx264 -pix_fmt yuv420p -crf 23 ""morphing.mp4 > /dev/null 2>&1", fps);
    
    int resultat = system(commande_ffmpeg);
    
    if (resultat == 0) {
        printf("✓ Vidéo créée : morphing.mp4 (~10 secondes à %d FPS)\n\n", fps);
    } else {
        fprintf(stderr, "✗ Erreur lors de la création de la vidéo\n\n");
    }
    
    // étape 5 : Nettoyage
    printf("Étape 5/5 : Nettoyage...\n");
    liberer_couples_points(cp);
    liberer_image(img1);
    liberer_image(img2);
    printf("✓ Terminé\n\n");
    
    printf("========================================\n");
    printf("MORPHING TERMINÉ !\n");
    printf("Fichier vidéo : morphing.mp4\n");
    printf("Pour lire : open morphing.mp4\n");
    printf("========================================\n");
    
    return 0;
}
