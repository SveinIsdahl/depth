namespace rl {
    #include "raylib.h"
}

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;
    const int cameraMode = rl::CAMERA_FIRST_PERSON;  // TODO: Try CAMERA_FREE  

    rl::InitWindow(screenWidth, screenHeight, "Testing");

    rl::Camera camera = {0};
    camera.position = (rl::Vector3){0.0f, 2.0f, 4.0f};
    camera.target = (rl::Vector3){0.0f, 2.0f, 0.0f};
    camera.up = (rl::Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.projection = rl::CAMERA_PERSPECTIVE;

    rl::SetTargetFPS(60);
    rl::DisableCursor();

    float heights[5] = {0};
    rl::Vector3 positions[5] = {0};
    rl::Color colors[5] = {0};

    // Main game loop
    while (!rl::WindowShouldClose())
    {
            
        rl::UpdateCamera(&camera, cameraMode);

        rl::BeginDrawing();

        rl::ClearBackground(rl::RAYWHITE);
        rl::BeginMode3D(camera);

        rl::DrawPlane((rl::Vector3){0.0f, 0.0f, 0.0f}, (rl::Vector2){32.0f, 32.0f}, rl::LIGHTGRAY);  // Draw ground
        rl::DrawCube((rl::Vector3){-16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f, rl::BLUE);            // Draw a blue wall
        rl::DrawCube((rl::Vector3){16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f, rl::LIME);             // Draw a green wall
        rl::DrawCube((rl::Vector3){0.0f, 2.5f, 16.0f}, 32.0f, 5.0f, 1.0f, rl::GOLD);             // Draw a yellow wall

        rl::EndMode3D();

        rl::EndDrawing();
    }

    rl::CloseWindow();

    return 0;
}
