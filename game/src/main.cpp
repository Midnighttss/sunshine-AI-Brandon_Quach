#include "rlImGui.h"
#include "Math.h"
#include <vector>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720


bool CheckCollisionLineCircle(Vector2 lineStart, Vector2 lineEnd, Vector2 circlePosition, float circleRadius)
{
    Vector2 nearest = NearestPoint(lineStart, lineEnd, circlePosition);
    return DistanceSqr(nearest, circlePosition) <= circleRadius * circleRadius;
}

struct Rigidbody
{
    Vector2 pos{};
    Vector2 vel{};
    Vector2 acc{};
    Vector2 dir{};
    float angularSpeed;
};

void Integrate(Rigidbody& rb, float dt)
{
    rb.vel = rb.vel + rb.acc * dt;
    rb.pos = rb.pos + rb.vel * dt + rb.acc * dt * dt * 0.5;
    rb.dir = RotateTowards(rb.dir, Normalize(rb.vel), rb.angularSpeed * dt);
}

Vector2 Seek(const Vector2& pos, const Rigidbody& rb, float maxSpeed)
{
    return Normalize(pos - rb.pos) * maxSpeed - rb.vel;
}


class Seeker
{
public:
    Rigidbody rb;
    float lineLength;
    float radius;

    Seeker(float startX, float startY, float angularSpeed, float lineLength, float radius)
        : lineLength(lineLength), radius(radius)
    {
        rb.pos = { startX, startY };
        rb.dir = { 0.0, 1.0 };
        rb.angularSpeed = angularSpeed;
    }

    void ObstacleAvoidance(const Vector2& obstaclePosition, float obstacleRadius, float avoidanceForce, float deltatime)
    {
        Vector2 right = Rotate(rb.dir, 90 * DEG2RAD);
        Vector2 left = Rotate(rb.dir, -90 * DEG2RAD);
        Vector2 top = Rotate(rb.dir, 0 * DEG2RAD);
        Vector2 bottom = Rotate(rb.dir, 180 * DEG2RAD);
        Vector2 rightWisk = rb.pos + right * lineLength;
        Vector2 leftWisk = rb.pos + left * lineLength;
        Vector2 topWisk = rb.pos + top * lineLength;
        Vector2 bottomWisk = rb.pos + bottom * lineLength;

        bool leftCollision = CheckCollisionLineCircle(rb.pos, leftWisk, obstaclePosition, obstacleRadius);
        bool rightCollision = CheckCollisionLineCircle(rb.pos, rightWisk, obstaclePosition, obstacleRadius);
        bool topCollision = CheckCollisionLineCircle(rb.pos, topWisk, obstaclePosition, obstacleRadius);;
        bool bottomCollision = CheckCollisionLineCircle(rb.pos, bottomWisk, obstaclePosition, obstacleRadius);;

        if (leftCollision || rightCollision||topCollision||bottomCollision)
        {
            Vector2 avoidanceDir = Normalize(rb.pos - obstaclePosition);
            rb.acc = rb.acc + avoidanceDir * avoidanceForce;
        }

        if (leftCollision)
        {
            Vector2 linearDirection = Normalize(rb.vel);
            float linearSpeed = Length(rb.vel);
            rb.vel = Rotate(linearDirection, rb.angularSpeed * deltatime * DEG2RAD) * linearSpeed;
        }

        if (rightCollision)
        {
            Vector2 linearDirection = Normalize(rb.vel);
            float linearSpeed = Length(rb.vel);
            rb.vel = Rotate(linearDirection, -rb.angularSpeed * deltatime * DEG2RAD) * linearSpeed;
        }
        if (topCollision)
        {
            Vector2 linearDirection = Normalize(rb.vel);
            float linearSpeed = Length(rb.vel);
            rb.vel = Rotate(linearDirection, -rb.angularSpeed * deltatime * DEG2RAD) * linearSpeed;
        }
        if (bottomCollision)
        {
            Vector2 linearDirection = Normalize(rb.vel);
            float linearSpeed = Length(rb.vel);
            rb.vel = Rotate(linearDirection, -rb.angularSpeed * deltatime * DEG2RAD) * linearSpeed;
        }
    }
};


int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    rlImGuiSetup(true);
    SetTargetFPS(144);

    float radius = 25.0f;
    float seekerWiskerLength = 100;
    Seeker seeker(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5, 100.0, 100.0, 25.0);


    std::vector<Vector2> obstaclePositions;
    Vector2 obstaclePosition{ SCREEN_WIDTH * 0.75, SCREEN_HEIGHT * 0.25};
    float obstacleRadius = 50.0f;



    bool useGui = false;

    while (!WindowShouldClose())
    {
        const float deltaTime = GetFrameTime();

        seeker.rb.acc = Seek(GetMousePosition(), seeker.rb, 100);
        Integrate(seeker.rb, deltaTime);
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            obstaclePositions.push_back(GetMousePosition());
        }

        for (const auto& obstaclePosition : obstaclePositions)
        {
            seeker.ObstacleAvoidance(obstaclePosition, 50.0, 100.0, deltaTime);
        }

        DrawCircleV(seeker.rb.pos, seeker.radius, BLUE);
        for (const auto& obstaclePosition : obstaclePositions)
        {
            DrawCircleV(obstaclePosition, 25, BLUE);
        }
        
        Vector2 right = Rotate(seeker.rb.dir, 90.0 * DEG2RAD);
        Vector2 left = Rotate(seeker.rb.dir, -90.0 * DEG2RAD);
        Vector2 top = Rotate(seeker.rb.dir, 0 * DEG2RAD);
        Vector2 bottom = Rotate(seeker.rb.dir, 180 * DEG2RAD);

        Vector2 rightWisk = seeker.rb.pos + right * seekerWiskerLength;
        Vector2 leftWisk = seeker.rb.pos + left * seekerWiskerLength;
        Vector2 topWisk = seeker.rb.pos + top * seekerWiskerLength;
        Vector2 bottomWisk = seeker.rb.pos + bottom * seekerWiskerLength;
        
        bool leftCollision = false;
        bool rightCollision = false;
        bool topCollision = false;
        bool bottomCollision = false;

        for (const auto& obstaclePosition : obstaclePositions)
        {
            leftCollision = CheckCollisionLineCircle(seeker.rb.pos, leftWisk, obstaclePosition, obstacleRadius);
            rightCollision = CheckCollisionLineCircle(seeker.rb.pos, rightWisk, obstaclePosition, obstacleRadius);
            topCollision = CheckCollisionLineCircle(seeker.rb.pos, topWisk, obstaclePosition, obstacleRadius);
            bottomCollision = CheckCollisionLineCircle(seeker.rb.pos, bottomWisk, obstaclePosition, obstacleRadius);
        }
        Color rightColor = rightCollision ? RED : GREEN;
        Color leftColor = leftCollision ? RED : GREEN;
        Color topColor = leftCollision ? RED : GREEN;
        Color bottomColor = leftCollision ? RED : GREEN;

        DrawLineV(seeker.rb.pos, rightWisk, rightColor);
        DrawLineV(seeker.rb.pos, leftWisk, leftColor);
        DrawLineV(seeker.rb.pos, topWisk, topColor);
        DrawLineV(seeker.rb.pos, bottomWisk, bottomColor);
        


        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircleV(seeker.rb.pos, radius, RED);

        


        
        DrawText("Hello World!", 16, 9, 20, BLACK);
        DrawFPS(1200, 10);

        EndDrawing();
    }
    rlImGuiShutdown();
    CloseWindow();
    return 0;
}