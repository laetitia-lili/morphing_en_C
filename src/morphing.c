#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/image.h"

// calculer les points intermédiaires
Point* calculer_points_intermediaires(CouplesPoints *couples, double alpha) {
    Point *points_inter = (Point*)malloc(couples->nb_points * sizeof(Point));
    if (!points_inter) {
        fprintf(stderr, "Erreur d'allocation mémoire pour points intermédiaires\n");
        return NULL;
    }
    
    for (int i = 0; i < couples->nb_points; i++) {
        points_inter[i].x = (int)((1.0 - alpha) * couples->points_depart[i].x + 
                                   alpha * couples->points_arrivee[i].x);
        points_inter[i].y = (int)((1.0 - alpha) * couples->points_depart[i].y + 
                                   alpha * couples->points_arrivee[i].y);
    }
    
    return points_inter;
}

// tester si un point est dans un triangle
int point_dans_triangle(Point p, Point a, Point b, Point c) {
    double epsilon = 0.01;  // Tolérance augmentée pour capturer les pixels de bord
    
    // calcul des vecteurs
    double v0x = c.x - a.x;
    double v0y = c.y - a.y;
    double v1x = b.x - a.x;
    double v1y = b.y - a.y;
    double v2x = p.x - a.x;
    double v2y = p.y - a.y;
    
    // calcul des produits scalaires
    double dot00 = v0x * v0x + v0y * v0y;
    double dot01 = v0x * v1x + v0y * v1y;
    double dot02 = v0x * v2x + v0y * v2y;
    double dot11 = v1x * v1x + v1y * v1y;
    double dot12 = v1x * v2x + v1y * v2y;
    
    // calcul des coordonnées barycentriques
    double inv_denom = 1.0 / (dot00 * dot11 - dot01 * dot01);
    double u = (dot11 * dot02 - dot01 * dot12) * inv_denom;
    double v = (dot00 * dot12 - dot01 * dot02) * inv_denom;
    
    // test avec tolérance
    return (u >= -epsilon) && (v >= -epsilon) && (u + v <= 1.0 + epsilon);
}

// trianguler une image
void trianguler_image(ImageTriangulee *img_tri) {
    if (img_tri->nb_points < 5) {
        fprintf(stderr, "Erreur: il faut au moins 5 points pour la triangulation\n");
        return;
    }
    
    // allocation initiale des triangles
    int capacite_triangles = 2 * img_tri->nb_points;
    img_tri->triangles = (Triangle*)malloc(capacite_triangles * sizeof(Triangle));
    if (!img_tri->triangles) {
        fprintf(stderr, "Erreur d'allocation mémoire pour triangles\n");
        return;
    }
    img_tri->nb_triangles = 0;
    
    // créer les 4 premiers triangles avec le point 4 (indice 4)
    img_tri->triangles[0].p1 = 0;
    img_tri->triangles[0].p2 = 1;
    img_tri->triangles[0].p3 = 4;
    
    img_tri->triangles[1].p1 = 1;
    img_tri->triangles[1].p2 = 3;
    img_tri->triangles[1].p3 = 4;
    
    img_tri->triangles[2].p1 = 3;
    img_tri->triangles[2].p2 = 2;
    img_tri->triangles[2].p3 = 4;
    
    img_tri->triangles[3].p1 = 2;
    img_tri->triangles[3].p2 = 0;
    img_tri->triangles[3].p3 = 4;
    
    img_tri->nb_triangles = 4;
    
    // pour chaque point suivant
    for (int p = 5; p < img_tri->nb_points; p++) {
        Point nouveau_point = img_tri->points_base[p];
        int triangle_trouve = -1;
        
        // trouver le triangle qui contient ce point
        for (int t = 0; t < img_tri->nb_triangles; t++) {
            Point a = img_tri->points_base[img_tri->triangles[t].p1];
            Point b = img_tri->points_base[img_tri->triangles[t].p2];
            Point c = img_tri->points_base[img_tri->triangles[t].p3];
            
            if (point_dans_triangle(nouveau_point, a, b, c)) {
                triangle_trouve = t;
                break;
            }
        }
        
        if (triangle_trouve == -1) {
            fprintf(stderr, "Attention: point %d non trouvé dans un triangle\n", p);
            continue;
        }
        
        // sauvegarder les indices
        int p1 = img_tri->triangles[triangle_trouve].p1;
        int p2 = img_tri->triangles[triangle_trouve].p2;
        int p3 = img_tri->triangles[triangle_trouve].p3;
        
        // vérifier capacité
        if (img_tri->nb_triangles + 2 >= capacite_triangles) {
            capacite_triangles *= 2;
            Triangle *nouveaux = (Triangle*)realloc(img_tri->triangles, 
                                                    capacite_triangles * sizeof(Triangle));
            if (!nouveaux) {
                fprintf(stderr, "Erreur de réallocation\n");
                return;
            }
            img_tri->triangles = nouveaux;
        }
        
        // remplacer + ajouter
        img_tri->triangles[triangle_trouve].p1 = p1;
        img_tri->triangles[triangle_trouve].p2 = p2;
        img_tri->triangles[triangle_trouve].p3 = p;
        
        img_tri->triangles[img_tri->nb_triangles].p1 = p2;
        img_tri->triangles[img_tri->nb_triangles].p2 = p3;
        img_tri->triangles[img_tri->nb_triangles].p3 = p;
        img_tri->nb_triangles++;
        
        img_tri->triangles[img_tri->nb_triangles].p1 = p3;
        img_tri->triangles[img_tri->nb_triangles].p2 = p1;
        img_tri->triangles[img_tri->nb_triangles].p3 = p;
        img_tri->nb_triangles++;
    }
    
    printf("Triangulation: %d triangles (attendu: %d)\n", 
           img_tri->nb_triangles, 2 * img_tri->nb_points - 6);
}

