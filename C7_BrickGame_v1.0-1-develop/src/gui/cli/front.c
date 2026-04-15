#include "front.h"

int main() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);
  nodelay(stdscr, TRUE);

  run_game_loop();

  endwin();
  return 0;
}

bool run_game_loop() {
  UserAction_t user_action;
  bool is_ok = true;
  Interface_t windows;
  windows.game_win = newwin(FIELD_WIDTH * 2 + 2, FIELD_HEIGHT + 2, 1, 1);
  windows.next_win = newwin(7, 18, 1, FIELD_WIDTH * 2 + 3);
  windows.info_win = newwin(15, 18, 8, FIELD_WIDTH * 2 + 3);

  start_color();
  init_pair((short)1, COLOR_BLACK, COLOR_YELLOW);
  init_pair((short)2, COLOR_BLACK, COLOR_CYAN);
  init_pair((short)3, COLOR_BLACK, COLOR_MAGENTA);
  init_pair((short)4, COLOR_BLACK, COLOR_GREEN);
  init_pair((short)5, COLOR_BLACK, COLOR_RED);
  init_pair((short)6, COLOR_BLACK, COLOR_BLUE);
  init_pair((short)7, COLOR_BLACK, COLOR_WHITE);

  while (is_ok) {
    GameInfo_t gameInfo = updateCurrentState();

    if (gameInfo.pause != EXIT_GAME) {
      print_field(&gameInfo, &windows);
      print_next(&gameInfo, &windows);
      print_info(&gameInfo, &windows);

      int key = getch();
      bool hold = (key != ERR);
      user_action = get_action(key);
      userInput(user_action, hold);

      free_game_info(&gameInfo);

      refresh();
      napms(5);
    } else
      is_ok = false;
  }

  delwin(windows.game_win);
  delwin(windows.next_win);
  delwin(windows.info_win);

  return 0;
}

void free_game_info(GameInfo_t *gameInfo) {
  if (gameInfo->field) {
    for (int i = 0; i < FIELD_HEIGHT; i++) {
      free(gameInfo->field[i]);
      gameInfo->field[i] = NULL;
    }
    free(gameInfo->field);
    gameInfo->field = NULL;

    if (gameInfo->next) {
      for (int i = 0; i < TETR_SIZE; i++) {
        free(gameInfo->next[i]);
        gameInfo->next[i] = NULL;
      }
      free(gameInfo->next);
      gameInfo->next = NULL;
    }
  }
}

void print_field(const GameInfo_t *gameInfo, Interface_t *windows) {
  werase(windows->game_win);
  box(windows->game_win, 0, 0);
  for (int y = 0; y < FIELD_HEIGHT; ++y) {
    for (int x = 0; x < FIELD_WIDTH; ++x) {
      if (gameInfo->field[y][x]) {
        if (gameInfo->pause) {
          mvwaddch(windows->game_win, y + 1, x * 2 + 1, '[');
          mvwaddch(windows->game_win, y + 1, x * 2 + 2, ']');
        } else {
          wattron(windows->game_win, COLOR_PAIR(gameInfo->field[y][x]));
          mvwaddch(windows->game_win, y + 1, x * 2 + 1, ' ');
          mvwaddch(windows->game_win, y + 1, x * 2 + 2, ' ');
          wattroff(windows->game_win, COLOR_PAIR(gameInfo->field[y][x]));
        }
      } else {
        mvwaddch(windows->game_win, y + 1, x * 2 + 1, ' ');
        mvwaddch(windows->game_win, y + 1, x * 2 + 2, ' ');
      }
    }
  }
  wrefresh(windows->game_win);
}

void print_next(const GameInfo_t *gameInfo, Interface_t *windows) {
  werase(windows->next_win);
  box(windows->next_win, 0, 0);
  for (int y = 0; y < TETR_SIZE; ++y) {
    for (int x = 0; x < TETR_SIZE; ++x) {
      if (gameInfo->next[y][x]) {
        if (gameInfo->pause) {
          mvwaddch(windows->next_win, y + 1, x * 2 + 4, '[');
          mvwaddch(windows->next_win, y + 1, x * 2 + 5, ']');
        } else {
          wattron(windows->next_win, COLOR_PAIR(gameInfo->next[y][x]));
          mvwaddch(windows->next_win, y + 1, x * 2 + 4, ' ');
          mvwaddch(windows->next_win, y + 1, x * 2 + 5, ' ');
          wattroff(windows->next_win, COLOR_PAIR(gameInfo->next[y][x]));
        }
      } else {
        mvwaddch(windows->next_win, y + 1, x * 2 + 4, ' ');
        mvwaddch(windows->next_win, y + 1, x * 2 + 5, ' ');
      }
    }
  }

  wrefresh(windows->next_win);
}

void print_info(const GameInfo_t *gameInfo, Interface_t *windows) {
  int offset_high = offset_counter(gameInfo->high_score);
  int offset = offset_counter(gameInfo->score);
  werase(windows->info_win);
  box(windows->info_win, 0, 0);
  if (gameInfo->pause == 1) {
    mvwprintw(windows->info_win, 1, 4, "= PAUSE =");
    mvwprintw(windows->info_win, 3, 4, "press  'P'");
    mvwprintw(windows->info_win, 4, 4, "to  resume");
  } else if (gameInfo->pause == 2) {
    mvwprintw(windows->info_win, 1, 4, "= TETRIS =");
    mvwprintw(windows->info_win, 3, 3, "press 'ENTER'");
    mvwprintw(windows->info_win, 4, 5, "to start");
  }
  if (gameInfo->pause) {
    mvwprintw(windows->info_win, 5, 4, "press 'ESC'");
    mvwprintw(windows->info_win, 6, 6, "to exit");
    mvwprintw(windows->info_win, 9, 5, "CONTROL");
    mvwprintw(windows->info_win, 10, 2, "< arrow keys >");
    mvwprintw(windows->info_win, 11, 8, "v");
    mvwprintw(windows->info_win, 12, 5, "'space'");
    mvwprintw(windows->info_win, 13, 4, "to rotate");
  } else {
    mvwprintw(windows->info_win, 2, 4, "high score");
    mvwprintw(windows->info_win, 3, 8 - offset_high, "%d",
              gameInfo->high_score);
    mvwprintw(windows->info_win, 5, 6, "score");
    mvwprintw(windows->info_win, 6, 8 - offset, "%d", gameInfo->score);
    mvwprintw(windows->info_win, 8, 6, "speed");
    mvwprintw(windows->info_win, 9, 6, "%3.1f x",
              (float)gameInfo->speed * 0.3 + 1);
    mvwprintw(windows->info_win, 11, 6, "level");
    mvwprintw(windows->info_win, 12, 4, "%5d", gameInfo->level);
  }
  wrefresh(windows->info_win);
}

UserAction_t get_action(int key) {
  UserAction_t action;
  switch (key) {
    case ENTER_KEY:
      action = Start;
      break;
    case 'p':
    case 'P':
      action = Pause;
      break;
    case 'q':
    case 'Q':
      action = Terminate;
      break;
    case KEY_LEFT:
      action = Left;
      break;
    case KEY_RIGHT:
      action = Right;
      break;
    case KEY_DOWN:
      action = Down;
      break;
    case SPACE_KEY:
      action = Action;
      break;
    case KEY_UP:
      action = Up;
      break;
    default:
      break;
  }
  return action;
}

int offset_counter(int number) {
  int count = 0;

  while (number > 0) {
    count++;
    number /= 10;
  }

  return count / 2;
}