#include <iostream>
#include <time.h>
#include <math.h>
#include "raylib.h"

void DrawClockHand(int x, int y, int l, int w, Color c, float r);
void DrawFrame();
void GetClockTime();

const int screenWidth = 160;
const int screenHeight = 200;
const int clockWidth = (screenWidth / 2) * .9;
const int clockInteriorWidth = (screenWidth / 2) * .8;

time_t timestamp;
struct tm* now;
int day = 0;
int birthdayTimestamp = 0; // Insert birthday here to get elapsed days since birth

float second = 0;

int main(void) {
  SetConfigFlags(FLAG_VSYNC_HINT);
  
  InitWindow(screenWidth, screenHeight, "rlclock");
  
  Font clockFont = LoadFont("Font/7x13B.bdf");
    
  // Main game loop
  while (!WindowShouldClose()) {
    
    if (second <= 0) {
      
      GetClockTime();
      BeginDrawing();
      ClearBackground(RAYWHITE);

      DrawFrame();

      // Hour Hand
      DrawClockHand(screenWidth / 2, screenHeight / 2, 35, 2, BLACK, (now->tm_hour % 12) * 30);

      // Minute Hand
      DrawClockHand(screenWidth / 2, screenHeight / 2, 50, 2, BLACK, (now->tm_min * 6));
      // Second Hand
      DrawClockHand(screenWidth / 2, screenHeight / 2, 45, 1, RED, (now->tm_sec * 6));

      Vector2 textPos = {screenWidth / 2, screenHeight * .9};
      DrawTextEx(clockFont, TextFormat("Jour %i", ((int)(timestamp - birthdayTimestamp) / 86400)), textPos, 10, 2, BLACK);

      EndDrawing();
      second = 1;

    } else {
      second -= GetFrameTime();
    }

  }
    
  CloseWindow();
    
  return 0;
}

// Functions

void DrawClockHand(int x, int y, int l, int w, Color c, float r) {

  float rad = r * DEG2RAD;

  Vector2 start = { x, y };
  Vector2 end = { x + sin(rad) * l, y - cos(rad) * l };

  DrawLineEx(start, end, w, c);
}

void DrawFrame() {
  for(int i = 0; i < 60; i++){

    float rad = i * 6 * DEG2RAD;
    
    Vector2 dotPosition = {screenWidth  / 2 + sin(rad) * clockWidth,
			  screenHeight / 2 - cos(rad) * clockWidth};
    
    Vector2 dotEnd = {screenWidth  / 2 + sin(rad) * clockInteriorWidth,
			  screenHeight / 2 - cos(rad) * clockInteriorWidth};
    if (i % 5 == 0){
      DrawLineEx(dotPosition, dotEnd, 2, BLACK);
    } else {
      DrawLineEx(dotPosition, dotEnd, 1, BLACK);
    }
    
  }
}

void GetClockTime(){
  timestamp = time(NULL);
  now = localtime(&timestamp);
}
	      
