#include "rlImGui.h"
#include <time.h>
#include"Tilemap.h"
#include<vector>
#include "Pathfinder.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

      
Tilemap map;



int main(void)
{
    srand(time(NULL));
    map.Randomize();
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tile Map");
    rlImGuiSetup(true);

    bool useGUI = false;
    SetTargetFPS(144);

    while (!WindowShouldClose())
    {

        map.Draw();
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (IsKeyPressed(KEY_W) && map.isTileWalkable(map.positionOfPlayer - TileCoord(0, 1)))
            map.positionOfPlayer -= TileCoord(0, 1);
        if (IsKeyPressed(KEY_A) && map.isTileWalkable(map.positionOfPlayer - TileCoord(1, 0)))
            map.positionOfPlayer -= TileCoord(1, 0);
        if (IsKeyPressed(KEY_S) && map.isTileWalkable(map.positionOfPlayer + TileCoord(0, 1)))
            map.positionOfPlayer += TileCoord(0, 1);
        if (IsKeyPressed(KEY_D) && map.isTileWalkable(map.positionOfPlayer + TileCoord(1, 0)))
            map.positionOfPlayer += TileCoord(1, 0);


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
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            for (int x = 0; x < MAP_WIDTH; x++)
            {
                if (map.isTileWalkable(TileCoord(x, y)))
                {
                    Vector2 centerOfTile = map.GetScreenPositionOfTile(TileCoord(x, y)) + Vector2{ map.tileSizeX / 2, map.tileSizeY / 2 };

                    int xAdjacent = 0;
                    int yAdjacent = 0;

                    
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

                    DrawCircle(centerOfTile.x,centerOfTile.y, 5, GREEN);

                }
            }
        }

       /* TileCoord mouseTilePos = map.GetScreenPositionOfTile(GetMousePosition());
        if (map.ContainsTile(mouseTilePos))
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
            {
                pathfinder = Pathfinder(&map, agent.tilePosition, TileCoord(mouseTilePos));
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                pathfinder = Pathfinder(&map, agent.tilePosition, TileCoord(mouseTilePos));
                pathfinder.SolvePath();
            }
        }
        if (pathfinder.map != nullptr)
        {
            if (IsKeyPressed(KEY_SPACE))
            {
                pathfinder.ProcessNextIterationFunctional();
            }
            if (drawPathInfo) pathfinder.DrawCurrentState();
        }

        void ProcessNextIterationFunctional()
        {
            if (IsCompleted()) return;
            currentNode = GetLowestCostIn(unvisited).first;

            for (auto adjacent : map->GetWalkableTilesAdjacentTo(currntNode))
            {
                    if (IsVisited(adjacent)) continue;
                float costThisWay = GetTotalCostToReach(currentNode) + map->GetCostForTile(adjacent);

                float oldCost = GetTotalCostToReach(adjacent);
                if (costThisWay < oldCost)
                {
                    SetCostToReach(adjacent, costThisWay);
                    cheapestEdgeTo[adjacent] = currentNode;
                }
            }
            MoveToVisitedSet(currntNode);

        }

        float GetTotalCostToReach(TileCoord pos) { return unvisited[pos]; }
        void SetCostToReach(TileCoord pos, float newCost)
        {
            unvisited[pos] = newCost;
        }

       
*/

        DrawText("Please be kind on \nmarking for the \nforseeable future =)\n WASD for movement", 1050, 9, 20, RED);


        EndDrawing();
    }

    CloseWindow();
    return 0;
}