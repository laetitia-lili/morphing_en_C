#include "uvsqgraphics_2.h"

// ############################
// Démo 2 de l'API uvsqgraphics
// ############################

// ################
// 1. Test du texte
// ################
void affichage_texte() {
	int i,n;
	int h,m,s;
	BOOL b;
	write_text("1. Test affichage texte"); write_ln();
	write_text("Bonjour en normal"); write_ln();
	pol_style(GRAS); write_text("Bonjour en gras"); write_ln();
	pol_style(ITALIQUE); write_text("Bonjour en italique"); write_ln();
	pol_style(SOULIGNE); write_text("Bonjour soulign"eacute); write_ln();
	pol_style(NORMAL); write_ln();

	write_text("2. Test de l'heure"); write_ln();
	h = heure();
	m = minute();
	s = seconde();
	write_text("Il est "); 
	write_int(h); write_text(" heure ");
	write_int(m); write_text( " minute ");
	write_int(s); write_text(" seconde");
	write_ln(); write_ln();

	write_text("3. Test affichage bool"eacute"en "); write_ln();
	b = (2<3);
	write_bool(b); write_text(" "); write_bool(2 == 3); write_text(" "); write_bool(TRUE); write_ln(); write_ln();

	write_text("4. Test alea");
	write_ln();
	for ( i=0 ; i<5 ; i=i+1 ) {
		n = alea_int(100); 
		write_int(n); write_ln();
	}
}


// ####################
// 2. Test du graphisme
// ####################
void affichage_graphique() {
	POINT P1, P2;
	P1 = wait_clic();
	P2 = wait_clic();
	draw_fill_rectangle(P1,P2,rouge);

	P1 = wait_clic(); draw_fill_circle(P1,40,rouge);
	P1 = wait_clic(); draw_fill_circle(P1,40,vert);
	P1 = wait_clic(); draw_fill_circle(P1,40,bleu);
	P1 = wait_clic(); draw_fill_circle(P1,40,jaune);
	P1 = wait_clic(); draw_fill_circle(P1,40,cyan);
	P1 = wait_clic(); draw_fill_circle(P1,40,magenta);
	P1 = wait_clic(); draw_fill_circle(P1,40,blanc);
	P1 = wait_clic(); draw_fill_circle(P1,40,gris);
	P1 = wait_clic(); draw_fill_circle(P1,40,noir); draw_circle(P1,40,blanc);
	P1 = wait_clic(); draw_circle(P1,40,rouge);
}


// #####################
// 2. Test des triangles
// #####################
void affichage_triangle() {
	POINT P1, P2, P3;
	P1 = wait_clic();
	P2 = wait_clic();
	P3 = wait_clic();
	draw_triangle(P1,P2,P3,bleu);

	P1 = wait_clic();
	P2 = wait_clic();
	draw_fill_ellipse(P1,P2,30,jaune);
}

// ###################
// 3. Test des flèches
// ###################
#define LE_RAYON 40
void test_fleches() {
	POINT P = {200,300};
	COULEUR C;
	POINT delta;
	POINT pos;
	char *s1 = "Appuyer sur les fl"egrave"ches";
	char s[32];
	int cpt = 
	C = bleu;
	affiche_auto_off();
	cpt = 100;
	pos.x = LARGEUR_FENETRE/2 - largeur_texte(s1,25)/2;
	pos.y = hauteur_texte(s1,25);; 
	fill_screen(noir);
	aff_pol(s1, 25,pos,jaune);
	affiche_all();

	while (cpt) {
		sprintf(s,"%s %d",s1,cpt);
		pos.x = LARGEUR_FENETRE/2 - largeur_texte(s,25)/2;
		aff_pol(s,25,pos,jaune);
		draw_fill_circle(P,LE_RAYON,C);
		affiche_all();
		delta = get_arrow();
		if (delta.x ||delta.y) {
			cpt--;
			P.x = P.x + 4*delta.x;
			P.y = P.y - 4*delta.y;
		}
	}
	affiche_auto_on();
}

// ####################
// 3. Test de la souris
// ####################

void test_souris() {
	POINT P = {200,300};
	COULEUR C = blanc;
	POINT pos;
	int cpt;
	char *s1 = "D"eacute"placer la souris";
	char s[32];
	affiche_auto_off();
	mouse_off();

	cpt = 1001;
	sprintf(s,"%s %d",s1,1000-cpt);
	pos.y = hauteur_texte(s1,25);; 
	while (cpt) {
		cpt--;
		aff_pol(s,25,pos,noir);
		P = get_mouse();
		attendre(5);
		draw_fill_circle(P,20,C);
		sprintf(s,"%s %03d",s1,cpt);
		pos.x = LARGEUR_FENETRE/2 - largeur_texte(s,25)/2;
		aff_pol(s,25,pos,rouge);
		affiche_all();
	}
	affiche_auto_on();
	mouse_on();
}

int NB_COULEURS;
int COUL[256];
char * NOM[256];
void affiche_couleur();

// ################
// ## 4. LE MAIN ##
// ################
int main (int argc, char *argv[]) {
	init_graphics(600,450); 
	POINT p = {170,45};

	aff_pol("Cliquer plusieurs fois", 25,p,jaune);
	affichage_graphique();
	affichage_triangle();
	aff_pol("Cliquer plusieurs fois", 25,p,noir);
	aff_pol("Cliquer pour continuer", 25,p,jaune); wait_clic();

	fill_screen(noir);
	affichage_texte();
	aff_pol("Cliquer pour continuer", 25,p,jaune); wait_clic();

	fill_screen(noir);
	test_fleches();

	fill_screen(noir);
	test_souris();

	attendre(500);
	exit (0);
}
