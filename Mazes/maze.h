#pragma once
#include <ncurses.h>

typedef struct _MAZE {
  WINDOW *win;
  WINDOW *maze_win;
} Maze;

void init_maze(Maze *maze);
void draw_maze(Maze *maze);
void resize_maze(Maze *maze);
void free_maze(Maze *maze);
