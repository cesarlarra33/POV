from PIL import Image, ImageOps
import math
import os

# ================= CONFIGURATION =================
IMAGE_ENTREE = "coeur.jpg"
FICHIER_C = "image_pattern.c"

# REGLAGES
RESOLUTION_ANGLE = 3.5   
NB_LEDS = 16
ZOOM = 0.90

# LOGIQUE COULEUR
IMAGE_INVERSEE = True      
SEUIL = 128

MASK_EXTERIEUR_EN_PREMIER = True 

# =================================================

def generer():
    print("--- Démarrage ---")
    
    # Chargement image
    try:
        raw_img = Image.open(IMAGE_ENTREE).convert("L")
    except:
        print(f"ERREUR: Impossible d'ouvrir {IMAGE_ENTREE}")
        return

    if IMAGE_INVERSEE:
        raw_img = ImageOps.invert(raw_img)

    # Resize carré
    img = raw_img.resize((500, 500))
    width, height = img.size
    center_x = width // 2
    center_y = height // 2
    rayon_max = (width // 2) * ZOOM

    # Génération C
    c_output = []
    c_output.append(f"// Généré automatiquement depuis {IMAGE_ENTREE}")
    c_output.append(f'#include "utils.h"')
    c_output.append(f'#include "image.h"')
    c_output.append("const pattern_t image_pattern[] PROGMEM = {")

    angle_deg = 0.0
    while angle_deg < 360.0:

        # Conversion angle
        angle_rad = math.radians(angle_deg - 90)

        # Direction
        vec_x = math.cos(angle_rad)
        vec_y = math.sin(angle_rad)

        leds_state = []

        # Scan radial 16 LED
        for i in range(NB_LEDS):

            dist = (i + 1) / float(NB_LEDS)
            
            px = int(center_x + (vec_x * dist * rayon_max))
            py = int(center_y + (vec_y * dist * rayon_max))

            px = max(0, min(px, width-1))
            py = max(0, min(py, height-1))
            
            val = img.getpixel((px, py))
            is_on = val > SEUIL
            leds_state.append(1 if is_on else 0)

        # Inversion si extérieur d'abord
        if MASK_EXTERIEUR_EN_PREMIER:
            final_bits = leds_state[::-1]
        else:
            final_bits = leds_state

        str_bits = ",".join(str(b) for b in final_bits)

        # Sortie C
        line = f"    {{ .angle = {angle_deg:.2f}F, .mask = MASK16({str_bits}) }},"
        c_output.append(line)

        angle_deg += RESOLUTION_ANGLE

    c_output.append("};")
    c_output.append("const int IMAGE_PATTERN_SIZE = (int)(sizeof(image_pattern) / sizeof(image_pattern[0]));")

    # Écriture du fichier C
    with open(FICHIER_C, "w") as f:
        f.write("\n".join(c_output))
    
    print("--- TERMINE ---")


if __name__ == "__main__":
    generer()