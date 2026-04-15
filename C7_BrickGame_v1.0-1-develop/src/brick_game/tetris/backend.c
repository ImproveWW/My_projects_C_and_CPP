#include "backend.h"

GameInfo_t updateCurrentState() {
  ModelInfo_t *actual_info = get_info();
  GameInfo_t result = {NULL, NULL, 0, 0, 1, 0, 0};
  int errors = 0;
  if (!result.field)
    errors += create_matrix(&result.field, FIELD_HEIGHT, FIELD_WIDTH);
  if (!result.next) errors += create_matrix(&result.next, TETR_SIZE, TETR_SIZE);

  if (!errors)
    run_actions_by_state(actual_info);
  else {
    run_terminate_actions(actual_info);
    free_result(&result);
  }
  result.pause = actual_info->pause;

  if (actual_info->pause != EXIT_GAME) {
    copy_matrix(result.field, actual_info->field_base, FIELD_HEIGHT,
                FIELD_WIDTH);
    copy_matrix(result.next, actual_info->next_tetramino, TETR_SIZE, TETR_SIZE);
    set_tetramino_on_field(result.field, actual_info);

    result.score = actual_info->score;
    result.high_score = actual_info->high_score;
    result.level = actual_info->level;
    result.speed = actual_info->speed;
  } else {
    free_result(&result);
  }

  return result;
}

void userInput(UserAction_t action, bool hold) {
  ModelInfo_t *actual_info = get_info();
  actual_info->user_action = action;
  actual_info->hold = hold;
}

ModelInfo_t *get_info() {
  static ModelInfo_t actual_info;
  static bool is_initialized = false;
  if (!is_initialized) {
    int error = 0;
    actual_info.state = Start_state;
    actual_info.user_action = Up;
    actual_info.hold = false;
    error += create_matrix(&actual_info.field_base, FIELD_HEIGHT, FIELD_WIDTH);
    error += create_matrix(&actual_info.next_tetramino, TETR_SIZE, TETR_SIZE);
    actual_info.next_type = generate_next_tetramino(actual_info.next_tetramino);
    error +=
        create_matrix(&actual_info.current_tetramino, TETR_SIZE, TETR_SIZE);
    error += create_matrix(&actual_info.collision_test_tetramino, TETR_SIZE,
                           TETR_SIZE);
    actual_info.current_type = 0;
    actual_info.x_position = SPAWN_X_POSITION;
    actual_info.y_position = SPAWN_Y_POSITION;
    actual_info.score = 0;
    actual_info.high_score = read_score();
    actual_info.level = 1;
    actual_info.speed = 0;
    actual_info.pause = error ? EXIT_GAME : 0;
    actual_info.timer = update_timer();

    srand(time(NULL));

    is_initialized = true;
  }

  return &actual_info;
}

void run_actions_by_state(ModelInfo_t *actual_info) {
  switch (actual_info->state) {
    case Start_state:
      initialize_game(actual_info);
      break;
    case Spawn:
      spawn_tetramino(actual_info);
      break;
    case Moving:
      move_tetramino(actual_info);
      break;
    case Shifting:
      shift_tetramino(actual_info);
      break;
    case Attaching:
      attach_tetramino(actual_info);
      break;
    case Pause_state:
      pause_actions(actual_info);
      break;
    case Game_over:
      game_over_actions(actual_info);
      break;
    case Exit_state:
      run_terminate_actions(actual_info);
      break;
  }
}

void initialize_game(ModelInfo_t *actual_info) {
  if (actual_info->hold) {
    switch (actual_info->user_action) {
      case Start:
        reset_matrix(actual_info->field_base, FIELD_HEIGHT, FIELD_WIDTH);
        actual_info->score = 0;
        actual_info->level = 1;
        actual_info->speed = 0;
        actual_info->pause = 0;
        actual_info->high_score = read_score();
        actual_info->state = Spawn;
        break;
      case Terminate:
        actual_info->state = Exit_state;
        break;
      default:
        break;
    }
  }
}

void spawn_tetramino(ModelInfo_t *actual_info) {
  copy_matrix(actual_info->current_tetramino, actual_info->next_tetramino,
              TETR_SIZE, TETR_SIZE);

  actual_info->current_type = actual_info->next_type;
  reset_matrix(actual_info->next_tetramino, TETR_SIZE, TETR_SIZE);

  actual_info->next_type = generate_next_tetramino(actual_info->next_tetramino);

  actual_info->x_position = SPAWN_X_POSITION;
  actual_info->y_position = SPAWN_Y_POSITION;

  if (is_move_collision(actual_info)) {
    actual_info->state = Game_over;
  } else {
    actual_info->state = Moving;
  }
}

void calculate_lines(ModelInfo_t *actual_info) {
  int lines_cleared = 0;
  for (int y = 0; y < FIELD_HEIGHT; y++) {
    bool is_line_full = true;
    for (int x = 0; x < FIELD_WIDTH; x++) {
      if (actual_info->field_base[y][x] == 0) {
        is_line_full = false;
      }
    }
    if (is_line_full) {
      clear_line(actual_info->field_base, y);
      lines_cleared++;
    }
  }
  if (lines_cleared) {
    update_score(&(actual_info)->score, lines_cleared);
    update_speed_and_level(actual_info);
  }
}

void clear_line(int **field_base, int line) {
  while (line) {
    for (int i = 0; i < FIELD_WIDTH; i++) {
      field_base[line][i] = field_base[line - 1][i];
    }
    line--;
  }
}

void update_score(int *score, int lines_cleared) {
  int multiplier = 1;
  while (lines_cleared--) multiplier *= 2;
  *score += 100 * (multiplier - 1);
}

