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
1.png          — imagen para punto 1
2.png          — imagen para punto 1
3.png          — imagen para punto 1
imA.png        — imagen con triceratops (puntos 3 y 4)
imB.png        — imagen sin triceratops (puntos 3 y 4)
```

---

## Punto 1 — 6 imágenes en una ventana

**Descripción:** Muestra 6 imágenes en una sola ventana organizada en 2 filas de 3. La fila superior muestra las imágenes originales en color. La fila inferior muestra: imagen en gris, imagen con brillo aumentado, e imagen con gradiente morfológico.

**Operaciones matemáticas:**
- `convertTo(img5, -1, 1.5, 100)` — ajuste de brillo: multiplica cada píxel por 1.5 y suma 100

**Operaciones morfológicas:**
- `MORPH_GRADIENT` con kernel rectangular 3×3 — diferencia entre dilatación y erosión, resalta bordes

---

## Punto 2A — Región 300×300 en escala de grises

**Descripción:** Convierte una región central de 300×300 píxeles a escala de grises. El resto de la imagen permanece en color. Guarda el resultado como `imagenB.png`.

**Operaciones matemáticas:**
- `cvtColor(COLOR_BGR2GRAY)` — conversión usando fórmula de luminancia: `gris = 0.299×R + 0.587×G + 0.114×B`

**Operaciones morfológicas:** ninguna.

**Archivos generados:** `../Data/imagenB.png`

---

## Punto 2B — Binarización de región con umbral 127

**Descripción:** Lee `imagenB.png` y binariza únicamente la región de 300×300 con umbral 127. El resto de la imagen no se modifica.

**Operaciones matemáticas:**
- `threshold(gray, gray, 127, 255, THRESH_BINARY)` — comparación píxel a píxel: `si valor > 127 → 255 (blanco), si no → 0 (negro)`

**Operaciones morfológicas:** ninguna.

---

## Punto 3A — Detección del triceratops (imagen diferencia)

**Descripción:** A partir de imagen(a) con triceratops e imagen(b) sin él, genera imagen(c) que es la diferencia absoluta entre ambas, revelando el triceratops sobre fondo oscuro.

**Operaciones matemáticas:**
- `absdiff(grayA, grayB)` — diferencia absoluta píxel a píxel: `|A - B|`

**Operaciones morfológicas:** ninguna.

**Archivos generados:** `../Data/output-punto3a.png`

---

## Punto 3B — Centro de masa del triceratops (bounding box)

**Descripción:** Lee imagen(c) del punto 3A y calcula el centro de masa del triceratops usando el método de caja englobante (bounding box). Dibuja el rectángulo en verde y el centro en rojo sobre la imagen.

**Operaciones matemáticas:**
- `threshold(imgC, binary, 10, 255, THRESH_BINARY)` — umbralización fija para binarizar
- `cx = bbox.x + bbox.width / 2` y `cy = bbox.y + bbox.height / 2` — cálculo del centro del bounding box

**Operaciones morfológicas:** ninguna.

**Salida en consola:**
```
Punto 3B - Bounding Box: x=... y=... w=... h=...
Punto 3B - Centro de masa: (x, y)
```
**Archivos generados:** `../Data/output-punto3b.png`

---

## Punto 4A — Triceratops en colores grises originales

**Descripción:** Genera imagen(c) donde aparece únicamente el triceratops con sus valores de gris originales de imagen(a), sobre fondo blanco. Usa OTSU para calcular automáticamente el mejor umbral y `drawContours` para aislar solo el triceratops descartando los otros dinosaurios.

**Operaciones matemáticas:**
- `absdiff(grayA, grayB)` — diferencia absoluta para detectar qué cambió entre A y B
- `threshold(diferencia, mascara, 0, 255, THRESH_BINARY + THRESH_OTSU)` — umbral automático OTSU: analiza el histograma y calcula el umbral óptimo automáticamente
- `drawContours(..., FILLED)` — rellena el contorno más grande para crear máscara limpia del triceratops
- `grayA.copyTo(imgC, mascaraLimpia)` — copia los grises originales de imgA usando la máscara

**Operaciones morfológicas:** ninguna.

**Archivos generados:** `../Data/output-punto4a.png`

---

## Punto 4B — Centro de masa en grises originales (bounding box)

**Descripción:** Lee imagen(c) del punto 4A y calcula el centro de masa del triceratops usando bounding box. Como la imagen tiene fondo blanco y el triceratops es oscuro, se usa umbral invertido. Dibuja el bounding box en verde y el centro en rojo sobre la imagen en grises originales.

**Operaciones matemáticas:**
- `threshold(imgC, binaria, 127, 255, THRESH_BINARY_INV)` — umbral invertido: triceratops oscuro (<127) → blanco, fondo blanco (255) → negro
- `cx = caja.x + caja.width / 2` y `cy = caja.y + caja.height / 2` — cálculo del centro del bounding box

**Operaciones morfológicas:** ninguna.

**Salida en consola:**
```
Punto 4B - Bounding Box: x=... y=... w=... h=...
Punto 4B - Centro de masa (Bounding Box): (x, y)
```

---

## Resumen de operaciones

| Punto | Operación matemática | Operación morfológica |
|-------|---------------------|-----------------------|
| 1 | `convertTo` (brillo: ×1.5 +100) | `MORPH_GRADIENT` kernel rect 3×3 |
| 2A | `cvtColor` (luminancia: 0.299R+0.587G+0.114B) | — |
| 2B | `threshold` umbral fijo 127 | — |
| 3A | `absdiff` | — |
| 3B | `threshold` fijo 10 + centro del bbox | — |
| 4A | `absdiff` + `threshold OTSU` + `drawContours` | — |
| 4B | `threshold` invertido 127 + centro del bbox | — |
