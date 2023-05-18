//101191483 Brandon Quach

#include "rlImGui.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720


class Circle
{
public:
    float x, y;
    float circleRadius = 60;
    Color circleColor1;
    Color circleColor2;

    void Draw()
    {
        DrawCircleGradient(x, y, circleRadius, circleColor1, circleColor2);
    }
};


class Player
{
public:
    float x, y;
    float circleRadius = 60;
    Color circleColor1;
    Color circleColor2;

    void Draw()
    {
        DrawCircleGradient(x, y, circleRadius, circleColor1, circleColor2);
    }
};




Circle circle;
Player player;
int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    SetTargetFPS(60);
    Vector2 circleA = { (float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2 };
    Vector2 circleB = { -100.0f, -100.0f };
    bool collision = false;

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_D)) circleA.x += 10.0f;//Move circle to the right
        if (IsKeyDown(KEY_A)) circleA.x -= 10.0f;//Move circle to the left
        if (IsKeyDown(KEY_W)) circleA.y -= 10.0f;//Move circle to the up
        if (IsKeyDown(KEY_S)) circleA.y += 10.0f;//Move circle to the down

        circleB = GetMousePosition();//ball draws on mouse position


        //////////////////////////////////////////////////////////////////////////////////////////DRAW/////////////////////////////////////////////////////////////////////////////////
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Brandon Quach", 16, 9, 20, RED);
        DrawLine(45, 45, 90, 90, BLUE);//Draw A line
        DrawCircleV(circleB, 40, BLUE);//Draws circle that will follow the mouse
        DrawCircleV(circleA, 40, RED);//Draw a circle 
        DrawRectangle(360, 360, 500, 186, DARKPURPLE);//Draw a rectangle    
        SetExitKey(KEY_ESCAPE);//Allows to close program when esc is pressed


        //////////////////////////////////////////////////////////////////////////////////////////Collisions/////////////////////////////////////////////////////////////////////////////////

        collision = CheckCollisionCircles(circleA, 40, circleB, 40);

        if (collision)
        {
            DrawCircleV(circleA, 40, PURPLE);  //changes ball colour when collision occurs
            DrawCircleV(circleB, 40, PURPLE);  //changes ball colour when collision occurs

        }




        EndDrawing();
    }

    CloseWindow();
    return 0;
}
