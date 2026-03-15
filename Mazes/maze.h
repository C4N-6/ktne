#pragma once
#include <ncurses.h>

#define WALL_THICKNESS 1
#define WALL_CHAR '#'
#define WALL_INTERSECT_CHAR '+'
#define WALL_COLOR 1

#define INDICATOR_CHAR '*'
#define INDICATOR_COLOR 2

typedef struct _POINT {
  int x;
  int y;
} Point;

typedef struct _MAZE {
  bool vertical_walls[6][5];
  bool horizontal_walls[5][6];
  Point indicator[2];
} Maze;

extern const Maze possible_mazes[9];

typedef struct _MAZE_DISPLAY {
  WINDOW *win;
  const Maze *current_maze;
} MazeDisplay;

void init_maze(MazeDisplay *maze);
void draw_maze(MazeDisplay *maze);
void resize_maze(MazeDisplay *maze);
void free_maze(MazeDisplay *maze);

void draw_circle(WINDOW *win);
