#pragma once
#include <ncurses.h>

typedef struct _INPUT {
  WINDOW *win;
} Input;

void init_input(Input *input);
void draw_input(Input *input);
void free_input(Input *input);
