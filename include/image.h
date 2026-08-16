#ifndef IMAGE_H
#define IMAGE_H

// structure pour représenter un point en 2D
typedef struct  {
    int x;
    int y ;
}Point;

// structure pour représenter un pixel RGB 
typedef struct {
    unsigned char r ; // pour le Rouge (0-255)
    unsigned char g ; // pour le vert  (0-255)
    unsigned char b ; // pour le bleu 0-255)
}Pixel ;
 
// structure pour représenter une image 
typedef struct  {
    int largeur ;
    int hauteur ;
    int max_couleur ;
    Pixel **pixels; // Matrice de pixels 
}Image;

// structure pour stocker les couples de points entre deux images 
typedef struct {
    Point *points_depart ; //points dans l'image de départ
    Point *points_arrivee ;// points dans l'image d'arrivée
    int nb_points ; // nombre de couples de points 
    int capacite ; // capacité du tableau ( pour allocation dynamique )
}CouplesPoints;

//structure pour représenter un triangle
typedef struct {
    int p1, p2, p3;  //indices des 3 points de base
} Triangle;

//structure pour une image avec triangulation
typedef struct {
    Image *image;              //l'image elle-même
    Point *points_base;        //points de base de cette image
    int nb_points;             //nombre de points
    Triangle *triangles;       //triangulation
    int nb_triangles;          //nombre de triangles
} ImageTriangulee;


// prototype des fonctions 
//=============== partie 1 et 2 =================//
Image* creer_image(int largeur , int hauteur );
void liberer_image(Image *img);
Image* lire_ppm (const char *nom_fichier);
int ecrire_ppm(const char *nom_fichier,Image *img);

//=============== partie 3 =================//
CouplesPoints* creer_couples_points(int capacite_initiale);
void ajouter_couple(CouplesPoints *cp,Point p_depart,Point p_arrivee);
void liberer_couples_points(CouplesPoints *cp);
int sauvegarder_couples ( const char *nom_fichier,CouplesPoints *cp,int largeur ,int hauteur);
CouplesPoints* charger_couples(const char *nom_fichier);

//=============partie 4 =================//
ImageTriangulee* creer_image_triangulee(int largeur, int hauteur, int nb_points);
void liberer_image_triangulee(ImageTriangulee *it);
Point* calculer_points_intermediaires(CouplesPoints *cp, double alpha);
void trianguler_image(ImageTriangulee *it);
#endif





