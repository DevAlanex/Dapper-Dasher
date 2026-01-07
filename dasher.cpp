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

bool GroundCheck(AnimData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;
}

AnimData UpdateAnimData(AnimData data, float deltaTime, int maxFrame)
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

    float finishLine{nebulae[sizeOfNebulae - 1].pos.x};

    // Velocity
    int velocity{0};
    int nebVel{-200}; // pixels/sec

    // pixels/sec
    const int jumpSpeed{-600};

    // Mechanic 
    bool isInAir{};

    // Frame Rate
    SetTargetFPS(60);  

    // Backgrounds
    Texture2D background = LoadTexture("textures/far-buildings.png");
    Texture2D midground = LoadTexture("textures/back-buildings.png");
    Texture2D foreground = LoadTexture("textures/foreground.png");
    float bgX{}, mgX{}, fgX{};

    while(!WindowShouldClose()){
        
        const float dT{GetFrameTime()};

        BeginDrawing();
        ClearBackground(WHITE);
        bgX -= 20 * dT;
        mgX -= 40 * dT;
        fgX -= 80 * dT;
        Vector2 bg1Pos{bgX, 0.0};
        DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE);
        Vector2 bg2Pos{bgX + background.width * 2, 0.0};
        DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);
        Vector2 mg1Pos{mgX, 0.0};
        DrawTextureEx(midground, mg1Pos, 0.0, 2.0, WHITE);
        Vector2 mg2Pos{mgX + midground.width * 2, 0.0};
        DrawTextureEx(midground, mg2Pos, 0.0, 2.0, WHITE);
        Vector2 fg1Pos{fgX, 0.0};
        DrawTextureEx(foreground, fg1Pos, 0.0, 2.0, WHITE);
        Vector2 fg2Pos{fgX + foreground.width * 2, 0.0};
        DrawTextureEx(foreground, fg2Pos, 0.0, 2.0, WHITE);

        if(bgX < -background.width * 2)
        {
            bgX = 0.0;
        }

        if(mgX < -midground.width * 2)
        {
            mgX = 0.0;
        }

        if(fgX < -foreground.width * 2)
        {
            fgX = 0.0;
        }

        // Game Logic
        if(GroundCheck(scarfyData, windowDimensions[1]))
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
            // isInAir = true;
        }

        for(int i = 0; i < sizeOfNebulae; i++)
        {
            // updating position of each nebula
            nebulae[i].pos.x += nebVel * dT;
        }

        scarfyData.pos.y += velocity * dT;
        finishLine += nebVel * dT;

        // Animation cycle
        // Scarfy
        if(!isInAir)
        {
            scarfyData = UpdateAnimData(scarfyData, dT, 5);
        }
        
        for(int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i] = UpdateAnimData(nebulae[i], dT, 7);
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
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
    CloseWindow();
}