#ifndef BRICK_GAME_H
#define BRICK_GAME_H

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

GameInfo_t updateCurrentState();
void userInput(UserAction_t action, bool hold);

#endif