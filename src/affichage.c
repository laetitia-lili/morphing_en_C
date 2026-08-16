#include <stdio.h>
#include "../include/image.h"
#include "../IN304_Projet/uvsqgraphics_2.h"

// convertir RGB en COULEUR
COULEUR rgb_vers_couleur(unsigned char r, unsigned char g, unsigned char b) {
    return (r << 16) | (g << 8) | b;
}

// affiche une image à une position donnée dans la fenêtre
void afficher_image_pos(Image *img, int offset_x, int offset_y) {
    if (!img) {
        fprintf(stderr, "Erreur: image NULL\n");
        return;
    }
    
    // on parcourt tous les pixels de l'image et on les dessine un par un
    for (int y = 0; y < img->hauteur; y++) {
        for (int x = 0; x < img->largeur; x++) {
            Pixel p = img->pixels[y][x];
            COULEUR c = rgb_vers_couleur(p.r, p.g, p.b);
            POINT pt = {offset_x + x, offset_y + y};
            draw_pixel(pt, c);
        }
    }
}

// affiche deux images côte à côte dans une fenêtre
void afficher_deux_images(Image *img1, Image *img2) {
    if (!img1 || !img2) {
        fprintf(stderr, "Erreur : une ou plusieurs images sont NULL\n");
        return;
    }
    
    // calculer la taille de la fenêtre
    int largeur_fenetre = img1->largeur + img2->largeur + 60;
    int hauteur_fenetre = (img1->hauteur > img2->hauteur ? img1->hauteur : img2->hauteur) + 60;
    
    // initialiser la fenêtre graphique
    init_graphics(largeur_fenetre, hauteur_fenetre);
    
    // remplir l'écran en blanc
    fill_screen(blanc);
    
    // afficher l'image de gauche
    printf("Affichage image 1...\n");
    afficher_image_pos(img1, 20, 20);
    
    // afficher l'image de droite
    printf("Affichage image 2...\n");
    afficher_image_pos(img2, img1->largeur + 40, 20);
    
    // rafraîchir l'affichage
    affiche_all();
    
    printf("Appuyez sur Échap pour fermer...\n");
    
    // attendre Échap
    wait_escape();
}
