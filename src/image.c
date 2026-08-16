#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../include/image.h"

//================ parties 1 et 2 =======================//
// fonction qui crée une image vide avec allocation dynamique 
Image* creer_image(int largeur,int hauteur){

    //allouer la structure image
    Image *img = (Image*)malloc(sizeof(Image));
    if (!img){
        fprintf(stderr,"Erreur : allocation Image échoué\n");
        return NULL ;
    };

    // initialiser les champs 
    img ->largeur = largeur ;
    img ->hauteur = hauteur;
    img ->max_couleur = 255 ;

    // allouer le tableau de pointeurs ( les lignes )
    img ->pixels = (Pixel**)malloc (hauteur * sizeof(Pixel*));
    if (!img->pixels){
        fprintf(stderr,"Erreur : allocation lignee échoué \n");
        free (img);
        return NULL;
    }

    // alouer chaque ligne ( les colonnes)
    for (int i=0 ; i < hauteur ; i++ ){
        img -> pixels[i] = (Pixel*)malloc(largeur *sizeof(Pixel));
        if (!img->pixels[i]){
            fprintf(stderr,"Erreur allocation ligne %d échouée\n",i);
            // libérer ce qui a déja été alloué 
            for (int j = 0 ;j < i ; j++){
                free (img -> pixels[j]);
            }
            free (img->pixels);
            free (img);
            return NULL;
        }
    }
    return img;
}

//fonction qui libère toute la mémoire allouée à une image 
void liberer_image(Image *img){
    if (!img)return;

    //libérer chaque ligne 
    if (img -> pixels){
        for (int i = 0 ; i < img ->hauteur; i ++){
            free (img ->pixels[i]);
        }
        free (img ->pixels ); 
    }
    //libérer la structure 
    free (img);
}

// fonction qui ignore les lignes de commentaire dans les fichiers PPM
void ignorer_commentaires (FILE *f){
    int c ;
    while ((c=fgetc(f))=='#'){
        //lire jusqu'à la fin du fichier 
        while ((c=fgetc(f)) != '\n' && c != EOF);
    }
    // Remettre le dernier caractère lu 
    ungetc (c , f);
}

// fonction qui lit un fichier PPM (format P3 ou P6)
Image* lire_ppm(const char *nom_fichier) {
    FILE *f = fopen(nom_fichier, "rb");
    if (!f) {
        fprintf(stderr, "Erreur: impossible d'ouvrir %s\n", nom_fichier);
        return NULL;
    }
    
    // Lire le magic number
    char magic[3];
    if (!fgets(magic, sizeof(magic), f)) {
        fprintf(stderr, "Erreur: fichier vide\n");
        fclose(f);
        return NULL;
    }
    
    // Vérifier P3 ou P6
    int format_binaire = 0;
    if (magic[0] == 'P' && magic[1] == '6') {
        format_binaire = 1;
    } else if (magic[0] == 'P' && magic[1] == '3') {
        format_binaire = 0;
    } else {
        fprintf(stderr, "Erreur: format non supporté (attendu P3 ou P6)\n");
        fclose(f);
        return NULL;
    }
    
    ignorer_commentaires(f);
    
    int largeur, hauteur;
    if (fscanf(f, "%d %d", &largeur, &hauteur) != 2) {
        fprintf(stderr, "Erreur: dimensions invalides\n");
        fclose(f);
        return NULL;
    }
    
    ignorer_commentaires(f);
    
    int max_couleur;
    if (fscanf(f, "%d", &max_couleur) != 1) {
        fprintf(stderr, "Erreur: max_couleur invalide\n");
        fclose(f);
        return NULL;
    }
    
    fgetc(f); // Consommer le dernier newline
    
    Image *img = creer_image(largeur, hauteur);
    if (!img) {
        fclose(f);
        return NULL;
    }
    img->max_couleur = max_couleur;
    
    // Lire les pixels selon le format
    if (format_binaire) {
        // Format P6 (binaire)
        for (int y = 0; y < hauteur; y++) {
            for (int x = 0; x < largeur; x++) {
                unsigned char rgb[3];
                if (fread(rgb, 1, 3, f) != 3) {
                    fprintf(stderr, "Erreur: lecture pixels incomplète\n");
                    liberer_image(img);
                    fclose(f);
                    return NULL;
                }
                img->pixels[y][x].r = rgb[0];
                img->pixels[y][x].g = rgb[1];
                img->pixels[y][x].b = rgb[2];
            }
        }
    } else {
        // Format P3 (texte)
        for (int y = 0; y < hauteur; y++) {
            for (int x = 0; x < largeur; x++) {
                int r, g, b;
                if (fscanf(f, "%d %d %d", &r, &g, &b) != 3) {
                    fprintf(stderr, "Erreur: lecture pixels incomplète\n");
                    liberer_image(img);
                    fclose(f);
                    return NULL;
                }
                img->pixels[y][x].r = (unsigned char)r;
                img->pixels[y][x].g = (unsigned char)g;
                img->pixels[y][x].b = (unsigned char)b;
            }
        }
    }
    
    fclose(f);
    printf("✓ Image chargée : %s (%dx%d pixels, format P%c)\n", 
           nom_fichier, largeur, hauteur, format_binaire ? '6' : '3');
    return img;
}

