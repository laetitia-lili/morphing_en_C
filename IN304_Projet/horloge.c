#include "uvsqgraphics_2.h"

// ##############################
// Horloge numéroique et analogique
// Octobre 2025
// ##############################

#define PI 3.141592654
// Taille de l'écran
#define LARGEUR 600
#define HAUTEUR 900
// Centre de l'horloge analogique
#define CX (LARGEUR/2)
#define CY (2*HAUTEUR/3)
// Rayon de l'horloge analogique
#define RAYON (0.85*LARGEUR/2)

#define LS (RAYON)     // Longueur de l'aiguille des secondes
#define LM (0.8*RAYON) // Longueur de l'aiguille des minutes
#define LH (0.5*RAYON) // Longueur de l'aiguille des heures
#define COULS gris     // Couleur de l'aiguille des secondes
#define COULM blanc    // Couleur de l'aiguille des minutes
#define COULH rouge    // Couleur de l'aiguille des heures

// Couleur de l'affichage digital
#define COULD dodgerblue

// Taille de la police des chiffres du cadran
#define TAILLE_POL 45

// ###
// Horloge analogique
// ###

// Affiche les marques de 1 à 12 autour du cadran
void affiche_marque(int m, float angle, COULEUR c) {
	if (m==0) m=60;
	POINT P;
	P.x = CX + RAYON*cos(angle);
	P.y = CY - RAYON*sin(angle);
	if (m%5==0) {
		draw_fill_circle(P,6,c);
		char texte[16];
		sprintf(texte,"%d",m/5);
		P.x = CX + 0.85*RAYON*cos(angle);
		P.y = CY - 0.85*RAYON*sin(angle);
		aff_pol_centre(texte,TAILLE_POL,P,blanc);
	}
	else draw_fill_circle(P,3,c);
}

// Calcul l'angle an radian donnée en proprtion de val/un_tour
// Sachant que val vaut zéro en haut.
// si val vaut 3 et un_tour vaut 12 l'angle doit être 0
// si val vaut 2 et un_tour vaut 12 l'angle doit être PI/6
// si val vaut 1 et un_tour vaut 12 l'angle doit être 2*PI/6
// etc...
float calcul_angle(float val, int un_tour) {
	float alpha, beta;
	alpha = (2*PI*val)/un_tour;
	beta = 2*PI + PI/2 - alpha;
	return beta;
}

// Fonction générique pour afficher une aiguille
void affiche_une_aiguille(float angle, int longueur, COULEUR coul) {
	POINT centre, extremite_longue, extremite_courte;
	centre.x = CX; centre.y = CY;
	extremite_longue.x = CX + longueur*cos(angle);
	extremite_longue.y = CY - longueur*sin(angle);
	extremite_courte.x = CX + (longueur/5)*cos(angle+PI);
	extremite_courte.y = CY - (longueur/5)*sin(angle+PI);
	draw_line(centre,extremite_courte,coul);
	draw_line(centre,extremite_longue,coul);
}

void affiche_cadran(float s) {
	int m;
	for (m=0 ; m<60 ; m++)
		affiche_marque(m,calcul_angle(m,60),m<s?rouge:gris);
}

// Pour les 3 fonctions ci-dessous, on calcule l'angle de l'aiguille
// puis on appelle la fonction générique d'affichage
void affiche_heure(int h, int m, float s) {
	if (h>12) h = h-12;
	float angle = calcul_angle(3600*h+60*m+s,12*3600);
	affiche_une_aiguille(angle,LH,COULH);
}

void affiche_minute(int m, float s) {
	float angle = calcul_angle(60*m+s,3600);
	affiche_une_aiguille(angle,LM,COULM);
}

void affiche_seconde(float s) {
	float angle = calcul_angle(s,60);
	affiche_une_aiguille(angle,LS,COULS);
}

void affiche_AM_PM(int h) {
	POINT hg;
	char texte[3];
	if (h<12) sprintf(texte,"AM"); else sprintf(texte,"PM");
//	hg.x = LARGEUR - 1.1*largeur_texte(texte,TAILLE_POL);
//	hg.y = HAUTEUR/3 + 1.1*hauteur_texte(texte,TAILLE_POL);
	hg.x = LARGEUR/2;
	hg.y = HAUTEUR/4;
//	aff_pol(texte,TAILLE_POL,hg,blanc);
}

void affiche_analogique(int h, int m, float s) {
	affiche_cadran(s);
	affiche_heure(h,m,s);
	affiche_minute(m,s);
	affiche_seconde(s);
//	affiche_AM_PM(h);
}

// ###
// Séparation
// ###
void affiche_separation() {
	POINT g, d;
	g.x = 0; d.x = LARGEUR;
	g.y = d.y = HAUTEUR/3;
	draw_line(g,d,blanc);
}

// ###
// Horloge digitale
// ###
// Les segments sont numérotés de la façon suivante
//    -    0
//   | |  1 2
//    -    3
//   | |  4 5
//    -    6

