#include <opencv2/opencv.hpp>
#include <iostream>
#include <string.h>

namespace rl {
    #include "raylib.h"
}
struct Point3D {
    rl::Vector3 position;
    rl::Color color;
};
int main(void) {
    std::string imagePath = "out.png";
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);

    cv::Size newSize(static_cast<int>(image.cols * 0.05),
                     static_cast<int>(image.rows * 0.05));

    cv::resize(image, image, newSize);

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
    points.reserve(image.rows * image.cols);

    for (int y = 0; y < image.rows; y++) {
        for (int x = 0; x < image.cols; x++) {
            float depth = (float)image.at<uchar>(y, x) / 32.0f;
            points.push_back({(rl::Vector3){((float)x)/20+2, depth, ((float)(y))/20+2}, rl::BLACK});
        }
    }

    while (!rl::WindowShouldClose())
    {
        rl::UpdateCamera(&camera, cameraMode);

        rl::BeginDrawing();
        rl::ClearBackground(rl::RAYWHITE);
        rl::BeginMode3D(camera);

        rl::DrawPlane((rl::Vector3){0.0f, 0.0f, 0.0f}, (rl::Vector2){32.0f, 32.0f}, rl::LIGHTGRAY);  // Draw ground
        //rl::DrawCube((rl::Vector3){-16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f, rl::BLUE);            // Draw a blue wall
        
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
