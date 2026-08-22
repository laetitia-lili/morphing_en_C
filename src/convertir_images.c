#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

//fonction pour vérifier si un fichier existe
int fichier_existe(const char *chemin) {
    struct stat buffer;
    return (stat(chemin, &buffer) == 0);
}

//fonction pour convertir une image avec ImageMagick
int convertir_image(const char *entree, const char *sortie, int largeur, int hauteur) {
    char commande[512];
    
    //créer la commande ImageMagick
    snprintf(commande, sizeof(commande),
             "magick \"%s\" -resize %dx%d -compress None \"%s\"",
             entree, largeur, hauteur, sortie);
    
    printf("Conversion : %s → %s (%dx%d)\n", entree, sortie, largeur, hauteur);
    
    //exécuter la commande
    int resultat = system(commande);
    
    if (resultat == 0) {
        printf("✓ Conversion réussie\n");
        return 1;
    } else {
        fprintf(stderr, "✗ Erreur lors de la conversion\n");
        return 0;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s image_entree.jpg image_sortie.ppm taille\n", argv[0]);
        printf("Exemple: %s images_origine/chat.jpg images_ppm/chat.ppm 200\n", argv[0]);
        return 1;
    }
    
    const char *entree = argv[1];
    const char *sortie = argv[2];
    int taille = atoi(argv[3]);
    
    if (taille < 50 || taille > 1000) {
        fprintf(stderr, "Erreur: la taille doit être entre 50 et 1000\n");
        return 1;
    }
    
    //vérifier que le fichier d'entrée existe
    if (!fichier_existe(entree)) {
        fprintf(stderr, "Erreur: le fichier %s n'existe pas\n", entree);
        return 1;
    }
    
    printf("=== Conversion d'image avec ImageMagick ===\n\n");
    
    //convertir l'image
    if (convertir_image(entree, sortie, taille, taille)) {
        printf("\n✓ Image convertie avec succès !\n");
        return 0;
    } else {
        fprintf(stderr, "\n✗ Échec de la conversion\n");
        return 1;
    }
}