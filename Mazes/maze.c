#include "maze.h"

void init_maze(Maze *maze) {
  int x, y;
  getmaxyx(stdscr, y, x);
  int split_point = x / 2;
  maze->win = newwin(0, x - split_point - 1, 0, split_point + 1);

  getmaxyx(maze->win, y, x);
  if (x > y) {
    maze->maze_win = derwin(maze->win, y, y, 0, (x - y) / 2);
  } else {
    maze->maze_win = derwin(maze->win, x, x, (y - x) / 2, 0);
  }
}

void draw_maze(Maze *maze) {
  wclear(maze->maze_win);
  int x, y;
  getmaxyx(maze->maze_win, x, y);

  for (int r = 0; r < y; r++) {
    for (int c = 0; c < x; c++) {
      mvwaddch(maze->maze_win, r, c, '&');
    }
  }
  wrefresh(maze->maze_win);
}

void free_maze(Maze *maze) {
  delwin(maze->maze_win);
  delwin(maze->win);
}
