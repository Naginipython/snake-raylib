#include "main.h"
#include "game.h"
#include <raylib.h>

int main(int argc, char* argv[]) {
  println("Hello, world!");
  // Initialize window
  InitWindow(800, 850, "Snake");
  SetTargetFPS(60);
  Game game;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    game.draw();
    game.update();
    EndDrawing();
  }
  return 0;
}