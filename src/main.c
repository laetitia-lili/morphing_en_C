#include <stdio.h>
#include<stdlib.h>
#include "../include/image.h"

//prototype de la fonction d'affichage (définie dans affichage.c)
void afficher_deux_images(Image *img1, Image *img2);

int main (int argc, char *argv[]){
    // vérifier les arguments 
    if (argc != 3) {
        printf("Usage: %s image1.ppm image2.ppm\n", argv[0]);
        printf("Exemple: %s images_ppm/chat_chien_1.ppm images_ppm/chat_chien_2.ppm\n", argv[0]);
        return 1;
    }
    printf("=== Projet Morphing - Test Partie 1 et 2 === \n\n");

    // charger la première image 
     printf("Chargement de l'image 1 %s\n",argv[1]);
     Image *img1 = lire_ppm(argv[1]);
     if (!img1){
         fprintf(stderr,"Erreur : impossible de charger l'image 1\n");
         return 1;
     }

   // charger la deuxième image 
     printf("Chargement de l'image 2 %s\n",argv[2]);
     Image *img2 = lire_ppm(argv[2]);
     if (!img2){
         fprintf(stderr,"Erreur : impossible de charger l'image 2\n");
         liberer_image(img1);
         return 1;
     }
     printf("\n== Affichage des images ==\n");

     // affichager les deux côte à côte 
     afficher_deux_images(img1,img2);

     // libérer la mémoire 
     printf("\nLibération de la mémoire ..\n");
     liberer_image(img1);
     liberer_image(img2);

     printf("Programme terminé avce succès !\n");
     return 0;
}