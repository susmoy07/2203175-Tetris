#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>
#include <fstream> 

double lastUpdateTime = 0;
float fadeAlpha = 1.0f;

bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

void DrawShadowedText(Font font, const char* text, Vector2 position, float fontSize, float spacing, Color textColor)
{
    DrawTextEx(font, text, {position.x + 2, position.y + 2}, fontSize, spacing, BLACK); // Shadow
    DrawTextEx(font, text, position, fontSize, spacing, textColor); // Main
}

int LoadHighScore()
{
    std::ifstream file("highscore.txt");
    int hs = 0;
    if (file.is_open()) file >> hs;
    return hs;
}

void SaveHighScore(int hs)
{
    std::ofstream file("highscore.txt");
    if (file.is_open()) file << hs;
}


enum GameState { START, SELECT_LEVEL, PLAYING, GAME_OVER, PAUSED };
GameState gameState = START;
int highScore = 0;

int selectedLevel = 1;          // 0 = Easy, 1 = Medium, 2 = Hard
double dropInterval = 0.2;      // Will be set based on selectedLevel

int main()
{
    InitWindow(500, 620, "raylib Tetris");
    SetTargetFPS(60);

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

    Game game = Game();
    highScore = LoadHighScore();


    while (!WindowShouldClose())
    {
        UpdateMusicStream(game.music);

        // Global pause toggle
        if (IsKeyPressed(KEY_P))
        {
            if (gameState == PLAYING) gameState = PAUSED;
            else if (gameState == PAUSED) gameState = PLAYING;
        }

        BeginDrawing();
        ClearBackground(darkBlue);

        // Fade overlay
        if (gameState == START || gameState == GAME_OVER)
        {
            fadeAlpha -= 0.01f;
            if (fadeAlpha < 0) fadeAlpha = 0;
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(darkBlue, fadeAlpha));
        }
        else
        {
            fadeAlpha = 1.0f;
        }

        if (gameState == START)
        {
            DrawRectangleRounded({50, 80, 400, 280}, 0.2, 10, darkGrey);

            DrawShadowedText(font, "TETRIS", {180, 100}, 48, 2, ORANGE);
            DrawShadowedText(font, "Press ENTER to Start", {110, 200}, 28, 2, WHITE);
            DrawShadowedText(font, "High Score:", {180, 300}, 28, 2, WHITE);

            char highScoreText[10];
            sprintf(highScoreText, "%d", highScore);
            DrawShadowedText(font, highScoreText, {350, 300}, 28, 2, YELLOW);

            if (IsKeyPressed(KEY_ENTER))
            {
                gameState = SELECT_LEVEL;  // 🚀 Go to level selection screen
            }

            if (IsKeyPressed(KEY_Q)) CloseWindow();
        }
        else if (gameState == SELECT_LEVEL)
        {
            DrawRectangleRounded({50, 80, 400, 330}, 0.2, 10, darkGrey);
            DrawShadowedText(font, "SELECT LEVEL", {110, 100}, 48, 2, WHITE);

            DrawShadowedText(font, "1 - EASY",   {150, 180}, 28, 2, selectedLevel == 0 ? YELLOW : WHITE);
            DrawShadowedText(font, "2 - MEDIUM", {150, 230}, 28, 2, selectedLevel == 1 ? YELLOW : WHITE);
            DrawShadowedText(font, "3 - HARD",   {150, 280}, 28, 2, selectedLevel == 2 ? YELLOW : WHITE);
            DrawShadowedText(font, "Press ENTER to Start", {80, 340}, 28, 2, GREEN);

            if (IsKeyPressed(KEY_ONE)) selectedLevel = 0;
            if (IsKeyPressed(KEY_TWO)) selectedLevel = 1;
            if (IsKeyPressed(KEY_THREE)) selectedLevel = 2;

            if (IsKeyPressed(KEY_ENTER))
            {
                // Set drop speed based on level
                if (selectedLevel == 0) dropInterval = 0.4;
                else if (selectedLevel == 1) dropInterval = 0.2;
                else if (selectedLevel == 2) dropInterval = 0.07;

                game.Reset();
                gameState = PLAYING;
            }
        }
        else if (gameState == PLAYING)
        {
            game.HandleInput();
            if (EventTriggered(dropInterval)) game.MoveBlockDown();

            DrawShadowedText(font, "Level", {370, 420}, 28, 2, WHITE);

            const char* levelText = selectedLevel == 0 ? "Easy" :
                                    selectedLevel == 1 ? "Medium" : "Hard";
            DrawShadowedText(font, levelText, {370, 460}, 28, 2, YELLOW);

            DrawShadowedText(font, "Score", {365, 15}, 38, 2, WHITE);
            DrawShadowedText(font, "Next", {370, 175}, 38, 2, WHITE);

            DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);
            char scoreText[10];
            sprintf(scoreText, "%d", game.score);
            Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
            DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);

            DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);

            game.Draw();

            if (game.gameOver)
        {
            if (game.score > highScore)
            {
                highScore = game.score;
                SaveHighScore(highScore);  // ✅ Save to file
            }
            gameState = GAME_OVER;  // ✅ Set game state to show Game Over screen
        }
        
        
            if (game.score > highScore)
            {
                highScore = game.score;
                SaveHighScore(highScore);  // ✅ Save to file
            }

        }
        else if (gameState == GAME_OVER)
        {
            DrawRectangleRounded({50, 180, 400, 250}, 0.2, 10, darkGrey);

            DrawShadowedText(font, "GAME OVER", {140, 200}, 48, 2, RED);
            DrawShadowedText(font, "Press ENTER to Restart", {90, 300}, 28, 2, WHITE);
            DrawShadowedText(font, "Press Q to Quit", {140, 350}, 28, 2, WHITE);

            if (IsKeyPressed(KEY_ENTER))
            {
                gameState = SELECT_LEVEL;  // 🌟 Let player choose again
            }

            if (IsKeyPressed(KEY_Q))
            {
                CloseWindow();
            }
        }
        else if (gameState == PAUSED)
        {
            DrawShadowedText(font, "PAUSED", {185, 260}, 48, 2, YELLOW);
            DrawShadowedText(font, "Press P to Resume", {130, 320}, 28, 2, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();
}
