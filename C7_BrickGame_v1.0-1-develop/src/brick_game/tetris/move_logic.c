#include "backend.h"

void move_tetramino(ModelInfo_t *actual_info) {
  if (actual_info->hold) {
    switch (actual_info->user_action) {
      case Left:
        move_left(actual_info);
        break;
      case Right:
        move_right(actual_info);
        break;
      case Down:
        actual_info->state = Shifting;
        break;
      case Action:
        if (!is_rotation_blocked()) {
          copy_matrix(actual_info->current_tetramino,
                      actual_info->collision_test_tetramino, TETR_SIZE,
                      TETR_SIZE);
        }
        break;
      case Terminate:
      case Pause:
        actual_info->state = Pause_state;
        actual_info->pause = 1;
        break;
      default:
        break;
    }
  }
  if ((update_timer() - actual_info->timer) >=
      (700 - (actual_info->speed * 52))) {
    actual_info->timer = update_timer();
    actual_info->state = Shifting;
  }
}

void move_left(ModelInfo_t *actual_info) {
  actual_info->x_position--;
  if (is_move_collision(actual_info)) actual_info->x_position++;
}

void move_right(ModelInfo_t *actual_info) {
  actual_info->x_position++;
  if (is_move_collision(actual_info)) actual_info->x_position--;
}

int is_rotation_blocked() {
  ModelInfo_t *actual_info = get_info();
  int error = NO_COLLISION;
  copy_matrix(actual_info->collision_test_tetramino,
              actual_info->current_tetramino, TETR_SIZE, TETR_SIZE);
  rotate(actual_info->current_type, &(actual_info->collision_test_tetramino));
  error = check_rotate_collision(actual_info);

  int origin_x_position = actual_info->x_position;

  if (error == RIGHT_COLLISION && error != BASE_COLLISION) {
    actual_info->x_position--;
    error = check_rotate_collision(actual_info);
  }

  for (int counter = 2; error == LEFT_COLLISION && counter > 0; counter--) {
    if (error != BASE_COLLISION) {
      actual_info->x_position++;
      error = check_rotate_collision(actual_info);
    }
  }

  if (error == BASE_COLLISION) actual_info->x_position++;
  error = check_rotate_collision(actual_info);
  if (error == BASE_COLLISION) actual_info->x_position -= 2;
  error = check_rotate_collision(actual_info);
  if (error == BASE_COLLISION) actual_info->x_position += 3;
  error = check_rotate_collision(actual_info);

  if (error) actual_info->x_position = origin_x_position;

  return error;
}

void rotate(TetraminoType_t type, int ***straight) {
  switch (type) {
    case O_tetramino:
      break;
    case I_tetramino:
    case S_tetramino:
    case Z_tetramino:
      (*straight)[1][2] ? rotate_left(straight) : rotate_right(straight);
      break;
    case T_tetramino:
    case L_tetramino:
    case J_tetramino:
      rotate_right(straight);
      break;
  }
}

/**
 * @brief Rotates the tetramino counterclockwise (left).
 *
 * @param straight A pointer to the matrix representing the current tetramino.
 */
void rotate_left(int ***straight) {
  int **rotated = NULL;
  int error = create_matrix(&rotated, TETR_SIZE, TETR_SIZE);
  if (!error) {
    for (int i = 0; i < TETR_SIZE; i++) {
      for (int j = 0; j < TETR_SIZE; j++) {
        rotated[TETR_SIZE - 1 - j][i] = (*straight)[i][j];
      }
    }
    copy_matrix(*straight, rotated, TETR_SIZE, TETR_SIZE);
    remove_matrix(&rotated, TETR_SIZE);
  }
}

void rotate_right(int ***straight) {
  int **rotated = NULL;
  int error = create_matrix(&rotated, TETR_SIZE, TETR_SIZE);
  if (!error) {
    for (int i = 0; i < TETR_SIZE; i++) {
      for (int j = 0; j < TETR_SIZE; j++) {
        rotated[j][TETR_SIZE - 1 - i] = (*straight)[i][j];
      }
    }
    copy_matrix(*straight, rotated, TETR_SIZE, TETR_SIZE);
    remove_matrix(&rotated, TETR_SIZE);
  }
}

void shift_tetramino(ModelInfo_t *actual_info) {
  actual_info->y_position++;
  if (is_move_collision(actual_info)) {
    actual_info->y_position--;
    actual_info->state = Attaching;
  } else
    actual_info->state = Moving;
}

void attach_tetramino(ModelInfo_t *actual_info) {
  set_tetramino_on_field(actual_info->field_base, actual_info);
  calculate_lines(actual_info);
  actual_info->state = Spawn;
}

int is_move_collision(const ModelInfo_t *actual_info) {
  int error = NO_COLLISION;

  for (int i = 0; i < TETR_SIZE; i++) {
    for (int j = 0; j < TETR_SIZE; j++) {
      int x_offset = actual_info->x_position + j;
      int y_offset = actual_info->y_position + i;

      if (actual_info->current_tetramino[i][j] != 0 && !error) {
        if (y_offset >= FIELD_HEIGHT) {
          error = FLOOR_COLLISION;
        } else if (x_offset < 0) {
          error = BASE_COLLISION;
        } else if (y_offset >= 0 &&
                   actual_info->field_base[y_offset][x_offset] != 0) {
          error = BASE_COLLISION;
        }
      }
    }
  }
  return error;
}

int check_rotate_collision(const ModelInfo_t *actual_info) {
  int error = NO_COLLISION;
  for (int i = 0; i < TETR_SIZE; i++) {
    for (int j = 0; j < TETR_SIZE; j++) {
      int x_offset = actual_info->x_position + j;
      int y_offset = actual_info->y_position + i;

      if (y_offset >= FIELD_HEIGHT &&
          actual_info->collision_test_tetramino[i][j] != 0) {
        error = FLOOR_COLLISION;
      } else if (actual_info->collision_test_tetramino[i][j] != 0) {
        if (x_offset < 0) {
          error = LEFT_COLLISION;
        } else if (x_offset >= FIELD_WIDTH) {
          error = RIGHT_COLLISION;
        } else if (y_offset >= 0 &&
                   actual_info->field_base[y_offset][x_offset] != 0)
          error = BASE_COLLISION;
      }
    }
  }
  return error;
}