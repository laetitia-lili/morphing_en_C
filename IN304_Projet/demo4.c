#include "uvsqgraphics_2.h"

// ##############################
// Démo 4 de l'API uvsqgraphics_2
// Octobre 2025
// ##############################

int NB_COULEURS;
int COUL[256];
char * NOM[256];


// #######################
// ## 1. Initialisation ##
// #######################
void init_couleur() {
	int cpt = 0;
	NOM[cpt] = "argent";    COUL[cpt] = 0xC0C0C0; cpt++;
	NOM[cpt] = "blanc";     COUL[cpt] = 0xFFFFFF; cpt++;
	NOM[cpt] = "bleu";      COUL[cpt] = 0x0000FF; cpt++;
	NOM[cpt] = "bleumarine";COUL[cpt] = 0x000080; cpt++;
	NOM[cpt] = "citronvert";COUL[cpt] = 0x00FF00; cpt++;
	NOM[cpt] = "cyan";      COUL[cpt] = 0x00FFFF; cpt++;
	NOM[cpt] = "magenta";   COUL[cpt] = 0xFF00FF; cpt++;
	NOM[cpt] = "gris";      COUL[cpt] = 0x808080; cpt++;
	NOM[cpt] = "jaune";     COUL[cpt] = 0xFFFF00; cpt++;
	NOM[cpt] = "marron";    COUL[cpt] = 0x800000; cpt++;
	NOM[cpt] = "noir";      COUL[cpt] = 0x000000; cpt++;
	NOM[cpt] = "rouge";     COUL[cpt] = 0xFF0000; cpt++;
	NOM[cpt] = "sarcelle";  COUL[cpt] = 0x008080; cpt++;
	NOM[cpt] = "vert";      COUL[cpt] = 0x008000; cpt++;
	NOM[cpt] = "vertolive"; COUL[cpt] = 0x808000; cpt++;
	NOM[cpt] = "violet";    COUL[cpt] = 0x800080; cpt++;
	NB_COULEURS = cpt;
	printf("%3d couleurs en français\n",NB_COULEURS);

	NOM[cpt] = "aliceblue";           COUL[cpt] = 0xF0F8FF; cpt++;
	NOM[cpt] = "antiquewhite";        COUL[cpt] = 0xFAEBD7; cpt++;
	NOM[cpt] = "aqua";                COUL[cpt] = 0x00FFFF; cpt++;
	NOM[cpt] = "aquamarine";          COUL[cpt] = 0x7FFFD4; cpt++;
	NOM[cpt] = "azure";               COUL[cpt] = 0xF0FFFF; cpt++;
	NOM[cpt] = "beige";               COUL[cpt] = 0xF5F5DC; cpt++;
	NOM[cpt] = "bisque";              COUL[cpt] = 0xFFE4C4; cpt++;
	NOM[cpt] = "black";               COUL[cpt] = 0x000000; cpt++;
	NOM[cpt] = "blanchedalmond";      COUL[cpt] = 0xFFEBCD; cpt++;
	NOM[cpt] = "blue";                COUL[cpt] = 0x0000FF; cpt++;
	NOM[cpt] = "blueviolet";          COUL[cpt] = 0x8A2BE2; cpt++;
	NOM[cpt] = "brown";               COUL[cpt] = 0xA52A2A; cpt++;
	NOM[cpt] = "burlywood";           COUL[cpt] = 0xDEB887; cpt++;
	NOM[cpt] = "cadetblue";           COUL[cpt] = 0x5F9EA0; cpt++;
	NOM[cpt] = "chartreuse";          COUL[cpt] = 0x7FFF00; cpt++;
	NOM[cpt] = "chocolate";           COUL[cpt] = 0xD2691E; cpt++;
	NOM[cpt] = "coral";               COUL[cpt] = 0xFF7F50; cpt++;
	NOM[cpt] = "cornflowerblue";      COUL[cpt] = 0x6495ED; cpt++;
	NOM[cpt] = "cornsilk";            COUL[cpt] = 0xFFF8DC; cpt++;
	NOM[cpt] = "crimson";             COUL[cpt] = 0xDC143C; cpt++;
	NOM[cpt] = "cyan";                COUL[cpt] = 0x00FFFF; cpt++;
	NOM[cpt] = "darkblue";            COUL[cpt] = 0x00008B; cpt++;
	NOM[cpt] = "darkcyan";            COUL[cpt] = 0x008B8B; cpt++;
	NOM[cpt] = "darkgoldenrod";       COUL[cpt] = 0xB8860B; cpt++;
	NOM[cpt] = "darkgray";            COUL[cpt] = 0xA9A9A9; cpt++;
	NOM[cpt] = "darkgreen";           COUL[cpt] = 0x006400; cpt++;
	NOM[cpt] = "darkkhaki";           COUL[cpt] = 0xBDB76B; cpt++;
	NOM[cpt] = "darkmagenta";         COUL[cpt] = 0x8B008B; cpt++;
	NOM[cpt] = "darkolivegreen";      COUL[cpt] = 0x556B2F; cpt++;
	NOM[cpt] = "darkorange";          COUL[cpt] = 0xFF8C00; cpt++;
	NOM[cpt] = "darkorchid";          COUL[cpt] = 0x9932CC; cpt++;
	NOM[cpt] = "darkred";             COUL[cpt] = 0x8B0000; cpt++;
	NOM[cpt] = "darksalmon";          COUL[cpt] = 0xE9967A; cpt++;
	NOM[cpt] = "darkseagreen";        COUL[cpt] = 0x8FBC8F; cpt++;
	NOM[cpt] = "darkslateblue";       COUL[cpt] = 0x483D8B; cpt++;
	NOM[cpt] = "darkslategray";       COUL[cpt] = 0x2F4F4F; cpt++;
	NOM[cpt] = "darkturquoise";       COUL[cpt] = 0x00CED1; cpt++;
	NOM[cpt] = "darkviolet";          COUL[cpt] = 0x9400D3; cpt++;
	NOM[cpt] = "deeppink";            COUL[cpt] = 0xFF1493; cpt++;
	NOM[cpt] = "deepskyblue";         COUL[cpt] = 0x00BFFF; cpt++;
	NOM[cpt] = "dimgray";             COUL[cpt] = 0x696969; cpt++;
	NOM[cpt] = "dodgerblue";          COUL[cpt] = 0x1E90FF; cpt++;
	NOM[cpt] = "firebrick";           COUL[cpt] = 0xB22222; cpt++;
	NOM[cpt] = "floralwhite";         COUL[cpt] = 0xFFFAF0; cpt++;
	NOM[cpt] = "forestgreen";         COUL[cpt] = 0x228B22; cpt++;
	NOM[cpt] = "fuchsia";             COUL[cpt] = 0xFF00FF; cpt++;
	NOM[cpt] = "gainsboro";           COUL[cpt] = 0xDCDCDC; cpt++;
	NOM[cpt] = "ghostwhite";          COUL[cpt] = 0xF8F8FF; cpt++;
	NOM[cpt] = "gold";                COUL[cpt] = 0xFFD700; cpt++;
	NOM[cpt] = "goldenrod";           COUL[cpt] = 0xDAA520; cpt++;
	NOM[cpt] = "gray";                COUL[cpt] = 0x808080; cpt++;
	NOM[cpt] = "green";               COUL[cpt] = 0x008000; cpt++;
	NOM[cpt] = "greenyellow";         COUL[cpt] = 0xADFF2F; cpt++;
	NOM[cpt] = "honeydew";            COUL[cpt] = 0xF0FFF0; cpt++;
	NOM[cpt] = "hotpink";             COUL[cpt] = 0xFF69B4; cpt++;
	NOM[cpt] = "indianred";           COUL[cpt] = 0xCD5C5C; cpt++;
	NOM[cpt] = "indigo";              COUL[cpt] = 0x4B0082; cpt++;
	NOM[cpt] = "ivory";               COUL[cpt] = 0xFFFFF0; cpt++;
	NOM[cpt] = "khaki";               COUL[cpt] = 0xF0E68C; cpt++;
	NOM[cpt] = "lavender";            COUL[cpt] = 0xE6E6FA; cpt++;
	NOM[cpt] = "lavenderblush";       COUL[cpt] = 0xFFF0F5; cpt++;
	NOM[cpt] = "lawngreen";           COUL[cpt] = 0x7CFC00; cpt++;
	NOM[cpt] = "lemonchiffon";        COUL[cpt] = 0xFFFACD; cpt++;
	NOM[cpt] = "lightblue";           COUL[cpt] = 0xADD8E6; cpt++;
	NOM[cpt] = "lightcoral";          COUL[cpt] = 0xF08080; cpt++;
	NOM[cpt] = "lightcyan";           COUL[cpt] = 0xE0FFFF; cpt++;
	NOM[cpt] = "lightgoldenrodyellow";COUL[cpt] = 0xFAFAD2; cpt++;
	NOM[cpt] = "lightgreen";          COUL[cpt] = 0x90EE90; cpt++;
	NOM[cpt] = "lightgrey";           COUL[cpt] = 0xD3D3D3; cpt++;
	NOM[cpt] = "lightpink";           COUL[cpt] = 0xFFB6C1; cpt++;
	NOM[cpt] = "lightsalmon";         COUL[cpt] = 0xFFA07A; cpt++;
	NOM[cpt] = "lightseagreen";       COUL[cpt] = 0x20B2AA; cpt++;
	NOM[cpt] = "lightskyblue";        COUL[cpt] = 0x87CEFA; cpt++;
	NOM[cpt] = "lightslategray";      COUL[cpt] = 0x778899; cpt++;
	NOM[cpt] = "lightsteelblue";      COUL[cpt] = 0xB0C4DE; cpt++;
	NOM[cpt] = "lightyellow";         COUL[cpt] = 0xFFFFE0; cpt++;
	NOM[cpt] = "lime";                COUL[cpt] = 0x00FF00; cpt++;
	NOM[cpt] = "limegreen";           COUL[cpt] = 0x32CD32; cpt++;
	NOM[cpt] = "linen";               COUL[cpt] = 0xFAF0E6; cpt++;
	NOM[cpt] = "magenta";             COUL[cpt] = 0xFF00FF; cpt++;
	NOM[cpt] = "maroon";              COUL[cpt] = 0x800000; cpt++;
	NOM[cpt] = "mediumaquamarine";    COUL[cpt] = 0x66CDAA; cpt++;
	NOM[cpt] = "mediumblue";          COUL[cpt] = 0x0000CD; cpt++;
	NOM[cpt] = "mediumorchid";        COUL[cpt] = 0xBA55D3; cpt++;
	NOM[cpt] = "mediumpurple";        COUL[cpt] = 0x9370DB; cpt++;
	NOM[cpt] = "mediumseagreen";      COUL[cpt] = 0x3CB371; cpt++;
	NOM[cpt] = "mediumslateblue";     COUL[cpt] = 0x7B68EE; cpt++;
	NOM[cpt] = "mediumspringgreen";   COUL[cpt] = 0x00FA9A; cpt++;
	NOM[cpt] = "mediumturquoise";     COUL[cpt] = 0x48D1CC; cpt++;
	NOM[cpt] = "mediumvioletred";     COUL[cpt] = 0xC71585; cpt++;
	NOM[cpt] = "midnightblue";        COUL[cpt] = 0x191970; cpt++;
	NOM[cpt] = "mintcream";           COUL[cpt] = 0xF5FFFA; cpt++;
	NOM[cpt] = "mistyrose";           COUL[cpt] = 0xFFE4E1; cpt++;
	NOM[cpt] = "moccasin";            COUL[cpt] = 0xFFE4B5; cpt++;
	NOM[cpt] = "navajowhite";         COUL[cpt] = 0xFFDEAD; cpt++;
	NOM[cpt] = "navy";                COUL[cpt] = 0x000080; cpt++;
	NOM[cpt] = "oldlace";             COUL[cpt] = 0xFDF5E6; cpt++;
	NOM[cpt] = "olive";               COUL[cpt] = 0x808000; cpt++;
	NOM[cpt] = "olivedrab";           COUL[cpt] = 0x6B8E23; cpt++;
	NOM[cpt] = "orange";              COUL[cpt] = 0xFFA500; cpt++;
	NOM[cpt] = "orangered";           COUL[cpt] = 0xFF4500; cpt++;
	NOM[cpt] = "orchid";              COUL[cpt] = 0xDA70D6; cpt++;
	NOM[cpt] = "palegoldenrod";       COUL[cpt] = 0xEEE8AA; cpt++;
	NOM[cpt] = "palegreen";           COUL[cpt] = 0x98FB98; cpt++;
	NOM[cpt] = "paleturquoise";       COUL[cpt] = 0xAFEEEE; cpt++;
	NOM[cpt] = "palevioletred";       COUL[cpt] = 0xDB7093; cpt++;
	NOM[cpt] = "papayawhip";          COUL[cpt] = 0xFFEFD5; cpt++;
	NOM[cpt] = "peachpuff";           COUL[cpt] = 0xFFDAB9; cpt++;
	NOM[cpt] = "peru";                COUL[cpt] = 0xCD853F; cpt++;
	NOM[cpt] = "pink";                COUL[cpt] = 0xFFC0CB; cpt++;
	NOM[cpt] = "plum";                COUL[cpt] = 0xDDA0DD; cpt++;
	NOM[cpt] = "powderblue";          COUL[cpt] = 0xB0E0E6; cpt++;
	NOM[cpt] = "purple";              COUL[cpt] = 0x800080; cpt++;
	NOM[cpt] = "red";                 COUL[cpt] = 0xFF0000; cpt++;
	NOM[cpt] = "rosybrown";           COUL[cpt] = 0xBC8F8F; cpt++;
	NOM[cpt] = "royalblue";           COUL[cpt] = 0x4169E1; cpt++;
	NOM[cpt] = "saddlebrown";         COUL[cpt] = 0x8B4513; cpt++;
	NOM[cpt] = "salmon";              COUL[cpt] = 0xFA8072; cpt++;
	NOM[cpt] = "sandybrown";          COUL[cpt] = 0xF4A460; cpt++;
	NOM[cpt] = "seagreen";            COUL[cpt] = 0x2E8B57; cpt++;
	NOM[cpt] = "seashell";            COUL[cpt] = 0xFFF5EE; cpt++;
	NOM[cpt] = "sienna";              COUL[cpt] = 0xA0522D; cpt++;
	NOM[cpt] = "silver";              COUL[cpt] = 0xC0C0C0; cpt++;
	NOM[cpt] = "skyblue";             COUL[cpt] = 0x87CEEB; cpt++;
	NOM[cpt] = "slateblue";           COUL[cpt] = 0x6A5ACD; cpt++;
	NOM[cpt] = "slategray";           COUL[cpt] = 0x708090; cpt++;
	NOM[cpt] = "snow";                COUL[cpt] = 0xFFFAFA; cpt++;
	NOM[cpt] = "springgreen";         COUL[cpt] = 0x00FF7F; cpt++;
	NOM[cpt] = "steelblue";           COUL[cpt] = 0x4682B4; cpt++;
	NOM[cpt] = "tan";                 COUL[cpt] = 0xD2B48C; cpt++;
	NOM[cpt] = "teal";                COUL[cpt] = 0x008080; cpt++;
	NOM[cpt] = "thistle";             COUL[cpt] = 0xD8BFD8; cpt++;
	NOM[cpt] = "tomato";              COUL[cpt] = 0xFF6347; cpt++;
	NOM[cpt] = "turquoise";           COUL[cpt] = 0x40E0D0; cpt++;
	NOM[cpt] = "violetlight";         COUL[cpt] = 0xEE82EE; cpt++;
	NOM[cpt] = "wheat";               COUL[cpt] = 0xF5DEB3; cpt++;
	NOM[cpt] = "white";               COUL[cpt] = 0xFFFFFF; cpt++;
	NOM[cpt] = "whitesmoke";          COUL[cpt] = 0xF5F5F5; cpt++;
	NOM[cpt] = "yellow";              COUL[cpt] = 0xFFFF00; cpt++;
	NOM[cpt] = "yellowgreen";         COUL[cpt] = 0x9ACD32; cpt++;
	printf("%3d couleurs en anglais\n",cpt-NB_COULEURS);
	NB_COULEURS = cpt;
	printf("%3d couleurs\n",NB_COULEURS);
}

