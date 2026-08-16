#include "uvsqgraphics_2.h"

// ##############################
// Démo 1 de l'API uvsqgraphics_2
// Octobre 2025
// ##############################


int main () {
	POINT P1, P2, P3;
	init_graphics(800,600);
	fill_screen (antiquewhite);

	P1=wait_clic();
	draw_fill_circle(P1,50,blueviolet);
	P1=wait_clic();
	draw_circle(P1,39,white);
	draw_circle(P1,40,white);
	draw_circle(P1,41,white);

	P1=wait_clic();
	P2=wait_clic();
	draw_fill_rectangle(P1,P2,violetlight);
	P2=wait_clic();
	draw_rectangle(P1,P2,violet);

	wait_clic();
	fill_screen(lavender);
	P1=wait_clic();
	draw_fill_circle(P1,80,crimson);

	P1 = wait_clic();
	draw_fill_circle(P1,80,rouge);
	wait_clic();

	P1.x = 400;
	P1.y = 300;
	aff_pol_centre("Cliquer trois fois pour faire un triangle",30,P1,blanc);
	P1=wait_clic();
	P2=wait_clic();
	P3=wait_clic();
	draw_fill_triangle(P1,P2,P3,vert);

// Attente de l'appui sur la touche Echap pour terminer
	wait_escape();
	exit(0);
}
