#include "rlImGui.h"
#include "Math.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720




int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    rlImGuiSetup(true);
    SetTargetFPS(144);

    const float radius = 25.0f;
    Vector2 obsticle { SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f };
    Vector2 direction { 0.0f, 1.0f };




    bool useGui = false;

    while (!WindowShouldClose())
    {
        Vector2 mousePosition = GetMousePosition();
        Vector2 fromAgentToMouse = { 0,-1 }; // Normalize(mousePosition - obsticle);
        Vector2 rightWisk = Rotate(fromAgentToMouse, -15 * DEG2RAD);
        Vector2 leftWisk = Rotate(fromAgentToMouse, 15 * DEG2RAD);




        RMAPI Vector2 NearestPoint(Vector2 fromAgentToMouse, Vector2 rightWisk, Vector2 mousePosition);
        {
            Vector2 AB = Subtract(rightWisk, fromAgentToMouse);
            float t = Dot(Subtract(mousePosition, fromAgentToMouse), AB) / Dot(AB, AB);
            return  Add(fromAgentToMouse, Scale(AB, Clamp(t, 0.0f, 1.0f)));
        }




        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircleV(obsticle, radius, BLUE);
        DrawCircleV(mousePosition, radius, RED);
 
        DrawLineV(obsticle, obsticle + fromAgentToMouse *100, BLACK);
        DrawLineV(obsticle, obsticle + rightWisk *100, GREEN);
        DrawLineV(obsticle, obsticle + leftWisk *100, GREEN);




        HideCursor();


        
        DrawText("Hello World!", 16, 9, 20, RED);
        DrawFPS(1200, 10);

        EndDrawing();
    }
    rlImGuiShutdown();
    CloseWindow();
    return 0;
}