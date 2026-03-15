#pragma once
#include "input.h"
#include "maze.h"
#include <ncurses.h>

#define SCREEN_SPLIT_RATIO 3

void wprintw_centered(WINDOW *win, char *str);

typedef struct _DISPLAY {
  Input input;
  MazeDisplay maze;
} Display;

void init_display(Display *disp);
void draw_display(Display *disp);
void resize_display(Display *disp);
void free_display(Display *disp);
