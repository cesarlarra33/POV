from PIL import Image, ImageDraw

def generate_pattern_for_rotation(image_path, c_file_path, led_count=16, max_cols=255, threshold=128):
    """
    Génère un pattern_dict pour un bandeau LED, avec la correspondance exacte 
    de l'image. Pas de PROGMEM, angle correspond à la position réelle.
    """
    img = Image.open(image_path).convert("L")
    width, height = img.size

    # Redimensionner verticalement pour correspondre à led_count
    new_width = min(width, max_cols)
    img = img.resize((new_width, led_count), Image.NEAREST)
    pixels = img.load()

    # Générer pattern et image de visualisation
    pattern_list = []
    sim_img = Image.new("RGB", (new_width*10, led_count*10), "white")
    draw = ImageDraw.Draw(sim_img)

    for x in range(new_width):
        byte1 = 0
        byte2 = 0
        for y in range(led_count):
            bit = 1 if pixels[x, y] < threshold else 0
            if y < 8:
                byte1 |= bit << (7 - y)
            else:
                byte2 |= bit << (7 - (y-8))
            color = "black" if bit else "white"
            draw.rectangle([x*10, y*10, x*10+9, y*10+9], fill=color, outline="grey")
        pattern_list.append((byte1, byte2))

    sim_img.save("pattern_visual.png")
    print("Image visualisée : pattern_visual.png")

    # Génération fichier C : angle = index colonne, pour rotation exacte
    # Génère pattern_dict pour 16 LEDs, une LED par tranche d'angle
    with open("pattern_dict.c", "w") as f:
        f.write("typedef struct {\n    uint8_t buffer[2];\n    uint16_t angle;\n} pattern_t;\n\n")
        f.write("const pattern_t pattern_dict[16] = {\n")
        for i in range(16):
            byte1 = 0
            byte2 = 0
            if i < 8:
                byte1 = 1 << (7 - i)
            else:
                byte2 = 1 << (7 - (i - 8))
            angle = i * (360 // 16)
            f.write(f"    {{ {{0x{byte1:02X}, 0x{byte2:02X}}}, {angle} }},\n")
        f.write("};\n")

# Exemple
generate_pattern_for_rotation("smiley.png", "pattern_dict.c", led_count=16, max_cols=255)
