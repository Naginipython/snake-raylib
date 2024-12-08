#pragma once
#include <raylib.h>
#include <vector>

enum Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

class Game {
  const int width{20};
  const int height{20};
  const int TITLEBAR_HEIGHT{50};

  Vector2 goal;
  std::vector<Vector2> snake;
  Direction direction;
  double lastUpdateTime{};
  bool gameOver{};
  bool paused{};
  bool justReset{};

  void move_snake();
  void reset();
 public:
  Game();
  void update();
  void draw();
};