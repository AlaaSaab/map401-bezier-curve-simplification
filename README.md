# MAP401 — Contour Extraction & Simplification (C)

Processing and vectorization pipeline for black–white images in **PBM** format:
1) extract pixel **contours**,  
2) optionally **simplify** them with **Douglas–Peucker** or fit **Bézier** curves (quadratic/cubic),  
3) **export** vector output as **EPS** (stroke or filled).

> Course project — UGA (MAP401, 2024/25). Implemented in portable C with a Makefile.

---

## Features
- **PBM reader** and mask generation
- **Contour tracing** (full-image multiple contours)
- **Douglas–Peucker** polyline simplification (`type=1`)
- **Bézier degree‑2** fitting (`type=2`) and **degree‑3** fitting (`type=3`)
- **EPS export** of raw contours or simplified curves
- Small **test suite** and example PBM images (e.g., `Asterix3.pbm`, `ColombesDeLaPaix.pbm`, `Bugs_Bunny.pbm`)

---

## Project Structure
```
.
├── *.pbm                      # sample input images
├── *.eps                      # example outputs (generated)
├── image.c/.h                 # PBM I/O and image helpers
├── geometrie2d.c/.h           # 2D points, vectors, distances, projections
├── sequence_point.c/.h        # list/array containers for points
├── calcul_contour.c/.h        # contour extraction (raster → polylines)
├── simplification_contours.c/.h
│   ├─ Douglas–Peucker
│   └─ Bézier (deg 2 & 3) least‑squares fitting
├── generer_eps.c/.h           # EPS writers (stroke/fill; polyline/Bezier)
├── test_image.c               # PBM I/O demo
├── test_geometrie.c           # geometry sanity checks
├── test_calcul_contour.c      # raw contour extraction → EPS
├── test_simplification_contours.c
│                              # contour + simplification → EPS
└── Makefile                   # clang/gcc build rules
```

> VS Code settings are included in `.vscode/` for convenience.

---

## Build
Requires a C compiler (tested with **clang**, compatible with **gcc**).

```bash
# in the project root
make            # builds the test executables
make clean      # removes objects and executables
```

Generated executables (target names may vary by Makefile):
- `test_image`
- `test_geometrie`
- `test_calcul_contour`
- `test_simplification_contours`

---

## Usage

### 1) Raw contour extraction → EPS
```bash
./test_calcul_contour <image.pbm> <mode>
# mode: 0 = stroke (contour), 1 = fill (remplissage)
# Example:
./test_calcul_contour Asterix3.pbm 0
# → produces: Asterix3.eps (or Asterix3_contours.eps depending on target)
```

### 2) Contour simplification / Bézier fitting → EPS
```bash
./test_simplification_contours <image.pbm> <type> <threshold> <render_mode>
# type: 1 = Douglas-Peucker, 2 = Bézier2, 3 = Bézier3
# threshold: positive float controlling simplification strength
# render_mode: 0 = stroke, 1 = fill

# Examples (using included images):
./test_simplification_contours ColombesDeLaPaix.pbm 2 3 0
# → e.g. ColombesDeLaPaix_bezier2_d3.eps

./test_simplification_contours ColombesDeLaPaix.pbm 3 3 0
# → e.g. ColombesDeLaPaix_bezier3_d3.eps
```

**Notes**
- Bézier outputs are suffixed with `_bezier2_d<threshold>.eps` or `_bezier3_d<threshold>.eps`.
- Douglas–Peucker output is an EPS of simplified polylines (filename may end with `_contours.eps`).

---

## How it works (quick overview)
- **Contours** are traced on the raster into point sequences.
- **Douglas–Peucker** recursively splits segments by the point with max perpendicular distance until all distances ≤ `threshold`.
- **Bézier fitting** computes control points from sampled contour points (degree‑2/3) via closed‑form least‑squares relations, then emits EPS `curveto` segments.
- **EPS** coordinates flip the Y‑axis to match PostScript’s origin; you can choose **stroke** or **fill** mode.

---

## Sample Inputs
The repo ships several PBM images for testing, e.g.:
```
Asterix3.pbm
Bugs_Bunny.pbm
ColombesDeLaPaix.pbm
JoaquimHock-LesArbres.pbm
papillon2.pbm
```
Corresponding example EPS files are included (e.g., `*_bezier2_d3.eps`, `*_bezier3_d3.eps`).

---

## Troubleshooting
- If you see “Usage: …” messages, verify argument order and types.
- Ensure the input is **PBM** (portable bitmap). Other formats must be converted first.
- If EPS looks mirrored vertically, that’s expected: the writer maps image coordinates to EPS by flipping Y.

---

## License
Academic/educational use. If you plan to reuse outside coursework, adapt licensing as needed.

---

##  Authors
Alaa Saab & Abdul Rahman Jaber — UGA MAP401, 2024/25. 
