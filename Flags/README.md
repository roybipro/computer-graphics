# Computer Graphics Flag Assignment

This folder contains ten independent C++ OpenGL Immediate Mode projects using GLUT/FreeGLUT.

## Projects

- `Canada/main.cpp`
- `USA/main.cpp`
- `NewZealand/main.cpp`
- `Jordan/main.cpp`
- `Morocco/main.cpp`
- `Ghana/main.cpp`
- `CapeVerde/main.cpp`
- `SouthAfrica/main.cpp`
- `Croatia/main.cpp`
- `Haiti/main.cpp`

Each program includes:

- `init()`
- `display()`
- `reshape()`
- `main()`
- Modular helper functions for rectangles, triangles, stars, circles, shields, leaves, and flag-specific emblems.

## Compile

On Linux with GLUT or FreeGLUT:

```bash
g++ main.cpp -o flag -lGL -lGLU -lglut
./flag
```

On macOS with the system GLUT framework:

```bash
g++ main.cpp -o flag -framework OpenGL -framework GLUT
./flag
```

All drawings are made manually with OpenGL primitives. No textures, images, bitmap loading, SVG files, or shaders are used.
