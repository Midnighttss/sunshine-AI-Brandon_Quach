#include "rlImGui.h"
#include"Math.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    Vector2 position = { 100,500 };
    Vector2 velocity = {10,0};
    SetTargetFPS(144);
    float maxSpeed = 1000;

    rlImGuiSetup(true);// sets up imgui

    HideCursor();

    bool useGUI = false;
    while (!WindowShouldClose())
    {
        const float dt =GetFrameTime();


        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (IsKeyDown(KEY_GRAVE)) useGUI = !useGUI;
        if (useGUI)
        {
            rlImGuiBegin();

            ImGui::SliderFloat2("position", &(position.x), 0, SCREEN_WIDTH);
            ImGui::SliderFloat2("velocity", &(velocity.x), -maxSpeed, maxSpeed);
           

            rlImGuiEnd();
        }


        
        Vector2 displacement = velocity * dt;
        position = position + displacement;

        //position = GetMousePosition();
        DrawCircleV(position, 50, DARKGREEN);

        DrawFPS(1200, 10);
        DrawText("Hello World!", 16, 9, 20, RED);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}