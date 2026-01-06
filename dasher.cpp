/*
Game: Dapper Dasher
Author: Alexander Johnson
Dec, 7th 2025
*/

#include "raylib.h"

int main() {

    // Window Dimensions
    const int window_width{512};
    const int window_height{380};

    // window initialization
    InitWindow(window_width, window_height, "Dapper Dasher");

    // Gravity (pixels/sec)/sec
    const int gravity{1000};

    // Load Sprites
    // Scarfy
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;

    Vector2 scarfyPos;
    scarfyPos.x = window_width/2 - scarfyRec.width/2;
    scarfyPos.y = window_height - scarfyRec.height;

    // Nebula
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    
    Rectangle nebRec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Rectangle neb2Rec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 nebPos{window_width, window_height - nebRec.height};
    Vector2 neb2Pos{window_width + 300, window_height - nebRec.height};


    // Velocity
    int velocity{0};
    int nebVel{-200}; // pixels/sec

    // pixels/sec
    const int jumpSpeed{-600};

    // Mechanic 
    bool isInAir{};

    // Frame Rate
    SetTargetFPS(60);

    // Animation Logic
    int frame{};
    const float updateTime{1.0/12.0};
    float runningTime{};

    int nebFrame{};
    const float nebUpdateTime{1.0/12.0};
    float nebRunningTime{1.0/12.0};

    int neb2Frame{};
    const float neb2UpdateTime{1.0/16.0};
    float neb2RunningTime;

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);

        const float dT{GetFrameTime()};

         // Game Logic
        if(IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpSpeed;
            isInAir = true;
        }
        else if (isInAir && scarfyPos.y < window_height - scarfyRec.height)
        {
            isInAir = true;
            velocity += gravity * dT;
        }
        else 
        {
            isInAir = false;
            velocity = 0;
        }

        nebPos.x += nebVel * dT;
        neb2Pos.x += nebVel * dT;
        scarfyPos.y += velocity * dT;

        // Animation cycle
        // Scarfy
        if(!isInAir)
        {
            runningTime = runningTime + dT;  
            if(runningTime >= updateTime) 
            {
                runningTime = 0.0;
                scarfyRec.x = frame * scarfyRec.width;
                frame++;

                if( frame > 5 )
                {
                frame = 0;
                }
            }
        }
        
        // Nebula
        nebRunningTime = nebRunningTime + dT;
        if(nebRunningTime >= nebUpdateTime)
        {
            nebRunningTime = 0;
            nebRec.x = nebFrame * nebRec.width;
            nebFrame++;

            if(nebFrame > 7)
            {
                nebFrame = 0;
            }
        }

        // Nebula 2
        neb2RunningTime = neb2RunningTime + dT;
        if(neb2RunningTime >= neb2UpdateTime)
        {
            neb2RunningTime = 0;
            neb2Rec.x = neb2Frame * neb2Rec.width;
            neb2Frame++;

            if(neb2Frame > 7)
            {
                neb2Frame = 0;
            }
        }

        // Render Images
        // Scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        // Nebula and Nebula 2
        DrawTextureRec(nebula, nebRec, nebPos, WHITE);
        DrawTextureRec(nebula, neb2Rec, neb2Pos, RED);


        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}