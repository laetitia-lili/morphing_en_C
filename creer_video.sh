#!/bin/bash

# Script pour créer une vidéo à partir des images de morphing
# Usage: ./creer_video.sh [fps]

FPS=${1:-10}  # 10 images par seconde par défaut

echo "=== Création de la vidéo de morphing ==="
echo "FPS: $FPS"
echo ""

# vérifier que le dossier images_out contient des images
if [ ! -d "images_out" ] || [ -z "$(ls -A images_out/*.ppm 2>/dev/null)" ]; then
    echo "Erreur: Aucune image trouvée dans images_out/"
    echo "Générez d'abord les images avec: ./generer_morphing"
    exit 1
fi

#compter le nombre d'images
NB_IMAGES=$(ls -1 images_out/morphing_*.ppm 2>/dev/null | wc -l)
echo "Nombre d'images trouvées: $NB_IMAGES"

if [ $NB_IMAGES -eq 0 ]; then
    echo "Erreur: Aucune image de morphing trouvée"
    exit 1
fi

# créer la vidéo avec ffmpeg
echo ""
echo "Création de la vidéo..."

ffmpeg -y -framerate $FPS -i images_out/morphing_%02d.ppm \-vf "pad=ceil(iw/2)*2:ceil(ih/2)*2" \-c:v libx264 -pix_fmt yuv420p -crf 23 \morphing.mp4

if [ $? -eq 0 ]; then
    echo ""
    echo "✓ Vidéo créée avec succès: morphing.mp4"
    ls -lh morphing.mp4
    echo ""
    echo "Pour lire la vidéo: open morphing.mp4"
else
    echo ""
    echo "✗ Erreur lors de la création de la vidéo"
    exit 1
fi