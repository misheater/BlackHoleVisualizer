# Black Hole Visualizer

A real-time C++ visualization of Kerr black holes with physically accurate ray tracing and gravitational lensing, inspired by the visual effects from *Interstellar*.

## Features

- **Kerr Black Hole Physics**: Realistic rotating black hole simulation
- **Ray Tracing**: GPU-accelerated photon tracing around the event horizon
- **Gravitational Lensing**: Accurate light bending effects
- **Accretion Disk**: Glowing disk of matter around the black hole
- **Event Horizon Visualization**: The point of no return
- **Real-time Rendering**: Interactive 3D visualization with 60+ FPS
- **Camera Controls**: Orbit, zoom, and rotate around the black hole

## Requirements

- C++17 or later
- CMake 3.16+
- OpenGL 4.6+
- CUDA 11.0+ (for GPU acceleration, optional)

### Dependencies

- **GLFW** - Window and input management
- **GLM** - Mathematics library
- **GLAD** - OpenGL loader
- **stb_image** - Image loading

## Build Instructions

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

## Usage

```bash
./BlackHoleVisualizer
```

### Controls

- **Mouse Movement**: Rotate camera around black hole
- **Scroll**: Zoom in/out
- **WASD**: Fine camera position adjustments
- **SPACE**: Reset camera
- **ESC**: Exit

## Physics Model

The visualizer uses the **Kerr metric** to describe spacetime around a rotating black hole:

- **Black Hole Mass**: Adjustable (1-10 solar masses)
- **Spin Parameter (a)**: 0-1 (0 = Schwarzschild, 1 = maximally rotating)
- **Observer Distance**: Configurable
- **Accretion Disk Temperature**: Affects color and brightness

## Project Structure

```
BlackHoleVisualizer/
├── CMakeLists.txt
├── README.md
├── src/
│   ├── main.cpp
│   ├── renderer/
│   │   ├── Renderer.cpp
│   │   ├── Renderer.h
│   │   ├── ShaderProgram.cpp
│   │   └── ShaderProgram.h
│   ├── physics/
│   │   ├── KerrBlackHole.cpp
│   │   ├── KerrBlackHole.h
│   │   ├── RayTracer.cpp
│   │   └── RayTracer.h
│   ├── core/
│   │   ├── Camera.cpp
│   │   ├── Camera.h
│   │   ├── Window.cpp
│   │   └── Window.h
│   └── utils/
│       ├── Math.h
│       └── Logger.h
├── shaders/
│   ├── raytracing.vert
│   ├── raytracing.frag
│   ├── accretion.vert
│   ├── accretion.frag
│   └── composite.frag
└── assets/
    └── textures/
```

## References

- Kerr Metric: https://en.wikipedia.org/wiki/Kerr_metric
- Ray Tracing in Curved Spacetime: https://arxiv.org/abs/1502.03808
- Interstellar VFX: https://www.youtube.com/watch?v=zrl3mbMEue4

## License

MIT

## Author

misheater

