#include <stdio.h>
#include <string.h>
#include "../include/image.h"
#include "../IN304_Projet/uvsqgraphics_2.h"

// convertir RGB en COULEUR
COULEUR rgb_vers_couleur(unsigned char r, unsigned char g, unsigned char b) {
    return (r << 16) | (g << 8) | b;
}

// affiche une image à une position donnée
void afficher_image_simple(Image *img, int offset_x, int offset_y) {
    if (!img) return;
    
    for (int y = 0; y < img->hauteur; y++) {
        for (int x = 0; x < img->largeur; x++) {
            Pixel p = img->pixels[y][x];
            COULEUR c = rgb_vers_couleur(p.r, p.g, p.b);
            POINT pt = {offset_x + x, offset_y + y};
            draw_pixel(pt, c);
        }
    }
}

// dessine un cercle avec numéro visible
void dessiner_cercle_point(int x, int y, int numero, COULEUR couleur) {
    POINT centre = {x, y};
    draw_circle(centre, 5, couleur);
    draw_fill_circle(centre, 3, couleur);
    
    // afficher le numéro à côté
    char num_str[10];
    snprintf(num_str, sizeof(num_str), "%d", numero);
    POINT pos_texte = {x + 8, y - 3};
    aff_pol(num_str, 14, pos_texte, noir);
}

// dessiner un bouton avec texte
void dessiner_bouton(int x, int y, int largeur, int hauteur, const char *texte, COULEUR couleur_fond) {
    POINT p1 = {x, y};
    POINT p2 = {x + largeur, y + hauteur};
    draw_fill_rectangle(p1, p2, couleur_fond);
    draw_rectangle(p1, p2, noir);
    
    // afficher le texte centré
    POINT centre = {x + largeur / 2, y + hauteur / 2};
    aff_pol_centre((char*)texte, 20, centre, noir);
}

// vérifier si on a cliqué sur un bouton
int clic_sur_bouton(POINT clic, int btn_x, int btn_y, int btn_largeur, int btn_hauteur) {
    return (clic.x >= btn_x && clic.x <= btn_x + btn_largeur &&
            clic.y >= btn_y && clic.y <= btn_y + btn_hauteur);
}

