#include "uvsqgraphics_2.h"

// ##############################
// Démo 0 de l'API uvsqgraphics_2
// Octobre 2025
// ##############################

int main(int argc, char *argv[]) {
// Création d'un fenêtre graphique de taille 900x600
	init_graphics(900,600);

// Déclaration de deux variables de type POINT
	POINT P1;
	POINT P2;

// Affection des champs x et y des variables P1 et P2
	P1.x =  10; P1.y = 10;
	P2.x = 700; P2.y = 500;
// Affichage d'un segment rouge entre P1 et P2
	draw_line(P1,P2,rouge);

// Affection des champs x et y des variables P1 et P2
	P1.x = 100; P1.y =  90;
	P2.x = 200; P2.y = 300;
// Affichage d'un rectangle colorié en bleu parallèle aux cotés de la fenêtre graphique
	draw_fill_rectangle(P1,P2,bleu);

// Affection des champs x et y de la variable P1
	P1.x = 300; P1.y = 350;
// Affichage d'un cercle centré en P1, de rayon 100 et de couleur verte
	draw_circle(P1, 100, vert);

// Attente d'un clic de la souris et au moment du clic les coordonnées x, y
// du curseur sont affectées aux champs x, y de P1
	P1 = wait_clic();
// Affichage d'un disque centré en P1, de rayon 70 et de couleur orange
	draw_fill_circle(P1,70,orange);

// Attente de l'appui sur la touche Echap avant de fermer la fenêtre graphique
	wait_escape();
	exit(0);
}