// fonction qui sauvegarde une image au format PPM P6
int ecrire_ppm(const char *nom_fichier , Image *img){
    if (!img) {
        fprintf(stderr, "Erreur: image NULL\n");
        return 0;
    }
    
    // Ouvrir le fichier en mode binaire écriture
    FILE *f = fopen(nom_fichier, "wb");
    if (!f) {
        fprintf(stderr, "Erreur: impossible de créer %s\n", nom_fichier);
        return 0;
    }
    
    // Écrire l'en-tête P6
    fprintf(f, "P6\n%d %d\n%d\n", img->largeur, img->hauteur, img->max_couleur);
    
    // Écrire les pixels en binaire
    for (int y = 0; y < img->hauteur; y++) {
        for (int x = 0; x < img->largeur; x++) {
            unsigned char rgb[3] = {
                img->pixels[y][x].r,
                img->pixels[y][x].g,
                img->pixels[y][x].b
            };
            fwrite(rgb, 1, 3, f);
        }
    }
    
    fclose(f);
    printf("✓ Image sauvegardée : %s\n", nom_fichier);
    return 1;
}

//=============== partie 3  =================//

// fonction qui une structure pour stocker les couples de points 
CouplesPoints* creer_couples_points(int capacite_initiale) {
    CouplesPoints *cp = (CouplesPoints*)malloc(sizeof(CouplesPoints));
    if (!cp) {
        fprintf(stderr, "Erreur: allocation CouplesPoints échouée\n");
        return NULL;
    }
    
    cp->nb_points = 0;
    cp->capacite = capacite_initiale;
    
    cp->points_depart = (Point*)malloc(capacite_initiale * sizeof(Point));
    cp->points_arrivee = (Point*)malloc(capacite_initiale * sizeof(Point));
    
    if (!cp->points_depart || !cp->points_arrivee) {
        fprintf(stderr, "Erreur: allocation tableaux de points échouée\n");
        free(cp->points_depart);
        free(cp->points_arrivee);
        free(cp);
        return NULL;
    }
    return cp;
}

