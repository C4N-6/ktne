#pragma once
#include <ncurses.h>

typedef struct _POINT {
  int x;
  int y;
} Point;

typedef struct _MAZE {
  bool vertical_walls[6][5];
  bool horizontal_walls[5][6];
  Point indicator[2];
} Maze;

extern Maze possible_mazes[9];

typedef struct _MAZE_DISPLAY {
  WINDOW *win;
} MazeDisplay;

void init_maze(MazeDisplay *maze);
void draw_maze(MazeDisplay *maze);
void resize_maze(MazeDisplay *maze);
void free_maze(MazeDisplay *maze);
