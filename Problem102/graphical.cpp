
#include "raylib.h"
#include "triangle.hpp"
#include <cstdlib>
#include <ctime>
#include <list>

// Window dimensions
const int screenWidth = 800;
const int screenHeight = 600;

// Function to generate a random triangle inside the window
Triangle generateRandomTriangle() {
    return {
        rand() % screenWidth, rand() % screenHeight,
        rand() % screenWidth, rand() % screenHeight,
        rand() % screenWidth, rand() % screenHeight
    };
}

Rect generateRandomRectangle()
{
    return {rand() % screenWidth, rand() % screenHeight, 10 + rand() % 190, 10 + rand() % 190};
}

void drawScale()
{
    for(int off=0; off<100; off+=10)
    {
        DrawLine(off, 10, off+10, 10, BLACK);
        DrawLine(off, 5, off, 10, BLACK);
        DrawLine(off+10, 5, off+10, 10, BLACK);

        DrawLine(10, off, 10, off+10, BLACK);
        DrawLine(5, off, 10, off, BLACK);
        DrawLine(5, off+10, 10, off+10, BLACK);
    }
}

Triangle mirrorY(Triangle t)
{
    return {t.ax, -t.ay, t.bx, -t.by, t.cx, -t.cy};
}

/**
 * compile:
 * clang++ vec.cpp Problem102/triangle.cpp Problem102/graphical.cpp -o Problem102/graphical -std=c++2b -Wall -I/usr/local/include -L/usr/local/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
 */
int main() {
    // Initialize window
    InitWindow(screenWidth, screenHeight, "Raylib - Random Triangle");
    SetTargetFPS(60);

    srand(time(NULL));

    // Generate initial triangle
    Triangle triangle = generateRandomTriangle();
    // Rect rect = generateRandomRectangle();

    std::list<Vector2> border_points;

    bool last_contained = false;

    while (!WindowShouldClose()) {
        // Get mouse position
        int mouseX = GetMouseX();
        int mouseY = GetMouseY();

        Color triangleColor;

        // Determine triangle color
        if(contains(triangle, mouseX, mouseY))
        {
            triangleColor = GREEN;

            if(!last_contained)
                border_points.push_back((Vector2) {(float) mouseX, (float) mouseY});

            last_contained = true;
        }
        else
        {
            triangleColor = BLUE;

            if(last_contained)
                border_points.push_back((Vector2) {(float) mouseX, (float) mouseY});

            last_contained = false;
        }

        // Check for spacebar press to generate a new triangle
        if (IsKeyPressed(KEY_SPACE)) {
            triangle = generateRandomTriangle();
            border_points.clear();
        }

        // Rendering
        BeginDrawing();
        ClearBackground(RAYWHITE);

        drawScale();

        // Draw the triangle
        DrawTriangle({(float) triangle.ax, (float) triangle.ay},
            {(float) triangle.bx, (float) triangle.by},
            {(float) triangle.cx, (float) triangle.cy},
            triangleColor);
        // DrawRectangle(rect.x, rect.y, rect.w, rect.h, triangleColor);

        for(Vector2 &v: border_points)
            DrawCircle(v.x, v.y, 4, RED);

        // Draw text instructions
        DrawText("Press SPACE to generate a new triangle", 10, 10, 20, DARKGRAY);
        DrawText("Move mouse to check containment", 10, 40, 20, DARKGRAY);

        EndDrawing();
    }

    // Cleanup
    CloseWindow();
    return 0;
}
