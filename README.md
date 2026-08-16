# Morphing d'images en C

Projet réalisé dans le cadre de l'UE **IN304 — Développement d'Applications, Langage C** (L2 Informatique, UFR des Sciences, UVSQ — Université Paris-Saclay).

Ce programme réalise un **morphing** entre deux images : il génère une séquence d'images intermédiaires qui transforment progressivement une image de départ en une image d'arrivée, à partir de couples de points de correspondance sélectionnés par l'utilisateur. Les images générées sont ensuite assemblées en une vidéo MP4.

## Aperçu

1. L'utilisateur choisit deux images (déjà converties au format PPM).
2. Une interface graphique (SDL2) s'ouvre et affiche les deux images côte à côte : l'utilisateur clique sur des points qui se correspondent (yeux, nez, contours…).
3. Le programme triangule les points de base et calcule, pour chaque image intermédiaire, l'interpolation des positions et des couleurs entre les deux images (triangulation + interpolation barycentrique).
4. Les images intermédiaires sont enregistrées dans `images_out/`, puis assemblées en vidéo avec `ffmpeg`.

## Structure du projet

```
.
├── src/                    # Code source du projet
│   ├── image.c               # Lecture/écriture PPM (P3 et P6), gestion mémoire des images
│   ├── selection_points.c    # Interface graphique de sélection des couples de points
│   ├── morphing.c            # Triangulation et interpolation (cœur de l'algorithme)
│   ├── convertir_images.c    # Utilitaire de conversion JPG/PNG -> PPM (via ImageMagick)
│   ├── main_final.c          # Point d'entrée du programme final
│   └── main.c, main_selection.c, main_morphing.c, affichage.c
│                              # Versions de développement / tests intermédiaires
├── include/
│   └── image.h               # Structures (Point, Pixel, Image, CouplesPoints, Triangle...)
├── IN304_Projet/             # Bibliothèque graphique fournie par l'UE (uvsqgraphics, SDL2)
├── data/                     # Couples de points sauvegardés par l'interface de sélection
├── images_origine/           # Images sources avant conversion (JPG/PNG)
├── images_ppm/                # Images converties au format PPM, prêtes pour le morphing
├── images_out/                # Images intermédiaires générées par le programme
├── creer_video.sh            # Assemble les images de images_out/ en vidéo MP4 (ffmpeg)
├── Makefile                   # Compilation du projet
└── Documentation projet morphing en C.pdf
                               # Documentation détaillée (choix techniques, fonctions, ressources)
```

> `IN304_Projet/` contient la bibliothèque graphique `uvsqgraphics` fournie par l'UVSQ pour l'enseignement (basée sur SDL2), utilisée pour l'affichage et l'interface de sélection des points. Ce n'est pas du code écrit dans le cadre de ce projet.

## Installation et lancement

Le programme dépend de trois outils : **SDL2** (+ `SDL2_ttf`, `SDL2_gfx`) pour l'interface graphique, **ImageMagick** pour convertir des images en PPM, et **FFmpeg** pour assembler la vidéo finale.

### macOS

