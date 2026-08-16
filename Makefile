# Makefile du projet de morphing d'images
# UE Développement d'applications en C - UVSQ (L3 Informatique)
#
# Utilise pkg-config pour retrouver SDL2 / SDL2_ttf / SDL2_gfx,
# ce qui rend la compilation portable entre Linux et macOS
# (installer les libs via apt sur Linux ou brew sur macOS, voir README.md).

CC = gcc
CFLAGS = -Wall -Wextra -g -I./include -I./IN304_Projet \
         $(shell pkg-config --cflags sdl2 SDL2_ttf SDL2_gfx 2>/dev/null)
LDFLAGS = $(shell pkg-config --libs sdl2 SDL2_ttf SDL2_gfx 2>/dev/null) -lm

SRCDIR = src
OBJDIR = obj

# Programme principal (final)
morphing: $(OBJDIR)/main_final.o $(OBJDIR)/image.o $(OBJDIR)/selection_points.o $(OBJDIR)/morphing.o $(OBJDIR)/uvsqgraphics_2.o
	$(CC) -o $@ $^ $(LDFLAGS)

# Utilitaire de conversion d'images (JPG/PNG -> PPM via ImageMagick)
convertir_images: $(OBJDIR)/convertir_images.o
	$(CC) -o $@ $^ -lm

# Compilation des fichiers objets
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/uvsqgraphics_2.o: IN304_Projet/uvsqgraphics_2.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Créer le dossier obj
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Nettoyer les fichiers générés par la compilation
clean:
	rm -rf $(OBJDIR) morphing convertir_images

.PHONY: clean
