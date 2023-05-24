#include "rlImGui.h"
#include "Math.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Vector2 WraparoundScreen(Vector2 position)
{
    Vector2 outPosition =
    {
        (int)(position.x + SCREEN_WIDTH) % SCREEN_WIDTH,
        (int)(position.y + SCREEN_HEIGHT) % SCREEN_HEIGHT
    };

    return outPosition;
}


class Rigidbody
{
public:
    Vector2 position;
    Vector2 velocity;
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

Vector2 flee(const Vector2& agentPosition, const Vector2& agentVelocity, const Vector2& targetPosition, float maxAcceleration)
{
    Vector2 desiredVelocity = Normalize(agentPosition - targetPosition) * maxAcceleration;
    Vector2 steer = desiredVelocity - agentVelocity;
    return steer;
}


int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    SetTargetFPS(144);

    rlImGuiSetup(true); // Sets up imgui

    Vector2 position = { 100, 100 };
    Vector2 target = { 100, 400 };
    Vector2 velocity = { 0.0f, 0.0f };
    Vector2 acceleration = { 0.0f, 0.0f };
    float speed = 500.0f;
    float maxSpeed = 1000;

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

            ImGui::SliderFloat2("Position", &(position.x), 0, SCREEN_WIDTH);
            ImGui::SliderFloat2("Velocity", &(velocity.x), -maxSpeed, maxSpeed);
            ImGui::SliderFloat2("Acceleration", &(acceleration.x), -maxSpeed, maxSpeed);

            rlImGuiEnd();
        }
        
        target= GetMousePosition();
        HideCursor();
        acceleration = Normalize(target - position) * speed - velocity;
        velocity = velocity + acceleration * deltaTime;
        position = position + velocity * deltaTime + acceleration * deltaTime * deltaTime * 0.5f;
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            acceleration = Normalize(target - position) * speed - velocity;
            velocity = velocity + acceleration * deltaTime;
            position = position - velocity * deltaTime - acceleration * deltaTime * deltaTime * 0.5f;
        }
        position = WraparoundScreen(position);
        // Flee from another object in the world (e.g., a point)
        /*if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {

        Vector2 fleeTargetPosition = { 500, 300 };
        Vector2 fleeAcceleration = flee(target, velocity, fleeTargetPosition, speed);
        }*/
        DrawText("Hello World!", 16, 9, 20, RED);

        DrawCircleV(position, 50, GREEN);
        DrawCircleGradient(target.x, target.y, 50, LIGHTGRAY, BLACK);


        DrawFPS(10, 100);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}