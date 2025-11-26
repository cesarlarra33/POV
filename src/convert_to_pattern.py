from PIL import Image

def image_to_c_pattern_highres(image_path, c_file_path, led_count=16, cols=64, threshold=128):
    """
    Convertit une image en pattern POV avec plus de colonnes pour plus de précision
    """
    img = Image.open(image_path).convert("L")
    # Redimensionner verticalement et horizontalement
    img = img.resize((cols, led_count))
    pixels = img.load()

    patterns = []
    for x in range(cols):
        byte1 = 0
        byte2 = 0
        for y in range(led_count):
            bit = 1 if pixels[x, y] < threshold else 0
            if y < 8:
                byte1 |= bit << (7 - y)
            else:
                byte2 |= bit << (7 - (y - 8))
        patterns.append((byte1, byte2))

    with open(c_file_path, "w") as f:
        f.write("typedef struct {\n    uint8_t buffer[2];\n    uint16_t angle;\n} pattern_t;\n\n")
        f.write(f"pattern_t pattern_dict[{cols}] = {{\n")
        for i, (b1, b2) in enumerate(patterns):
            angle = i * 360 // cols
            f.write(f"    {{ {{0x{b1:02X}, 0x{b2:02X}}}, {angle} }},\n")
        f.write("};\n")
    print(f"Pattern POV généré avec {cols} colonnes : {c_file_path}")

# Exemple d'utilisation
image_to_c_pattern_highres("smiley.png", "pattern_highres.c", led_count=16, cols=64)