// interface graphique de sélection des points de base
CouplesPoints* interface_selection_points(Image *img1, Image *img2) {
    if (!img1 || !img2) {
        fprintf(stderr, "Erreur: images NULL\n");
        return NULL;
    }
    
    // créer la structure pour stocker les couples
    CouplesPoints *cp = creer_couples_points(10);
    if (!cp) return NULL;
    
    // calculer les dimensions de la fenêtre
    int marge = 20;
    int zone_milieu_largeur = 200;
    int largeur_fenetre = img1->largeur + zone_milieu_largeur + img2->largeur + 4 * marge;
    int hauteur_max = (img1->hauteur > img2->hauteur ? img1->hauteur : img2->hauteur);
    int zone_boutons = 80;
    int hauteur_fenetre = hauteur_max + 2 * marge + zone_boutons;
    
    // initialiser la fenêtre
    init_graphics(largeur_fenetre, hauteur_fenetre);
    
    // positions des éléments
    int offset_img1_x = marge;
    int offset_img1_y = marge;
    int offset_zone_milieu_x = offset_img1_x + img1->largeur + marge;
    int offset_zone_milieu_y = marge;
    int offset_img2_x = offset_zone_milieu_x + zone_milieu_largeur + marge;
    int offset_img2_y = marge;
    
    // positions des boutons
    int btn_y = hauteur_max + marge + 20;
    int btn_largeur = 100;
    int btn_hauteur = 40;
    int btn_sauver_x = largeur_fenetre / 2 - btn_largeur * 1.5 - 10;
    int btn_supprimer_x = largeur_fenetre / 2 - btn_largeur / 2;
    int btn_quitter_x = largeur_fenetre / 2 + btn_largeur / 2 + 10;
    
    // variables pour la sélection
    int attendre_depart = 1;
    Point dernier_point_depart;
    int sauvegarde_effectuee = 0;
    int mode_suppression = 0;  // 0 = mode normal, 1 = mode suppression
    
    printf("\n=== Sélection des points de base ===\n");
    printf("Instructions:\n");
    printf("1. Cliquez sur l'image de GAUCHE (départ)\n");
    printf("2. Puis cliquez sur l'image de DROITE (arrivée)\n");
    printf("3. Répétez pour chaque couple de points\n");
    printf("4. Cliquez sur le bouton SAUVER pour enregistrer\n");
    printf("5. Cliquez sur le bouton QUITTER pour terminer\n\n");
    
    int continuer = 1;
    while (continuer) {
        // effacer et redessiner
        fill_screen(blanc);
        
        // afficher les deux images
        afficher_image_simple(img1, offset_img1_x, offset_img1_y);
        afficher_image_simple(img2, offset_img2_x, offset_img2_y);
        
        // dessiner la zone du milieu (liste des couples)
        POINT zone_p1 = {offset_zone_milieu_x, offset_zone_milieu_y};
        POINT zone_p2 = {offset_zone_milieu_x + zone_milieu_largeur, offset_zone_milieu_y + hauteur_max};
        draw_rectangle(zone_p1, zone_p2, gris);
        
        // afficher les couples dans la zone du milieu
        int y_liste = offset_zone_milieu_y + 20;
        int espacement_ligne = 25;
        
        for (int i = 0; i < cp->nb_points && i < 15; i++) {
            int y_actuel = y_liste + i * espacement_ligne;
            
            // point de départ (rouge) à gauche
            POINT pt_depart = {offset_zone_milieu_x + 30, y_actuel};
            draw_fill_circle(pt_depart, 6, rouge);
            
            // ligne de liaison
            POINT pt_milieu_gauche = {offset_zone_milieu_x + 40, y_actuel};
            POINT pt_milieu_droit = {offset_zone_milieu_x + zone_milieu_largeur - 40, y_actuel};
            draw_line(pt_milieu_gauche, pt_milieu_droit, gris);
            
            // point d'arrivée (vert) à droite
            POINT pt_arrivee = {offset_zone_milieu_x + zone_milieu_largeur - 30, y_actuel};
            draw_fill_circle(pt_arrivee, 6, vert);
            
            // numéro du couple (approximatif avec des petits carrés)
            for (int n = 0; n < (i + 1) && n < 5; n++) {
                POINT pt_num = {offset_zone_milieu_x + zone_milieu_largeur / 2 - 10 + n * 5, y_actuel - 2};
                draw_fill_rectangle(pt_num, (POINT){pt_num.x + 2, pt_num.y + 4}, noir);
            }
        }
        
        // dessiner les points sur les images
        for (int i = 0; i < cp->nb_points; i++) {
            // point sur image 1 (rouge)
            dessiner_cercle_point(
                offset_img1_x + cp->points_depart[i].x,
                offset_img1_y + cp->points_depart[i].y,
                i + 1,
                rouge
            );
            
            // point sur image 2 (vert)
            dessiner_cercle_point(
                offset_img2_x + cp->points_arrivee[i].x,
                offset_img2_y + cp->points_arrivee[i].y,
                i + 1,
                vert
            );
        }
        
        // point en cours de sélection (jaune)
        if (!attendre_depart) {
            dessiner_cercle_point(
                offset_img1_x + dernier_point_depart.x,
                offset_img1_y + dernier_point_depart.y,
                cp->nb_points + 1,
                jaune
            );
        }
        
        // dessiner les boutons
        dessiner_bouton(btn_sauver_x, btn_y, btn_largeur, btn_hauteur, "SAUVER", 
                       sauvegarde_effectuee ? vert : cyan);
        dessiner_bouton(btn_supprimer_x, btn_y, btn_largeur, btn_hauteur, "SUPPR.", 
                       mode_suppression ? jaune : gris);
        dessiner_bouton(btn_quitter_x, btn_y, btn_largeur, btn_hauteur, "QUITTER", rouge);
        
        affiche_all();
        
        // attendre un événement
        char touche;
        int fleche;
        POINT clic;
        int type_event = wait_key_arrow_clic(&touche, &fleche, &clic);
        
        if (type_event == EST_CLIC) {
            // vérifier si clic sur bouton SAUVER
            if (clic_sur_bouton(clic, btn_sauver_x, btn_y, btn_largeur, btn_hauteur)) {
                printf("\n=== SAUVEGARDE ===\n");
                if (sauvegarder_couples("data/points.txt", cp, img1->largeur, img1->hauteur)) {
                    sauvegarde_effectuee = 1;
                }
            }
            // vérifier si clic sur bouton SUPPRIMER
            else if (clic_sur_bouton(clic, btn_supprimer_x, btn_y, btn_largeur, btn_hauteur)) {
                mode_suppression = !mode_suppression;  // Toggle le mode
                if (mode_suppression) {
                    printf("\n=== MODE SUPPRESSION ACTIVÉ ===\n");
                    printf("Cliquez sur un point pour le supprimer\n");
                } else {
                    printf("\n=== MODE NORMAL ===\n");
                }
            }
            // vérifier si clic sur bouton QUITTER
            else if (clic_sur_bouton(clic, btn_quitter_x, btn_y, btn_largeur, btn_hauteur)) {
                printf("\n=== QUITTER ===\n");
                continuer = 0;
            }
            // si mode suppression activé
            else if (mode_suppression) {
                // chercher si on a cliqué près d'un point existant
                int point_trouve = -1;
                int rayon_detection = 10;
                
                // vérifier les points sur image 1
                for (int i = 0; i < cp->nb_points; i++) {
                    int px = offset_img1_x + cp->points_depart[i].x;
                    int py = offset_img1_y + cp->points_depart[i].y;
                    int dist = (clic.x - px) * (clic.x - px) + (clic.y - py) * (clic.y - py);
                    
                    if (dist < rayon_detection * rayon_detection) {
                        point_trouve = i;
                        break;
                    }
                }
                
                // vérifier les points sur image 2 si pas trouvé sur image 1
                if (point_trouve == -1) {
                    for (int i = 0; i < cp->nb_points; i++) {
                        int px = offset_img2_x + cp->points_arrivee[i].x;
                        int py = offset_img2_y + cp->points_arrivee[i].y;
                        int dist = (clic.x - px) * (clic.x - px) + (clic.y - py) * (clic.y - py);
                        
                        if (dist < rayon_detection * rayon_detection) {
                            point_trouve = i;
                            break;
                        }
                    }
                }
                
                // si un point est trouvé, le supprimer
                if (point_trouve != -1) {
                    printf("✓ Suppression du couple %d\n", point_trouve + 1);
                    
                    // décaler tous les points suivants
                    for (int i = point_trouve; i < cp->nb_points - 1; i++) {
                        cp->points_depart[i] = cp->points_depart[i + 1];
                        cp->points_arrivee[i] = cp->points_arrivee[i + 1];
                    }
                    cp->nb_points--;
                    
                    sauvegarde_effectuee = 0;  // Marquer comme non sauvegardé
                }
            }
            // clic sur image de gauche
            else if (attendre_depart && 
                     clic.x >= offset_img1_x && clic.x < offset_img1_x + img1->largeur &&
                     clic.y >= offset_img1_y && clic.y < offset_img1_y + img1->hauteur) {
                
                dernier_point_depart.x = clic.x - offset_img1_x;
                dernier_point_depart.y = clic.y - offset_img1_y;
                
                printf("Point %d - Départ: (%d, %d)\n", 
                       cp->nb_points + 1, dernier_point_depart.x, dernier_point_depart.y);
                
                attendre_depart = 0;
                sauvegarde_effectuee = 0;
            }
            // clic sur image de droite
            else if (!attendre_depart &&
                     clic.x >= offset_img2_x && clic.x < offset_img2_x + img2->largeur &&
                     clic.y >= offset_img2_y && clic.y < offset_img2_y + img2->hauteur) {
                
                Point point_arrivee;
                point_arrivee.x = clic.x - offset_img2_x;
                point_arrivee.y = clic.y - offset_img2_y;
                
                printf("Point %d - Arrivée: (%d, %d)\n", 
                       cp->nb_points + 1, point_arrivee.x, point_arrivee.y);
                
                ajouter_couple(cp, dernier_point_depart, point_arrivee);
                
                printf("✓ Couple %d ajouté\n\n", cp->nb_points);
                
                attendre_depart = 1;
                sauvegarde_effectuee = 0;
            }
        }
    }
    
    printf("\n✓ Sélection terminée : %d couples de points\n", cp->nb_points);
    return cp;
}
