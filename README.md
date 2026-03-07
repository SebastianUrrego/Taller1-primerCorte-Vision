# Taller Electiva Visión por Computador
**Universidad Sergio Arboleda**

## Requisitos
- OpenCV 4.x
- g++ / CMake

## Compilación

### Opción 1 — g++ directo (archivo único)
```bash
g++ taller_completo.cpp -o taller `pkg-config --cflags --libs opencv4`
./taller
```

### Opción 2 — CMake
```bash
mkdir build && cd build
cmake ..
make
```

### Archivos de imágenes necesarios en carpeta `../Data/`
```
1.png      — imagen para punto 1
2.png      — imagen para punto 1
3.png      — imagen para punto 1
imA.png    — imagen con triceratops (puntos 3 y 4)
imB.png    — imagen sin triceratops (puntos 3 y 4)
```

---

## Punto 1 — 6 imágenes en una ventana

**Descripción:** Muestra 6 imágenes en una sola ventana en 2 filas de 3. Fila superior: imágenes originales en color. Fila inferior: imagen en gris, imagen con brillo aumentado, imagen con gradiente morfológico.

**Técnicas usadas:**
- **Conversión de color** `cvtColor` — BGR a escala de grises usando luminancia
- **Ajuste de brillo** `convertTo` — multiplica cada píxel por 1.5 y suma 100
- **Gradiente morfológico** `MORPH_GRADIENT` con kernel rectangular 3×3 — diferencia entre dilatación y erosión, resalta bordes
- **Concatenación** `hconcat` / `vconcat` — une imágenes horizontal y verticalmente

---

## Punto 2A — Región 300×300 en escala de grises

**Descripción:** Convierte una región central de 300×300 píxeles a escala de grises. El resto de la imagen permanece en color. Guarda el resultado como `imagenB.png`.

**Técnicas usadas:**
- **ROI (Region of Interest)** — selección de región central de 300×300
- **Conversión de luminancia** `cvtColor` — fórmula `gris = 0.299×R + 0.587×G + 0.114×B`

**Archivos generados:** `../Data/imagenB.png`

---

## Punto 2B — Binarización de región con umbral 127

**Descripción:** Lee `imagenB.png` y binariza únicamente la región de 300×300 con umbral 127. El resto de la imagen no se modifica.

**Técnicas usadas:**
- **Umbralización fija** `threshold` umbral 127 — `THRESH_BINARY`: píxeles > 127 → 255 (blanco), resto → 0 (negro)

---

## Punto 3A — Detección del triceratops (imagen diferencia)

**Descripción:** A partir de imagen(a) con triceratops e imagen(b) sin él, genera imagen(c) que es la diferencia absoluta entre ambas, revelando el triceratops.

**Técnicas usadas:**
- **Diferencia absoluta** `absdiff` — operación matemática píxel a píxel: `|A - B|`

**Archivos generados:** `../Data/output-punto3a.png`

---

## Punto 3B — Centro de masa del triceratops (bounding box)

**Descripción:** Lee imagen(c) del punto 3A, limpia el ruido y la sombra con morfología, y calcula el centro de masa del triceratops usando bounding box.

**Técnicas usadas:**
- **Umbralización fija** `threshold` umbral 80 — `THRESH_BINARY` para eliminar sombras y ruido
- **Morfología MORPH_OPEN** kernel elíptico 9×9 — erosión + dilatación, elimina píxeles de ruido pequeños dispersos
- **Morfología MORPH_CLOSE** kernel elíptico 9×9 — dilatación + erosión, rellena huecos internos del triceratops
- **Detección de contornos** `findContours` — encuentra regiones conectadas
- **Caja englobante** `boundingRect` — rectángulo mínimo que encierra el contorno más grande
- **Centro de masa** `cx = x + w/2`, `cy = y + h/2` — centro geométrico del bounding box

**Salida en consola:**
```
Punto 3B - Bounding Box: x=... y=... w=... h=...
Punto 3B - Centro de masa: (x, y)
```
**Archivos generados:** `../Data/output-punto3b.png`

---

## Punto 4A — Triceratops en grises originales + siluetas otros dinosaurios

**Descripción:** Genera imagen(c) usando división de imágenes. El triceratops aparece oscuro con sus grises originales. Los otros dos dinosaurios aparecen como siluetas tenues ya que sus píxeles son similares en A y B.

**Técnicas usadas:**
- **Conversión a float** `convertTo(CV_32F)` — necesario para hacer división sin pérdida de precisión
- **División de imágenes** `divide(imgAf × 255, imgBf)`:
  - Donde triceratops oscuro en A / fondo claro en B → valor pequeño → **oscuro**
  - Donde fondo/otros dinosaurios similares en A y B → valor ≈ 255 → **blanco/gris claro**
- **Clamp** `min(divResult, 255)` — limita valores al rango [0, 255]

**Archivos generados:** `../Data/output-punto4a.png`

---

## Punto 4B — Centro de masa en grises originales (bounding box)

**Descripción:** Lee imagen(c) del punto 4A y calcula el centro de masa del triceratops usando bounding box. Como la imagen tiene fondo blanco y el triceratops es oscuro, se usa umbral invertido.

**Técnicas usadas:**
- **Umbralización invertida** `THRESH_BINARY_INV` umbral 200 — triceratops oscuro (<200) → blanco, fondo blanco → negro
- **Morfología MORPH_CLOSE** kernel rectangular 5×5 — une la región del triceratops
- **Detección de contornos** `findContours`
- **Caja englobante** `boundingRect`
- **Centro de masa** `cx = x + w/2`, `cy = y + h/2`

**Salida en consola:**
```
Punto 4B - Bounding Box: x=... y=... w=... h=...
Punto 4B - Centro de masa (Bounding Box): (x, y)
```

---

## Resumen de técnicas

| Punto | Técnica matemática | Técnica morfológica |
|-------|--------------------|---------------------|
| 1 | Ajuste de brillo (×1.5 +100) | MORPH_GRADIENT kernel rect 3×3 |
| 2A | Luminancia (0.299R+0.587G+0.114B) | — |
| 2B | Umbral fijo 127 | — |
| 3A | absdiff \|A-B\| | — |
| 3B | Umbral fijo 80 | MORPH_OPEN + MORPH_CLOSE kernel elíptico 9×9 |
| 4A | División A/B × 255 | — |
| 4B | Umbral invertido 200 | MORPH_CLOSE kernel rect 5×5 |
