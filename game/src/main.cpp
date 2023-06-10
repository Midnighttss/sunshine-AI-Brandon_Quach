#include "rlImGui.h"
#include <time.h>
#include"Tilemap.h"
#include<vector>


#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

      
Tilemap map;

std::vector<Vector2> GetWalkableTileAdjacentTo(Vector2 tileposition) 
{
    std::vector<Vector2> adjacentTilePosition;

    //North,South,East,West
    Vector2 N = tileposition + NORTH;
    Vector2 S = tileposition + SOUTH;
    Vector2 E = tileposition + EAST;
    Vector2 W= tileposition + WEST;

    if (IsWalkable(N)) adjacentTilePosition.push_back(N);
    if (IsWalkable(S)) adjacentTilePosition.push_back(S);
    if (IsWalkable(E)) adjacentTilePosition.push_back(E);
    if (IsWalkable(W)) adjacentTilePosition.push_back(W);
    
    return adjacentTilePosition;
}

int main(void)
{
    srand(time(NULL));
    map.Randomize();
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    rlImGuiSetup(true);

    bool useGUI = false;
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        map.Draw();
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (IsKeyPressed(KEY_GRAVE)) useGUI = !useGUI;
        if (useGUI)
        {
            rlImGuiBegin();
            if (ImGui::Button("Randomize Map"))
            {
                map.Randomize();
            }
            rlImGuiEnd();
        }

        DrawText("Hello World!", 16, 9, 20, RED);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}