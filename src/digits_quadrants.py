#!/usr/bin/env python3
import os
import math
from PIL import Image, ImageOps, ImageFilter

# ---------------------------------------------------------------------------
# PARAMÈTRES GLOBAUX
# ---------------------------------------------------------------------------

# Doit correspondre à THETA_RESOLUTION dans ton C et être divisible par 4.
IMG_SIZE = 120        # <--- pas trop elevé si non trop lourd
SEUIL = 128
PADDING_RATIO = 0.15
LED_COUNT = 16
ZOOM = 0.95

N = IMG_SIZE          # nombre de pas angulaires
# ---------------------------------------------------------------------------
# GÉNÉRATION DE src/digits.c (MODE BATCH UNIQUEMENT)
# ---------------------------------------------------------------------------

digits_c_path = os.path.join("src", "digits.c")
os.makedirs(os.path.dirname(digits_c_path), exist_ok=True)

with open(digits_c_path, "w") as f:
    f.write('// Fichier généré automatiquement : buffers polaires pour chaque chiffre et chaque quart\n')
    f.write('#include "pattern.h"\n\n')

    if N % 4 != 0:
        raise ValueError(f"IMG_SIZE (= {N}) doit être divisible par 4")
quart_size = N // 4

    for digit in range(10):
        img_path = f"img/{digit}.png"
        if not os.path.exists(img_path):
            print(f"[WARN] Pas d'image pour le digit {digit} : {img_path}, je le saute.")
            continue

        # 1) Chargement & prétraitement
        img = Image.open(img_path).convert("L")
        img = ImageOps.invert(img)
        img = img.filter(ImageFilter.GaussianBlur(0.5))
        img = img.point(lambda p: 255 if p > SEUIL else 0)

        # 2) 4 quadrants identiques
        quarter_img = img.resize((IMG_SIZE // 2, IMG_SIZE // 2))
        canvas_all = Image.new("L", (IMG_SIZE, IMG_SIZE), 0)
 canvas_all.paste(quarter_img, (0, 0))
        canvas_all.paste(quarter_img, (IMG_SIZE // 2, 0))
        canvas_all.paste(quarter_img, (0, IMG_SIZE // 2))
        canvas_all.paste(quarter_img, (IMG_SIZE // 2, IMG_SIZE // 2))

        # 3) Padding
        pad = int(IMG_SIZE * PADDING_RATIO)
        padded_size = IMG_SIZE + 2 * pad
        canvas_padded = Image.new("L", (padded_size, padded_size), 0)
        canvas_padded.paste(canvas_all, (pad, pad))

        cx = padded_size // 2
        cy = padded_size // 2

        # 4) Échantillonnage polaire : on ne garde ici que
 #    les angles "d'origine" pour debug, mais on ne les
        #    réutilise PAS pour la sortie finale.
        buffers_polar = []
        for i in range(N):
            angle_raw = i * 360.0 / N
            angle = int(round(angle_raw))
            if angle >= 360:
                angle -= 360

            mask = 0
            for led in range(LED_COUNT):
                r = (led + 1) / LED_COUNT * (padded_size // 2) * ZOOM
                x = int(cx + r * math.cos(math.radians(angle)))
                y = int(cy - r * math.sin(math.radians(angle)))
                if 0 <= x < padded_size and 0 <= y < padded_size:
                    if canvas_padded.getpixel((x, y)) == 255:
                        mask |= (1 << led)
   buffers_polar.append((angle, mask))

        # Debug minimal
        for idx in [0, quart_size, 2 * quart_size, 3 * quart_size, N - 1]:
            a, _ = buffers_polar[idx]
            print(f"[DEBUG] digit={digit}, idx={idx}, angle_orig={a}")


        src_quarts = [1, 2, 3, 0]          # indices source
        out_names = ['Q1', 'Q2', 'Q3', 'Q4']

        for out_idx, src_idx in enumerate(src_quarts):
            name = out_names[out_idx]
            f.write(f"const pattern_t number_{digit}_{name}[{quart_size}] PROGMEM = {{\n")
           start = src_idx * quart_size
            end = start + quart_size

            for i, (_, mask) in enumerate(buffers_polar[start:end]):
                global_idx = out_idx * quart_size + i
                angle_out = int(round(global_idx * 360.0 / N))
                if angle_out >= 360:
                    angle_out -= 360

                bits_list = [str((mask >> b) & 1) for b in reversed(range(LED_COUNT))]
                bits_str = ','.join(bits_list)
                f.write(
                    f"    {{.angle = {angle_out:3d}U, .mask = MASK16({bits_str})}},\n"
                )

            f.write("};\n\n")

print(f"[OK] digits.c généré : {digits_c_path}")