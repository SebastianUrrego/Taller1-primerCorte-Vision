# Taller 1 Electiva Visión por Computador
**Universidad Sergio Arboleda**

## Requisitos
- OpenCV 4.12
- c++ / CMake

## Compilación

### Opción 1 — g++ directo
```bash
g++ ejercicio1.cpp  -o ejercicio1  `pkg-config --cflags --libs opencv4`
g++ ejercicio2a.cpp -o ejercicio2a `pkg-config --cflags --libs opencv4`
g++ ejercicio2b.cpp -o ejercicio2b `pkg-config --cflags --libs opencv4`
g++ ejercicio3a.cpp -o ejercicio3a `pkg-config --cflags --libs opencv4`
g++ ejercicio3b.cpp -o ejercicio3b `pkg-config --cflags --libs opencv4`
g++ ejercicio4a.cpp -o ejercicio4a `pkg-config --cflags --libs opencv4`
g++ ejercicio4b.cpp -o ejercicio4b `pkg-config --cflags --libs opencv4`
```

### Opción 2 — CMake
```bash
mkdir build && cd build
cmake ..
make
```

---

## Ejercicio 1 — 6 imágenes en una ventana

**Descripción:** Muestra 6 imágenes en una sola ventana organizada en 2 filas de 3. La fila superior muestra las imágenes en color y la inferior en escala de grises.

**Operaciones usadas:**
- `cvtColor` — conversión de color BGR a gris
- `resize` — redimensionar imágenes al mismo tamaño
- `hconcat` / `vconcat` — concatenar imágenes horizontal y verticalmente

**Uso:**
```bash
./ejercicio1
```
> Edita la lista `imagePaths` en el código para usar tus propias imágenes.

---

## Ejercicio 2A — Región 100×100 en escala de grises

**Descripción:** Convierte una región central de 100×100 píxeles a escala de grises sin usar máscara externa. El resto de la imagen permanece en color.

**Operaciones usadas:**
- **Matemática:** Fórmula de luminancia píxel a píxel:
  `gris = 0.299×R + 0.587×G + 0.114×B`

**Uso:**
```bash
./ejercicio2a lena.png
```

---

## Ejercicio 2B — Binarización de región con umbral 127

**Descripción:** Sobre la imagen del ejercicio 2A, binariza únicamente la región de 100×100 con umbral 127. El resto de la imagen no se modifica.

**Operaciones usadas:**
- **Matemática:** Umbralización manual píxel a píxel:
  `si valor > 127 → 255 (blanco), si no → 0 (negro)`

**Uso:**
```bash
./ejercicio2b lena.png
```

---

## Ejercicio 3A — Detección del triceratops (imagen diferencia)

**Descripción:** A partir de imagen(a) que contiene el triceratops e imagen(b) sin él, genera imagen(c) que es la diferencia absoluta entre ambas, revelando el triceratops.

**Operaciones usadas:**
- **Matemática:** `absdiff(grayA, grayB)` — diferencia absoluta entre las dos imágenes en escala de grises

**Uso:**
```bash
./ejercicio3a imagen_a.jpg imagen_b.jpg
```
**Salida:** `output_ejercicio3a.png`

---

## Ejercicio 3B — Centro de masa del triceratops (bounding box)

**Descripción:** Toma imagen(c) del ejercicio 3A y calcula el centro de masa del triceratops usando el método de caja englobante (bounding box).

**Operaciones usadas:**
- **Matemática:** `threshold` con umbral 10 para binarizar la imagen diferencia
- **Geométrica:** `boundingRect` sobre el contorno más grande:
  `cx = x + w/2`, `cy = y + h/2`

**Uso:**
```bash
./ejercicio3b output_ejercicio3a.png
```
**Salida en consola:**
```
Bounding Box: x=120 y=180 w=250 h=200
Centro de masa del triceratops: (245, 280)
```
**Salida:** `output_ejercicio3b.png`

---

## Ejercicio 4A — Triceratops en colores grises originales

**Descripción:** Genera imagen(c) donde aparece únicamente el triceratops con sus valores de gris originales de imagen(a), sobre fondo negro. Usa morfología para limpiar el ruido antes de extraer la región.

**Operaciones usadas:**
- **Matemática:** `absdiff` + `threshold` con umbral 10
- **Morfológica — MORPH_OPEN** (kernel elíptico 15×15): erosión seguida de dilatación; elimina píxeles de ruido pequeños dispersos (fantasmas del tiranosaurio y estegosaurio)
- **Morfológica — MORPH_CLOSE** (kernel elíptico 15×15): dilatación seguida de erosión; une los píxeles del cuerpo del triceratops en una sola región sólida
- `boundingRect` para extraer la región completa con su fondo gris original

**Uso:**
```bash
./ejercicio4a imagen_a.jpg imagen_b.jpg
```
**Salida:** `output_ejercicio4a.png`

---

## Ejercicio 4B — Centro de masa del triceratops en gris (bounding box)

**Descripción:** Toma imagen(c) del ejercicio 4A y calcula el centro de masa del triceratops en sus colores grises originales usando bounding box. Dibuja el rectángulo en verde y el centro en rojo.

**Operaciones usadas:**
- **Matemática:** `threshold` con umbral 10
- **Geométrica:** `boundingRect` sobre el contorno más grande:
  `cx = x + w/2`, `cy = y + h/2`

**Uso:**
```bash
./ejercicio4b output_ejercicio4a.png
```
**Salida en consola:**
```
Bounding Box: x=... y=... w=... h=...
Centro de masa del triceratops: (x, y)
```
**Salida:** `output_ejercicio4b.png`

---

## Resumen de operaciones por ejercicio

| Ejercicio | Operación matemática | Operación morfológica |
|-----------|---------------------|-----------------------|
| 1A | — | — |
| 2A | Luminancia: 0.299R + 0.587G + 0.114B | — |
| 2B | Umbral manual: valor > 127 → 255 | — |
| 3A | absdiff | — |
| 3B | threshold + boundingRect | — |
| 4A | absdiff + threshold | MORPH_OPEN + MORPH_CLOSE |
| 4B | threshold + boundingRect | — |
