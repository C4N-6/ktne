#pragma once
#include <ncurses.h>

#define WALL_THICKNESS 1
#define WALL_CHAR '#'
#define WALL_INTERSECT_CHAR '+'
#define WALL_COLOR 1

#define INDICATOR_CHAR '*'
#define INDICATOR_COLOR 2

#define CIRCLE_ERROR 1;

typedef struct _POINT {
  int x;
  int y;
} Point;

int cmp_point(const Point *p1, const Point *p2);

enum direction {
  direction_up,
  direction_down,
  direction_left,
  direction_right,
};

typedef struct _MAZE {
  bool vertical_walls[6][5];
  bool horizontal_walls[5][6];
  Point indicators[2];
} Maze;

extern const Maze possible_mazes[9];

typedef struct _MAZE_DISPLAY {
  WINDOW *win;
  const Maze *current_maze;
} MazeDisplay;

typedef struct {
  Point p;
  enum direction d;
} Path;

void init_maze_display(MazeDisplay *maze);
void draw_maze_display(MazeDisplay *maze, Point start_and_end[2]);
void resize_maze_display(MazeDisplay *maze);
void free_maze_display(MazeDisplay *maze);

Path *pathfind(const Maze *m, Point start_and_end[2]);

WINDOW *init_cell_window(const MazeDisplay *maze, const Point *p);
void move_cell_window(const MazeDisplay *maze, WINDOW *win, const Point *p);

void draw_circle(WINDOW *win, char c);
void draw_triangle(WINDOW *win, char c);
void draw_arrow(WINDOW *win, enum direction d, char c);

void draw_line(WINDOW *win, const Point *p1, const Point *p2, char c);
