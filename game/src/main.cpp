#include "rlImGui.h"
#include <time.h>
#include"Tilemap.h"
#include<vector>


#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

      
Tilemap map;



int main(void)
{
    srand(time(NULL));
    map.Randomize();
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    rlImGuiSetup(true);

    bool useGUI = false;
    SetTargetFPS(144);

    while (!WindowShouldClose())
    {

        map.Draw();
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (IsKeyPressed(KEY_W) && map.isTileWalkable(map.playerPosition - TileCoord(0, 1)))
            map.playerPosition -= TileCoord(0, 1);
        if (IsKeyPressed(KEY_S) && map.isTileWalkable(map.playerPosition + TileCoord(0, 1)))
            map.playerPosition += TileCoord(0, 1);
        if (IsKeyPressed(KEY_A) && map.isTileWalkable(map.playerPosition - TileCoord(1, 0)))
            map.playerPosition -= TileCoord(1, 0);
        if (IsKeyPressed(KEY_D) && map.isTileWalkable(map.playerPosition + TileCoord(1, 0)))
            map.playerPosition += TileCoord(1, 0);

        
        


        if (IsKeyPressed(KEY_GRAVE)) useGUI = !useGUI;
        if (useGUI)
        {
            rlImGuiBegin();
            if (ImGui::Button("Randomize Map"))
            {
                map.Randomize();
            }
            rlImGuiEnd();
       
           for (int x = 0; x < MAP_WIDTH; x++)
           {
               for (int y = 0; y < MAP_HEIGHT; y++)
               {
                   if (map.isTileWalkable(TileCoord(x, y)))
                   {
                       Vector2 centerOfTile = map.GetScreenPositionOfTile(TileCoord(x, y)) + Vector2{ map.tileSizeX / 2, map.tileSizeY / 2 };

                       int xAdjacent = 0;
                       int yAdjacent = 0;

                       
                       xAdjacent = x;
                       yAdjacent = y - 1;
                       if (yAdjacent >= 0 && map.isTileWalkable(TileCoord(xAdjacent, yAdjacent)))
                       {
                           Vector2 adjacentTileCenter = map.GetScreenPositionOfTile(TileCoord(xAdjacent, yAdjacent)) + Vector2{ map.tileSizeX / 2, map.tileSizeY / 2 };
                           DrawLineEx(centerOfTile, adjacentTileCenter, 1, GREEN);
                       }

                       
                       xAdjacent = x;
                       yAdjacent = y + 1;
                       if (yAdjacent < MAP_HEIGHT && map.isTileWalkable(TileCoord(xAdjacent, yAdjacent)))
                       {
                           Vector2 adjacentTileCenter = map.GetScreenPositionOfTile(TileCoord(xAdjacent, yAdjacent)) + Vector2{ map.tileSizeX / 2, map.tileSizeY / 2 };
                           DrawLineEx(centerOfTile, adjacentTileCenter, 1, GREEN);
                       }

                       
                       xAdjacent = x + 1;
                       yAdjacent = y;
                       if (xAdjacent < MAP_WIDTH && map.isTileWalkable(TileCoord(xAdjacent, yAdjacent)))
                       {
                           Vector2 adjacentTileCenter = map.GetScreenPositionOfTile(TileCoord(xAdjacent, yAdjacent)) + Vector2{ map.tileSizeX / 2, map.tileSizeY / 2 };
                           DrawLineEx(centerOfTile, adjacentTileCenter, 1, GREEN);
                       }

                       
                       xAdjacent = x - 1;
                       yAdjacent = y;
                       if (xAdjacent >= 0 && map.isTileWalkable(TileCoord(xAdjacent, yAdjacent)))
                       {
                           Vector2 adjacentTileCenter = map.GetScreenPositionOfTile(TileCoord(xAdjacent, yAdjacent)) + Vector2{ map.tileSizeX / 2, map.tileSizeY / 2 };
                           DrawLineEx(centerOfTile, adjacentTileCenter, 1, GREEN);
                       }

                       DrawCircle(static_cast<int>(centerOfTile.x), static_cast<int>(centerOfTile.y), 5, GREEN);
                   }
               }
           }
        }

        DrawText("Hello World!", 16, 9, 20, RED);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}