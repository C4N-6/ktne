#pragma once
#include "maze.h"
#include <ncurses.h>

typedef struct _INPUT {
  WINDOW *win;
  Point curser_pos;
  Point indicators[2];
  Point start_pos;
  Point end_pos;
} Input;

void init_input(Input *input);
void draw_input(Input *input);
void resize_input(Input *input);
void free_input(Input *input);