// calculer les coordonnées barycentriques
void calculer_coordonnees_barycentriques(Point p, Point a, Point b, Point c, 
                                         double *lambda, double *mu) {
    double AB_x = b.x - a.x;
    double AB_y = b.y - a.y;
    double AC_x = c.x - a.x;
    double AC_y = c.y - a.y;
    double AP_x = p.x - a.x;
    double AP_y = p.y - a.y;
    
    double det = AB_x * AC_y - AB_y * AC_x;
    
    if (fabs(det) < 0.0001) {
        *lambda = 0.0;
        *mu = 0.0;
        return;
    }
    
    *lambda = (AP_x * AC_y - AP_y * AC_x) / det;
    *mu = (AB_x * AP_y - AB_y * AP_x) / det;
}

// interpoler un pixel
void interpoler_pixel(ImageTriangulee *img_tri, Image *img_dep, Image *img_arr, 
                      Image *img_inter, int x, int y, double alpha, 
                      CouplesPoints *couples) {
    Point p = {x, y};
    
    // chercher triangle
    for (int t = 0; t < img_tri->nb_triangles; t++) {
        Point a = img_tri->points_base[img_tri->triangles[t].p1];
        Point b = img_tri->points_base[img_tri->triangles[t].p2];
        Point c = img_tri->points_base[img_tri->triangles[t].p3];
        
        if (point_dans_triangle(p, a, b, c)) {
            double lambda, mu;
            calculer_coordonnees_barycentriques(p, a, b, c, &lambda, &mu);
            
            int idx_a = img_tri->triangles[t].p1;
            int idx_b = img_tri->triangles[t].p2;
            int idx_c = img_tri->triangles[t].p3;
            
            Point a_dep = couples->points_depart[idx_a];
            Point b_dep = couples->points_depart[idx_b];
            Point c_dep = couples->points_depart[idx_c];
            
            double PDx = a_dep.x + lambda * (b_dep.x - a_dep.x) + mu * (c_dep.x - a_dep.x);
            double PDy = a_dep.y + lambda * (b_dep.y - a_dep.y) + mu * (c_dep.y - a_dep.y);
            
            Point a_arr = couples->points_arrivee[idx_a];
            Point b_arr = couples->points_arrivee[idx_b];
            Point c_arr = couples->points_arrivee[idx_c];
            
            double PAx = a_arr.x + lambda * (b_arr.x - a_arr.x) + mu * (c_arr.x - a_arr.x);
            double PAy = a_arr.y + lambda * (b_arr.y - a_arr.y) + mu * (c_arr.y - a_arr.y);
            
            // clamping
            int PDx_int = (int)PDx;
            int PDy_int = (int)PDy;
            int PAx_int = (int)PAx;
            int PAy_int = (int)PAy;
            
            if (PDx_int < 0) PDx_int = 0;
            if (PDy_int < 0) PDy_int = 0;
            if (PDx_int >= img_dep->largeur) PDx_int = img_dep->largeur - 1;
            if (PDy_int >= img_dep->hauteur) PDy_int = img_dep->hauteur - 1;
            
            if (PAx_int < 0) PAx_int = 0;
            if (PAy_int < 0) PAy_int = 0;
            if (PAx_int >= img_arr->largeur) PAx_int = img_arr->largeur - 1;
            if (PAy_int >= img_arr->hauteur) PAy_int = img_arr->hauteur - 1;
            
            Pixel couleur_dep = img_dep->pixels[PDy_int][PDx_int];
            Pixel couleur_arr = img_arr->pixels[PAy_int][PAx_int];
            
            img_inter->pixels[y][x].r = (unsigned char)((1.0 - alpha) * couleur_dep.r + alpha * couleur_arr.r);
            img_inter->pixels[y][x].g = (unsigned char)((1.0 - alpha) * couleur_dep.g + alpha * couleur_arr.g);
            img_inter->pixels[y][x].b = (unsigned char)((1.0 - alpha) * couleur_dep.b + alpha * couleur_arr.b);
            
            return;
        }
    }
    
    // pixel non trouvé - interpolation directe
    int x_clamp = (x < 0) ? 0 : (x >= img_dep->largeur) ? img_dep->largeur - 1 : x;
    int y_clamp = (y < 0) ? 0 : (y >= img_dep->hauteur) ? img_dep->hauteur - 1 : y;
    
    Pixel p_dep = img_dep->pixels[y_clamp][x_clamp];
    Pixel p_arr = img_arr->pixels[y_clamp][x_clamp];
    
    img_inter->pixels[y][x].r = (unsigned char)((1.0 - alpha) * p_dep.r + alpha * p_arr.r);
    img_inter->pixels[y][x].g = (unsigned char)((1.0 - alpha) * p_dep.g + alpha * p_arr.g);
    img_inter->pixels[y][x].b = (unsigned char)((1.0 - alpha) * p_dep.b + alpha * p_arr.b);
}
// créer une image triangulée
ImageTriangulee* creer_image_triangulee(int largeur, int hauteur, int nb_points) {
    ImageTriangulee *img_tri = (ImageTriangulee*)malloc(sizeof(ImageTriangulee));
    if (!img_tri) {
        fprintf(stderr, "Erreur allocation ImageTriangulee\n");
        return NULL;
    }
    
    img_tri->image = creer_image(largeur, hauteur);
    if (!img_tri->image) {
        free(img_tri);
        return NULL;
    }
    
    img_tri->points_base = (Point*)malloc(nb_points * sizeof(Point));
    if (!img_tri->points_base) {
        liberer_image(img_tri->image);
        free(img_tri);
        return NULL;
    }
    
    img_tri->nb_points = nb_points;
    img_tri->triangles = NULL;
    img_tri->nb_triangles = 0;
    
    return img_tri;
}

// libérer une image triangulée
void liberer_image_triangulee(ImageTriangulee *img_tri) {
    if (img_tri) {
        if (img_tri->image) {
            liberer_image(img_tri->image);
        }
        if (img_tri->points_base) {
            free(img_tri->points_base);
        }
        if (img_tri->triangles) {
            free(img_tri->triangles);
        }
        free(img_tri);
    }
}