void update_speed_and_level(ModelInfo_t *actual_info) {
  if (actual_info->level <= 10) {
    actual_info->level = (actual_info->score / 600) + 1;
    if (actual_info->level > 10) {  // if 10 was skipped
      actual_info->level = 10;
    }
    actual_info->speed = actual_info->level - 1;
  }
}

void pause_actions(ModelInfo_t *actual_info) {
  if (actual_info->user_action == Pause) {
    actual_info->pause = 0;
    actual_info->state = Moving;
  } else if (actual_info->user_action == Terminate) {
    actual_info->state = Exit_state;
  }
}

void game_over_actions(ModelInfo_t *actual_info) {
  if (actual_info->score > actual_info->high_score) {
    write_score(actual_info->score);
  }
  actual_info->pause = 2;
  actual_info->state = Start_state;
}

void run_terminate_actions(ModelInfo_t *actual_info) {
  if (actual_info->score > actual_info->high_score) {
    write_score(actual_info->score);
  }
  if (actual_info->field_base)
    remove_matrix(&(actual_info)->field_base, FIELD_HEIGHT);
  if (actual_info->current_tetramino)
    remove_matrix(&(actual_info)->current_tetramino, TETR_SIZE);
  if (actual_info->next_tetramino)
    remove_matrix(&(actual_info)->next_tetramino, TETR_SIZE);
  if (actual_info->collision_test_tetramino)
    remove_matrix(&(actual_info)->collision_test_tetramino, TETR_SIZE);
  actual_info->pause = EXIT_GAME;
}

TetraminoType_t generate_next_tetramino(int **next) {
  TetraminoType_t random = 1 + (rand() % 7);
  fill_tetramino(next, random);
  if (random != O_tetramino) {
    int random_rotation = rand() % 4;
    while (random_rotation--) rotate(random, &next);
  }
  return random;
}

void fill_tetramino(int **filled, TetraminoType_t num) {
  switch (num) {
    case O_tetramino:
      for (int i = 1; i <= 2; i++) filled[1][i] = O_tetramino;
      for (int j = 1; j <= 2; j++) filled[2][j] = O_tetramino;
      break;
    case I_tetramino:
      for (int i = 0; i <= 3; i++) filled[2][i] = I_tetramino;
      break;
    case T_tetramino:
      filled[1][2] = T_tetramino;
      for (int i = 1; i <= 3; i++) filled[2][i] = T_tetramino;
      break;
    case S_tetramino:
      for (int i = 1; i <= 2; i++) filled[i][1] = S_tetramino;
      for (int j = 2; j <= 3; j++) filled[j][2] = S_tetramino;
      break;
    case Z_tetramino:
      for (int i = 1; i <= 2; i++) filled[2][i] = Z_tetramino;
      for (int j = 2; j <= 3; j++) filled[3][j] = Z_tetramino;
      break;
    case J_tetramino:
      filled[1][1] = J_tetramino;
      for (int i = 1; i <= 3; i++) filled[2][i] = J_tetramino;
      break;
    case L_tetramino:
      filled[1][3] = L_tetramino;
      for (int i = 1; i <= 3; i++) filled[2][i] = L_tetramino;
      break;
  }
}

long long int update_timer() {
  struct timeval current_time;
  gettimeofday(&current_time, NULL);
  return (long long int)current_time.tv_sec * 1000 +
         current_time.tv_usec / 1000;
}

int create_matrix(int ***matrix, int rows, int columns) {
  *matrix = NULL;
  int error = 0;
  if (rows <= 0 || columns <= 0) error++;
  if (!error) {
    (*matrix) = calloc(rows, sizeof(int *));
    if (!(*matrix)) error++;

    for (int i = 0; !error && i < rows; i++) {
      (*matrix)[i] = calloc(columns, sizeof(int));
      if (!(*matrix)[i]) {
        error++;
        for (int j = 0; j < i; j++) {
          free((*matrix)[j]);
          (*matrix)[j] = NULL;
        }
        free((*matrix));
        (*matrix) = NULL;
      }
    }
  }

  return error;
}

void remove_matrix(int ***matrix, int rows) {
  if (matrix && *matrix) {
    for (int i = 0; i < rows; i++) {
      if ((*matrix)[i]) {
        free((*matrix)[i]);
        (*matrix)[i] = NULL;
      }
    }
    free(*matrix);
    *matrix = NULL;
  }
}

void free_result(GameInfo_t *result) {
  if (result->field) remove_matrix(&result->field, FIELD_HEIGHT);
  if (result->next) remove_matrix(&result->next, TETR_SIZE);
}

void copy_matrix(int **dest, int **src, int rows, int columns) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      dest[i][j] = src[i][j];
    }
  }
}

void reset_matrix(int **src, int rows, int columns) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      src[i][j] = 0;
    }
  }
}

void set_tetramino_on_field(int **field, ModelInfo_t *actual_info) {
  for (int y = 0; y < TETR_SIZE; y++) {
    for (int x = 0; x < TETR_SIZE; x++) {
      int offset_y = actual_info->y_position + y;
      int offset_x = actual_info->x_position + x;

      if (offset_y >= 0 && offset_y < FIELD_HEIGHT && offset_x >= 0 &&
          offset_x < FIELD_WIDTH) {
        if (actual_info->current_tetramino[y][x] != 0) {
          field[offset_y][offset_x] = actual_info->current_tetramino[y][x];
        }
      }
    }
  }
}

void write_score(int high_score) {
  FILE *file = fopen("score.txt", "w");
  if (file) {
    fprintf(file, "%d", high_score);
    fclose(file);
  }
}

int read_score() {
  int high_score = 0;
  FILE *file = fopen("score.txt", "r");
  if (file) {
    fscanf(file, "%d", &high_score);
    fclose(file);
  }
  return high_score;
}