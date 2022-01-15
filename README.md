# SDL_Demo
Compilation instructions

```
cmake -B build -DCMAKE_BUILD_TYPE=RELEASE .
cmake --build build
build/sddemo
```

To select a particular renderer use
```
SDL_RENDER_DRIVER=opengles2 ./sddemo
```


Keys

- w: windowed
- f: fullscreen
- d: fullstreen desktop
- 0: disable vsync
- 1: enable vsync
- p: print FPS

All commands reset the counter too.
