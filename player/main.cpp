#include "raylib.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "battle-sim player");

    SetTargetFPS(60);

    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}