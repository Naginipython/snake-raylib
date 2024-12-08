#include "game.h"
#include "main.h"

Game::Game() {
  goal = {(float)GetRandomValue(0, width-1), (float)GetRandomValue(0, height-1)};
  snake.push_back({10, 10});
  snake.push_back({10, 11});
  direction = Direction::UP;
}

void Game::update() {
  if (gameOver && IsKeyPressed(KEY_SPACE)) reset();
  if (!gameOver) {
    // Lose conditions
    if (snake.front().x < 0 || snake.front().x >= width || snake.front().y < 0 || snake.front().y >= height) {
      WARN("You lose!");
      gameOver = true;
    }
    for (int i = 1; i < snake.size(); i++) {
      if (snake.front().x == snake[i].x && snake.front().y == snake[i].y) {
        WARN("You lose!");
        gameOver = true;
      }
    }

    // Handle Input
    if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) && direction != Direction::DOWN) direction = Direction::UP;
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S) && direction != Direction::UP) direction = Direction::DOWN;
    if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A) && direction != Direction::RIGHT) direction = Direction::LEFT;
    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D) && direction != Direction::LEFT) direction = Direction::RIGHT;
    if (IsKeyPressed(KEY_SPACE) && !justReset) paused = !paused;

    // Move snake
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime > 0.1 && !paused) {
      lastUpdateTime = currentTime;
      move_snake();
    }

    // Reach goal
    if (snake.front().x == goal.x && snake.front().y == goal.y) {
      goal = {(float)GetRandomValue(0, width-1), (float)GetRandomValue(0, height-1)};
      TRACE("Goal pos: " << goal.x << ", " << goal.y);
      snake.push_back(snake.back());
    }
    if (justReset) justReset = false;
  }
}

void Game::draw() {
  // Draw grid
  for (int i = 0; i < width; i++)
    for (int j = 0; j < height; j++)
      DrawRectangle(i * 40+1, j * 40+1 +TITLEBAR_HEIGHT, 40-2, 40-2, BLACK);
  // Draw snake
  for (auto& s : snake)
    DrawRectangle(s.x * 40+1, s.y * 40+1 +TITLEBAR_HEIGHT, 40-2, 40-2, LIME);
  // Draw head
  DrawRectangle(snake.front().x * 40+1, snake.front().y * 40+1 +TITLEBAR_HEIGHT, 40-2, 40-2, GREEN);
  // Draw goal
  DrawRectangle(goal.x * 40+1, goal.y * 40+1 +TITLEBAR_HEIGHT, 40-2, 40-2, RED);

  // Titlebar Left
  DrawRectangle(0, 0, GetScreenWidth(), TITLEBAR_HEIGHT, DARKGRAY);
  DrawTextEx(GetFontDefault(), "Score:", {10,0}, TITLEBAR_HEIGHT, 2, WHITE);
  // Titlebar Right
  const char* score = std::to_string(snake.size()).c_str();
  Vector2 textSize = MeasureTextEx(GetFontDefault(), score, TITLEBAR_HEIGHT, 2);
  DrawTextEx(GetFontDefault(), score, {GetScreenWidth()-textSize.x-10,0}, TITLEBAR_HEIGHT, 2, WHITE);

  if (paused) {
    DrawText("Paused", GetScreenWidth()/2 -20*4.5, GetScreenHeight()/2 -20, 40, YELLOW);
  }
  if (gameOver) {
    DrawText("Game Over", GetScreenWidth()/2 -20*4.5, GetScreenHeight()/2 -20, 40, RED);
  }
}

void Game::move_snake() {
  Vector2 new_head = snake.front();
  switch (direction) {
    case Direction::UP:
      new_head.y--;
      break;
    case Direction::DOWN:
      new_head.y++;
      break;
    case Direction::LEFT:
      new_head.x--;
      break;
    case Direction::RIGHT:
      new_head.x++;
      break;
  }
  snake.pop_back();
  snake.insert(snake.begin(), new_head);
}

void Game::reset() {
  gameOver = false;
  snake.clear();
  goal = {(float)GetRandomValue(0, width-1), (float)GetRandomValue(0, height-1)};
  snake.push_back({10, 10});
  snake.push_back({10, 11});
  direction = Direction::UP;
  justReset = true;
}