
Compile and run:   

```
g++ main.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 `pkg-config --cflags --libs opencv4`
```

TODO: Add CMakeList   
Uses Raylib for rendering and ZoeDepth to estimate depth from an image