//fonction qui ajoute un couple de points correspondants
void ajouter_couple(CouplesPoints *cp, Point p_depart, Point p_arrivee) {
    if (!cp) return;
    
    // agrandir le tableau si nécessaire
    if (cp->nb_points >= cp->capacite) {
        int nouvelle_capacite = cp->capacite * 2;
        Point *nouveaux_depart = (Point*)realloc(cp->points_depart, nouvelle_capacite * sizeof(Point));
        Point *nouveaux_arrivee = (Point*)realloc(cp->points_arrivee, nouvelle_capacite * sizeof(Point));
        
        if (!nouveaux_depart || !nouveaux_arrivee) {
            fprintf(stderr, "Erreur: réallocation échouée\n");
            return;
        }
        
        cp->points_depart = nouveaux_depart;
        cp->points_arrivee = nouveaux_arrivee;
        cp->capacite = nouvelle_capacite;
    }
    
    cp->points_depart[cp->nb_points] = p_depart;
    cp->points_arrivee[cp->nb_points] = p_arrivee;
    cp->nb_points++;

}

// fonction qui libère la mémoire des couples de points
void liberer_couples_points(CouplesPoints *cp) {
    if (!cp) return;
    
    free(cp->points_depart);
    free(cp->points_arrivee);
    free(cp);
}

// fonction qui sauvegarde les couples de points dans un fichier 
// format : nb_points largeur hauteur 
//          x1_depart y1_depart x1_arrivee y1_arrivee
//.         x2_depart y2_depart x2_arrivee y2_arrivee

int sauvegarder_couples (const char *nom_fichier, CouplesPoints *cp, int largeur, int hauteur) {
    if (!cp) return 0;
    
    FILE *f = fopen(nom_fichier, "w");
    if (!f) {
        fprintf(stderr, "Erreur: impossible de créer %s\n", nom_fichier);
        return 0;
    }
    
    // écrire le nombre de points et les dimensions
    fprintf(f, "%d %d %d\n", cp->nb_points + 4, largeur, hauteur);
    
    // ajouter les 4 coins en premier (automatiquement)
    fprintf(f, "0 0 0 0\n");                                    // Coin haut-gauche
    fprintf(f, "%d 0 %d 0\n", largeur-1, largeur-1);           // Coin haut-droit
    fprintf(f, "0 %d 0 %d\n", hauteur-1, hauteur-1);           // Coin bas-gauche
    fprintf(f, "%d %d %d %d\n", largeur-1, hauteur-1, largeur-1, hauteur-1); // Coin bas-droit
    
    // ecrire les couples de points
    for (int i = 0; i < cp->nb_points; i++) {
        fprintf(f, "%d %d %d %d\n",
                cp->points_depart[i].x, cp->points_depart[i].y,
                cp->points_arrivee[i].x, cp->points_arrivee[i].y);
    }
    fclose(f);
    printf("Couples de points sauvegardés : %s (%d points)\n", nom_fichier, cp->nb_points + 4);
    return 1;
}

//fonction qui charge les couples de points à afficher 

CouplesPoints* charger_couples(const char *nom_fichier) {
    FILE *f = fopen(nom_fichier, "r");
    if (!f) {
        fprintf(stderr, "Erreur: impossible d'ouvrir %s\n", nom_fichier);
        return NULL;
    }
    
    int nb_points, largeur, hauteur;
    if (fscanf(f, "%d %d %d", &nb_points, &largeur, &hauteur) != 3) {
        fprintf(stderr, "Erreur: format de fichier invalide\n");
        fclose(f);
        return NULL;
    }
    
    CouplesPoints *cp = creer_couples_points(nb_points);
    if (!cp) {
        fclose(f);
        return NULL;
    }
    
    // lire tous les couples
    for (int i = 0; i < nb_points; i++) {
        Point p_depart, p_arrivee;
        if (fscanf(f, "%d %d %d %d", &p_depart.x, &p_depart.y, 
                   &p_arrivee.x, &p_arrivee.y) != 4) {
            fprintf(stderr, "Erreur: lecture point %d échouée\n", i);
            liberer_couples_points(cp);
            fclose(f);
            return NULL;
        }
        
        ajouter_couple(cp, p_depart, p_arrivee);
    }
    
    fclose(f);
    printf("✓ Couples de points chargés : %s (%d points)\n", nom_fichier, nb_points);
    return cp;

}