// ##################
// ## 2. Affichage ##
// ##################
//#define inv(x) ((x)<0x80?0xFF:0)
//#define inv(x) ((x)<128?(255):(0))
COULEUR complementaire(COULEUR coul) {
	int R, G, B;
	R = (coul & rouge)>>16;
	G = (coul & vert) >> 8;
	B = (coul & bleu);
	double luminance = 0.2126 * R + 0.7152 * G + 0.0722 * B;
	if (luminance > 128) return couleur_RGB(0,0,0);
		else return couleur_RGB(255,255,255);
}

void affiche_couleur(int L, int H) {
	int i,j, cpt;;
	POINT hg, bd;


	POINT centre;
	centre.x = L/2;
	centre.y = 765; aff_pol_centre("Fran"ccedil"ais",20,centre,silver);
	centre.y = 33; aff_pol_centre("Anglais",20,centre,silver);
	cpt = 0;
	for (i=0;i<40;i++) {
		if (i<4) hg.y = H - (20*i + 30); else hg.y = H - (20*i + 60);
		for (j=0;j<4;j++) {
			hg.x = 150*j;
			bd.x = hg.x + 150;
			bd.y = hg.y + 20;
			if (cpt < NB_COULEURS) {
				draw_fill_rectangle(hg,bd,COUL[cpt]);
				hg.x += 3;
				aff_pol(NOM[cpt],14, hg, complementaire(COUL[cpt]));
			}
			cpt++;
		}
	}
	centre.y = 10;
	aff_pol_centre("http://fr.wikipedia.org/wiki/Liste_de_couleurs",20,centre,white);
	printf("http://fr.wikipedia.org/wiki/Liste_de_couleurs\n");
}

// ################
// ## 3. LE MAIN ##
// ################
int main (int argc, char *argv[]) {
	int H=870;
	int L=600;
	set_mode_WINDOW();
	init_graphics(L,H);
	init_couleur();
	affiche_couleur(L,H);
	affiche_all();
	wait_clic();

	exit (0);
}
