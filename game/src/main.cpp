#include "rlImGui.h"
#include "Math.h"
#include<vector>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Vector2 WraparoundScreen(Vector2 position)
{
    Vector2 outPosition =
    {
        fmodf (position.x + SCREEN_WIDTH , SCREEN_WIDTH),
        fmodf (position.y + SCREEN_HEIGHT, SCREEN_HEIGHT)
    };

    return outPosition;
}


class Rigidbody
{
public:
    Vector2 position;
    Vector2 velocity;
    Vector2 mousePosition;
};

// Sprite class
class Sprite
{
public:
    Texture2D texture;
    Vector2 position;
    Rectangle bounds;

    void Draw()
    {
        DrawTextureEx(texture, position, 0.0f, 1.0f, WHITE);
    }
};

// Agent class
class Agent
{
public:
    Rigidbody rigidbody;
    Sprite sprite;
    float maxSpeed;
    float maxAcceleration;
};



int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    SetTargetFPS(144);

    std::vector<Agent> agents;



    Agent agent;
    agent.rigidbody.position = { 400, 225 };
    agent.rigidbody.velocity = { 10, 0 };
    agent.maxSpeed = 400.0f;
    agent.maxAcceleration = 800.0f;



    rlImGuiSetup(true); // Sets up imgui
    Rigidbody ridgidbody;
    ridgidbody.mousePosition = GetMousePosition();
    Vector2 acceleration = { 10.0f, 0.0f };
    float speed = 500;
    float maxSpeed = 1000;
    float maxAccel = 1000;
    bool useGUI = false;
    while (!WindowShouldClose())
    {
        const float deltaTime = GetFrameTime();
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (IsKeyDown(KEY_GRAVE)) useGUI = !useGUI;
        if (useGUI)
        {
            rlImGuiBegin();

            ImGui::DragFloat2("Position", &(ridgidbody.position.x), 0, SCREEN_WIDTH);
            ImGui::DragFloat2("Velocity", &(agent.rigidbody.velocity.x), -maxSpeed, maxSpeed);
            ImGui::DragFloat2("Acceleration", &(acceleration.x),1, -maxAccel, maxAccel);

            rlImGuiEnd();
        }
        
        ridgidbody.mousePosition = GetMousePosition();
        HideCursor();



        ridgidbody.position = ridgidbody.position + agent.rigidbody.velocity * deltaTime + acceleration * deltaTime * deltaTime * 0.5f;
        agent.rigidbody.velocity = agent.rigidbody.velocity + acceleration * deltaTime;

        if(IsMouseButtonUp(MOUSE_LEFT_BUTTON))
        {
            acceleration = Normalize(ridgidbody.mousePosition - ridgidbody.position) * speed - agent.rigidbody.velocity;
        }
        else
        {
            acceleration = Normalize(ridgidbody.position - ridgidbody.mousePosition) * speed - agent.rigidbody.velocity;
        }
        



        //acceleration = { 0,0 };
        ridgidbody.position = WraparoundScreen(ridgidbody.position);


        
        
        DrawText("Hello World!", 16, 9, 20, RED);

        DrawCircleV(ridgidbody.position, 50, BLUE);
        DrawCircleGradient(ridgidbody.mousePosition.x, ridgidbody.mousePosition.y, 50, LIGHTGRAY, BLACK);
        
        DrawCircle(200,200, 50, BLUE);

        collision = CheckCollisionCircles(circleA, 40, circleB, 40);

        if (collision)
        {
            DrawCircleV(circleA, 40, PURPLE);  //changes ball colour when collision occurs
            DrawCircleV(circleB, 40, PURPLE);  //changes ball colour when collision occurs

        }

        
        DrawLineV(ridgidbody.position, ridgidbody.position + agent.rigidbody.velocity, RED);
        DrawLineV(ridgidbody.position, ridgidbody.position + acceleration, GREEN);
        DrawLineV(ridgidbody.position, ridgidbody.position + (ridgidbody.mousePosition - ridgidbody.position) *150, ORANGE);





        DrawFPS(1200, 10);

        EndDrawing();
    }
    rlImGuiShutdown();
    CloseWindow();
    return 0;
}