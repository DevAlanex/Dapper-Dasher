/*
Game: Dapper Dasher
Author: Alexander Johnson
Dec, 7th 2025
*/

#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool groundCheck(AnimData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
    // update runningTime
    data.runningTime += deltaTime;
    if(data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.0;
        // update animation frame
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if(data.frame > maxFrame)
        {
            data.frame = 0;
        }
    }
    return data;
}

int main() {

    // Window Dimensions
    int windowDimensions[2];
    windowDimensions[0] = 512;
    windowDimensions[1] = 380;

    // window initialization
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher");

    // Gravity (pixels/sec)/sec
    const int gravity{1000};

    // Load Sprites
    // Scarfy
    Texture2D scarfy = LoadTexture("textures/scarfy.png");

    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    
    scarfyData.pos.x = windowDimensions[0]/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;

    scarfyData.frame = 0.0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0.0;

    // Nebula
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    // Anim Data for nebulae
    const int sizeOfNebulae{6};
    AnimData nebulae[sizeOfNebulae]{};

    for(int i = 0; i < sizeOfNebulae; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8;

        nebulae[i].pos.x = windowDimensions[0] + i * 300;
        nebulae[i].pos.y = windowDimensions[1] - nebula.height/8;

        nebulae[i].frame = 0.0;
        nebulae[i].updateTime = 1.0/16.0;
        nebulae[i].runningTime = 0.0;
    }

    // Velocity
    int velocity{0};
    int nebVel{-200}; // pixels/sec

    // pixels/sec
    const int jumpSpeed{-600};

    // Mechanic 
    bool isInAir{};

    // Frame Rate
    SetTargetFPS(60);  

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);

        const float dT{GetFrameTime()};

        // Game Logic
        if(groundCheck(scarfyData, windowDimensions[1]))
        {
        velocity = 0;
        isInAir = false;
        }
        else
        {
        velocity += gravity * dT;
        isInAir = true;
        }

        if(IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpSpeed;
            isInAir = true;
        }

        for(int i = 0; i < sizeOfNebulae; i++)
        {
            // updating position of each nebula
            nebulae[i].pos.x += nebVel * dT;
        }

        scarfyData.pos.y += velocity * dT;

        // Animation cycle
        // Scarfy
        if(!isInAir)
        {
            scarfyData = updateAnimData(scarfyData, dT, 5);
        }
        
        for(int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i] = updateAnimData(nebulae[i], dT, 7);
        }

        // Render Images
        // Scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        // Nebulae
        for(int i = 0; i < sizeOfNebulae; i++)
        {
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        };


        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}