**1. Installer les dépendances** (avec [Homebrew](https://brew.sh)) :

```bash
brew install sdl2 sdl2_ttf sdl2_gfx imagemagick ffmpeg pkg-config
```

**2. Compiler** :

```bash
cd projet_morphing
make morphing
```

**3. Lancer** :

```bash
./morphing images_ppm/chat.ppm images_ppm/chien.ppm 30
```

### Linux (Debian / Ubuntu)

**1. Installer les dépendances** :

```bash
sudo apt update
sudo apt install build-essential pkg-config libsdl2-dev libsdl2-ttf-dev libsdl2-gfx-dev imagemagick ffmpeg
```

**2. Compiler** :

```bash
cd projet_morphing
make morphing
```

**3. Lancer** :

```bash
./morphing images_ppm/chat.ppm images_ppm/chien.ppm 30
```

### Windows

Le projet utilise des bibliothèques C (SDL2) et des outils en ligne de commande (`make`, `gcc`, ImageMagick, FFmpeg) pensés pour un environnement Unix. La façon la plus simple et la plus fiable de le faire tourner sous Windows est d'utiliser **WSL2** (Windows Subsystem for Linux), qui fait tourner un vrai Linux à l'intérieur de Windows.

**1. Installer WSL2** (dans un terminal PowerShell en administrateur) :

```powershell
wsl --install
```

Redémarrer l'ordinateur si demandé. Cela installe une distribution Ubuntu par défaut.

**2. Ouvrir le terminal Ubuntu** (depuis le menu Démarrer) puis installer les dépendances comme sur Linux :

```bash
sudo apt update
sudo apt install build-essential pkg-config libsdl2-dev libsdl2-ttf-dev libsdl2-gfx-dev imagemagick ffmpeg
```

**3. Récupérer le projet et compiler** :

```bash
cd projet_morphing
make morphing
```

**4. Lancer le programme** :

```bash
./morphing images_ppm/chat.ppm images_ppm/chien.ppm 30
```

> Pour que la fenêtre graphique SDL2 s'affiche, WSL2 doit avoir accès à un serveur graphique. Les versions récentes de Windows 11 gèrent cela automatiquement (WSLg, intégré par défaut). Sur Windows 10 ou si la fenêtre ne s'ouvre pas, installer [VcXsrv](https://sourceforge.net/projects/vcxsrv/) et lancer XLaunch avant de démarrer le programme.

*(Alternative sans WSL2 : installer [MSYS2](https://www.msys2.org/) puis les paquets `mingw-w64-x86_64-gcc`, `mingw-w64-x86_64-SDL2`, `mingw-w64-x86_64-SDL2_ttf`, `mingw-w64-x86_64-SDL2_gfx` — plus technique à mettre en place que WSL2.)*

## Utilisation du programme

**1. Convertir des images au format PPM** (si nécessaire) :

```bash
magick images_origine/chat.jpg -resize 400x400 images_ppm/chat.ppm
magick images_origine/chien.jpg -resize 400x400 images_ppm/chien.ppm
```

Tailles recommandées : 200×200 pour des tests rapides, 400×400 pour un bon compromis qualité/vitesse, 600×600 pour la meilleure qualité.

**2. Lancer le morphing** :

```bash
./morphing images_ppm/chat.ppm images_ppm/chien.ppm 30
```

- `images_ppm/chat.ppm` : image de départ
- `images_ppm/chien.ppm` : image d'arrivée
- `30` : nombre d'images intermédiaires générées (31 images au total)

**3. Sélectionner les points de correspondance** dans la fenêtre qui s'ouvre :
- clic sur un point dans l'image de gauche, puis sur le point correspondant dans l'image de droite (répéter pour 5 à 10 couples) ;
- bouton **SAUVER** (cyan) pour enregistrer les points dans `data/points.txt` ;
- bouton **QUITTER** (rouge) pour lancer la génération des images intermédiaires.

**4. Générer la vidéo finale** :

```bash
./creer_video.sh
# ou avec un nombre d'images par seconde personnalisé :
./creer_video.sh 15
```

## Détails techniques

- Le format **PPM** (P3 ASCII et P6 binaire) est utilisé pour manipuler les images en C sans dépendance externe pour la lecture/écriture des pixels.
- Les points sélectionnés forment une **triangulation** de l'image ; chaque triangle est interpolé indépendamment entre l'image de départ et l'image d'arrivée pour obtenir un rendu progressif et réaliste.
- La structure `Pixel` encode chaque couleur sur 3 `unsigned char` (RGB), ce qui limite l'empreinte mémoire par rapport à des `int`.
- La documentation complète (choix d'implémentation, fonctions détaillées, ressources consultées) est disponible dans `Documentation projet morphing en C.pdf`.

## Auteure

Laetitia ALIOUI — L2 Informatique, UVSQ (Université Paris-Saclay)
