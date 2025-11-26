import math
from PIL import Image, ImageDraw

# ==========================================
#              CONFIGURATION
# ==========================================
IMAGE_PATH = "coeur.jpg"  
OUTPUT_C_FILE = "heart_pattern.c"
OUTPUT_PREVIEW = "preview_final.png"

NUM_LEDS = 16
THRESHOLD = 250   # < 128 = Allumé (Noir)

# ZOOM : Augmente si le coeur fait une "boule" (ex: 1.3 ou 1.5)
ZOOM_FACTOR = 1.3 

# ROTATION : Pour remettre le coeur droit !
# Si le coeur s'affiche à 90° (à droite), mets -90 ici.
# Si le coeur s'affiche en bas, mets 180.
ROTATION_OFFSET = 0 

# ORDRE DES BITS (Calibration faite avec le diamant)
# Si True : MASK16(Exterieur, ..., Interieur/Centre)
# On met True car ton diamant s'affichait au centre avec le bit de fin.
INVERT_ORDER = True 

# ==========================================

def generate_final(image_path):
    try:
        img = Image.open(image_path).convert('L')
    except FileNotFoundError:
        print("Erreur: Image 'coeur.png' introuvable.")
        return

    width, height = img.size
    center_x = width // 2
    center_y = height // 2
    # Rayon max ajusté par le zoom
    max_radius = (min(center_x, center_y) - 1) / ZOOM_FACTOR
    
    # Préparation de la preview
    preview_img = Image.new('RGB', (600, 600), (0, 0, 0))
    draw = ImageDraw.Draw(preview_img)
    p_center = 300
    p_scale = 280
    
    c_patterns = []

    print(f"Génération en cours avec Rotation {ROTATION_OFFSET}°...")

    for angle_deg in range(360):
        led_states = [] 
        
        # 1. Calcul de l'angle pour lire l'image SOURCE
        # On applique l'OFFSET ici pour tourner l'image virtuellement
        # On ajoute -90 car en maths 0° = Droite, mais en horloge 0° = Haut
        read_angle = angle_deg - 90 - ROTATION_OFFSET
        angle_rad = math.radians(read_angle)
        
        # 2. Angle pour le dessin de la PREVIEW (Simulation visuelle)
        # Pour la preview, on veut voir ce que ça donnera avec 0° en haut
        preview_rad = math.radians(angle_deg - 90)

        for led_idx in range(NUM_LEDS):
            # led_idx 0 = Centre de l'image source
            r_source = (led_idx / NUM_LEDS) * max_radius
            
            x = int(center_x + r_source * math.cos(angle_rad))
            y = int(center_y + r_source * math.sin(angle_rad))
            
            state = 0
            if 0 <= x < width and 0 <= y < height:
                if img.getpixel((x, y)) < THRESHOLD:
                    state = 1
                    
                    # Dessin sur la preview pour vérifier
                    r_p = (led_idx / NUM_LEDS) * p_scale
                    px = int(p_center + r_p * math.cos(preview_rad))
                    py = int(p_center + r_p * math.sin(preview_rad))
                    draw.point((px, py), fill=(255, 50, 50)) # Rouge

            led_states.append(state)

        # 3. Application de l'ordre des bits (Hardware)
        # Si ton diamant (bit de fin) était au centre, alors 
        # la liste [Centre ... Exterieur] doit être inversée.
        if INVERT_ORDER:
            led_states.reverse()
        
        # 4. Génération de la ligne C
        mask_str = ", ".join(map(str, led_states))
        line = f"    {{ .angle = {angle_deg}U, .mask = MASK16({mask_str}) }}"
        c_patterns.append(line)

    # Ecriture du fichier C
    content = (
        f"// Genere avec Rotation {ROTATION_OFFSET}\n"
        f"#include \"clock_template.h\"\n\n"
        f"const pattern_t heart_pattern[] PROGMEM = {{\n"
    )
    content += ",\n".join(c_patterns)
    content += "\n};"
    content +=f"\n\nconst int HEART_PATTERN_SIZE = (int)(sizeof(heart_pattern) / sizeof(heart_pattern[0]));"
    
    with open(OUTPUT_C_FILE, "w") as f:
        f.write(content)
        
    preview_img.save(OUTPUT_PREVIEW)
    print("TERMINE ! Regarde 'preview_final.png'.")

if __name__ == "__main__":
    generate_final(IMAGE_PATH)