#define delta (LARGEUR/8)  // Ecart entre deux chiffres
#define S (0.4*delta)      // Demi longueur d'un segment
#define E 5                // Demi épaisseur du trait
void affiche_chiffre_couleur(POINT centre, int c, COULEUR coul, int fill) {
	POINT bg,hd;
// Segment 0
	if (c==0 || c==2 || c==3 || c==5 || c==6 || c==7 || c==8 || c==9) {
		bg.x = centre.x - S - E; bg.y = centre.y - 2*S + E;
		hd.x = bg.x + 2*S + 2*E; hd.y = bg.y - 2*E;
		if (fill) draw_fill_rectangle(bg,hd,coul);
			else  draw_rectangle(bg,hd,coul);
	}
// Segment 1
	if (c==0 || c==4 || c==5 || c==6 || c==8 || c==9) {
		bg.x = centre.x - S - E; bg.y = centre.y + E;
		hd.x = bg.x + 2*E;       hd.y = bg.y - 2*S - 2*E;
		if (fill) draw_fill_rectangle(bg,hd,coul);
			else  draw_rectangle(bg,hd,coul);
	}
// Segment 2
	if (c==0 || c==1 || c==2 || c==3 || c==4 || c==7 || c==8 || c==9) {
		bg.x = centre.x + S - E; bg.y = centre.y + E;
		hd.x = bg.x + 2*E;       hd.y = bg.y - 2*S - 2*E;
		if (fill) draw_fill_rectangle(bg,hd,coul);
			else  draw_rectangle(bg,hd,coul);
	}
// Segment 3
	if (c==2 || c==3 || c==4 || c==5 || c==6 || c==8 || c==9) {
		bg.x = centre.x - S - E; bg.y = centre.y + E;
		hd.x = bg.x + 2*S + 2*E; hd.y = bg.y - 2*E;
		if (fill) draw_fill_rectangle(bg,hd,coul);
			else  draw_rectangle(bg,hd,coul);
	}
// Segment 4
	if (c==0 || c==2 || c==6 || c==8) {
		bg.x = centre.x - S - E; bg.y = centre.y + 2*S + E;
		hd.x = bg.x + 2*E;       hd.y = bg.y - 2*S - 2*E;
		if (fill) draw_fill_rectangle(bg,hd,coul);
			else  draw_rectangle(bg,hd,coul);
	}
// Segment 5
	if (c==0 || c==1 || c==3 || c==4 || c==5 || c==6 || c==7 || c==8 || c==9) {
		bg.x = centre.x + S - E; bg.y = centre.y + 2*S + E;
		hd.x = bg.x + 2*E;       hd.y = bg.y - 2*S - 2*E;
		if (fill) draw_fill_rectangle(bg,hd,coul);
			else  draw_rectangle(bg,hd,coul);
	}
// Segment 6
	if (c==0 || c==2 || c==3 || c==5 || c==6 || c==8 || c==9) {
		bg.x = centre.x - S - E; bg.y = centre.y + 2*S + E;
		hd.x = bg.x + 2*S + 2*E; hd.y = bg.y - 2*E;
		if (fill) draw_fill_rectangle(bg,hd,coul);
			else  draw_rectangle(bg,hd,coul);
	}
}

void affiche_chiffre(POINT centre, int c) {
	affiche_chiffre_couleur(centre, c, COULD, 1);
	affiche_chiffre_couleur(centre, c, noir, 0);
}


void affiche_deux_points (POINT centre, float s) {
	if (s - (int)s < 0.5) {
		POINT hg, bd;
		hg.x = centre.x - E;
		bd.x = centre.x + E;
		hg.y = centre.y - E - S*0.75;
		bd.y = centre.y + E - S*0.75;
		draw_fill_rectangle(hg,bd,COULD);
		hg.y += S*1.5;
		bd.y += S*1.5;
		draw_fill_rectangle(hg,bd,COULD);
//		draw_fill_circle(H,2*E,COULD);
//		draw_fill_circle(B,2*E,COULD);
	}
}

void affiche_digital(int h, int m, float s) {
	POINT centre; centre.y = HAUTEUR/6;
	centre.x = delta;
	affiche_chiffre(centre,h/10);  centre.x += delta;
	affiche_chiffre(centre,h%10);  centre.x += 0.75*delta;
	affiche_deux_points(centre,s); centre.x += 0.75*delta;
	affiche_chiffre(centre,m/10);  centre.x += delta;
	affiche_chiffre(centre,m%10);  centre.x += 0.75*delta;
	affiche_deux_points(centre,s); centre.x += 0.75*delta;
	affiche_chiffre(centre,(int)s/10);  centre.x += delta;
	affiche_chiffre(centre,(int)s%10);
}

void affiche(int h, int m, float s) {
	fill_screen(noir);
	affiche_analogique(h,m,s);
	affiche_separation();
	affiche_digital(h,m,s);
	affiche_all();
}

int main() {
	int h,m;
	float s;
	set_mode_WINDOW();
	init_graphics(LARGEUR,HAUTEUR);
	while (1) {
		h = heure(); m = minute(); s = seconde();
		printf("%d:%d:%.2f\r",h,m,s);fflush(stdout);
		affiche(h,m,s);
//		attendre(1000);
	}
	exit(0);
}
