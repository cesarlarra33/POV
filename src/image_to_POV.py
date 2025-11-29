from PIL import Image, ImageDraw, ImageOps
import math
import os

# ================= CONFIGURATION =================
IMAGE_ENTREE = "coeur.jpg"
FICHIER_C = "heart_pattern.h"
IMAGE_DEBUG = "DEBUG_VISUALISATION.png"

# REGLAGES
RESOLUTION_ANGLE = 4    # Un trait tous les 2 degrés
NB_LEDS = 16
ZOOM = 0.90             # 1.0 = Bord à bord. Si le coeur est coupé, mettre 0.9

# LOGIQUE COULEUR
# True = Le coeur est NOIR sur fond BLANC
# False = Le coeur est BLANC sur fond NOIR
IMAGE_INVERSEE = True      
SEUIL = 128                # Niveau de gris pour décider noir/blanc

# LOGIQUE MATERIEL (Ta demande spécifique)
# True = MASK16(LED_EXTERIEURE, ..., LED_CENTRE)
MASK_EXTERIEUR_EN_PREMIER = True 

# =================================================

def generer():
    print("--- Démarrage ---")
    
    # 1. Charger et forcer l'image en carré pour éviter les déformations
    try:
        raw_img = Image.open(IMAGE_ENTREE).convert("L") # Niveaux de gris
    except:
        print(f"ERREUR: Impossible d'ouvrir {IMAGE_ENTREE}")
        return

    # On inverse si besoin pour travailler avec du Blanc (Allumé) sur Noir (Eteint)
    if IMAGE_INVERSEE:
        raw_img = ImageOps.invert(raw_img)

    # On redimensionne en carré propre (500x500)
    img = raw_img.resize((500, 500))
    width, height = img.size
    center_x = width // 2
    center_y = height // 2
    rayon_max = (width // 2) * ZOOM

    # Image de debug (On reprend l'originale pour dessiner dessus)
    debug_img = img.convert("RGB")
    draw = ImageDraw.Draw(debug_img)

    c_output = []
    c_output.append(f"// Généré automatiquement depuis {IMAGE_ENTREE}")
    c_output.append(f'#include "utils.h"')
    c_output.append("const pattern_t heart_pattern[] PROGMEM = {")

    # 2. SCAN
    for angle_deg in range(0, 360, RESOLUTION_ANGLE):
        
        # Conversion Angle POV (0° en Haut) vers Trigo
        # Le -90 sert à mettre le 0° en haut (Midi)
        angle_rad = math.radians(angle_deg - 90)
        
        # Sens Horaire
        vec_x = math.cos(angle_rad)
        vec_y = math.sin(angle_rad)

        leds_state = []

        # Boucle LED 0 (Centre) vers LED 15 (Bord)
        for i in range(NB_LEDS):
            # Calcul de la position du pixel pour cette LED
            # i=0 -> dist proche de 0
            # i=15 -> dist proche de 1.0
            dist = (i + 1) / float(NB_LEDS)
            
            px = int(center_x + (vec_x * dist * rayon_max))
            py = int(center_y + (vec_y * dist * rayon_max))

            # Lecture Pixel
            # On s'assure de ne pas sortir de l'image
            px = max(0, min(px, width-1))
            py = max(0, min(py, height-1))
            
            val = img.getpixel((px, py))
            
            # > SEUIL car on a inversé l'image au début (donc coeur est blanc/lumineux)
            is_on = val > SEUIL
            
            leds_state.append(1 if is_on else 0)

            # DESSIN DEBUG
            # Vert = LED Allumée / Rouge = LED Eteinte
            color = (0, 255, 0) if is_on else (255, 0, 0)
            # On dessine un petit rond
            r = 2
            draw.ellipse((px-r, py-r, px+r, py+r), fill=color)

        # 3. FORMATAGE SORTIE
        # Si ta macro MASK16 attend l'extérieur en premier argument
        # leds_state est actuellement [CENTRE, ..., EXTERIEUR]
        # Il faut donc inverser la liste
        if MASK_EXTERIEUR_EN_PREMIER:
            final_bits = leds_state[::-1]
        else:
            final_bits = leds_state

        str_bits = ",".join(str(b) for b in final_bits)
        
        # Syntaxe exacte demandée
        line = f"    {{ .angle = {angle_deg}U, .mask = MASK16({str_bits}) }},"
        c_output.append(line)

    c_output.append("};")
    c_output.append(f"const int HEART_PATTERN_SIZE = (int)(sizeof(heart_pattern) / sizeof(heart_pattern[0]));")

    # 4. ECRITURE
    with open(FICHIER_C, "w") as f:
        f.write("\n".join(c_output))
    
    debug_img.save(IMAGE_DEBUG)
    
    print("--- TERMINE ---")

if __name__ == "__main__":
    generer()