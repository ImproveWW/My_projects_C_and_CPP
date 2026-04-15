#ifndef FRONT_H
#define FRONT_H

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../../brick_game/brick_game.h"

#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20
#define TETR_SIZE 5
#define SPACE_KEY ' '
#define ENTER_KEY 10
#define EXIT_GAME -1

typedef struct {
  WINDOW *game_win;
  WINDOW *next_win;
  WINDOW *info_win;
} Interface_t;

bool run_game_loop();
void print_field(const GameInfo_t *gameInfo, Interface_t *windows);
void print_next(const GameInfo_t *gameInfo, Interface_t *windows);
void print_info(const GameInfo_t *gameInfo, Interface_t *windows);
void free_game_info(GameInfo_t *gameInfo);
UserAction_t get_action(int key);
int offset_counter(int number);

#endif