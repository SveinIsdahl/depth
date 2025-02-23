#include <iostream>
#include <string.h>
#include <vector>
#include <cstdlib>


namespace rl {
    #include "raylib/include/raylib.h"
}
struct Point3D {
    rl::Vector3 position;
    rl::Color color;
};
int main(void) {
    std::string imagePath = "out.png";

    const int screenWidth = 1600;
    const int screenHeight = 900;
    const int cameraMode = rl::CAMERA_FREE;  // TODO: Try CAMERA_FREE  

    rl::InitWindow(screenWidth, screenHeight, "Testing");

    rl::Camera camera = {0};
    camera.position = (rl::Vector3){0.0f, 2.0f, 4.0f};
    camera.target = (rl::Vector3){0.0f, 2.0f, 0.0f};
    camera.up = (rl::Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.projection = rl::CAMERA_PERSPECTIVE;

    rl::SetTargetFPS(60);
    rl::DisableCursor();

    std::vector<Point3D> points;


    FILE *f = fopen("vectors.txt", "r");
    if (!f) {
        perror("Error opening file");
        return 1;
    }


    int i = 0;
    int len = 0;
    int len_of_single_scan = 0;
    fscanf(f, "%d", &len);
    printf("%d\n", len);
    fscanf(f, "%d", &len_of_single_scan);
    printf("%d\n", len_of_single_scan);
    float *x = (float*) malloc(len * sizeof(float));
    float *y =  (float*) malloc(len* sizeof(float));
    float *z =  (float*) malloc(len* sizeof(float));

    for (i = 0; i < len; i++) {
        fscanf(f, "%f", &x[i]);
        fscanf(f, "%f", &y[i]);
        fscanf(f, "%f", &z[i]);

        Point3D p{rl::Vector3{y[i], z[i] + 5, x[i] }, rl::Color{230, 41, 55, 255}};
        points.push_back(p);
    }


    while (!rl::WindowShouldClose())
    {
        rl::UpdateCamera(&camera, cameraMode);

        rl::BeginDrawing();
        rl::ClearBackground(rl::RAYWHITE);
        rl::BeginMode3D(camera);

        rl::DrawPlane((rl::Vector3){0.0f, 0.0f, 0.0f}, (rl::Vector2){32.0f, 32.0f}, rl::LIGHTGRAY);  // Draw ground
        // rl::DrawCube((rl::Vector3){-16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f, rl::BLUE);            // Draw a blue wall
        
        //rl::DrawSphere((rl::Vector3){0.0f, 2.0f, 0.0f}, 0.01f, rl::BLACK);
        for (const auto& point : points) {
                rl::DrawCubeV(point.position, (rl::Vector3){0.02f, 0.02f, 0.02f}, point.color);
        }
        rl::EndMode3D();
        rl::DrawFPS(10, 10);
        rl::EndDrawing();
    }

    rl::CloseWindow();

    return 0;
}