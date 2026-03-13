#include "maze.h"

Maze possible_mazes[9] = {{{{false, false, true, false, false},
                            {true, false, true, false, false},
                            {true, false, true, false, false},
                            {true, false, false, true, false},
                            {false, false, true, false, true},
                            {false, true, false, true, false}},
                           {{false, true, false, false, true, true},
                            {false, false, true, true, true, false},
                            {false, true, false, false, true, false},
                            {false, true, true, true, true, false},
                            {false, true, false, false, true, false}},
                           {{0, 1}, {5, 2}}},
                          {{}, {}, {{}, {}}},
                          {{}, {}, {{}, {}}},
                          {{}, {}, {{}, {}}},
                          {{}, {}, {{}, {}}},
                          {{}, {}, {{}, {}}},
                          {{}, {}, {{}, {}}},
                          {{}, {}, {{}, {}}},
                          {{}, {}, {{}, {}}}};

void init_maze(MazeDisplay *maze) {
  int x, y;
  getmaxyx(stdscr, y, x);
  int split_point = x / 2 + 1;

  if (x - split_point > y) {
    maze->win = newwin(y, y, 0, split_point + (x - split_point - y) / 2);
  } else {
    maze->win = newwin(x - split_point, x - split_point,
                       (y + split_point - x) / 2, split_point);
  }
}

void draw_maze(MazeDisplay *maze) {
  wclear(maze->win);
  int x, y;
  getmaxyx(maze->win, x, y);

  for (int r = 0; r < y; r++) {
    for (int c = 0; c < x; c++) {
      mvwaddch(maze->win, r, c, '&');
    }
  }
  wnoutrefresh(maze->win);
}
void resize_maze(MazeDisplay *maze) {
  int x, y;
  getmaxyx(stdscr, y, x);
  int split_point = x / 2 + 1;

  if (x - split_point > y) {
    mvwin(maze->win, 0, split_point + (x - split_point - y) / 2);
    wresize(maze->win, y, y);
  } else {
    mvwin(maze->win, (y + split_point - x) / 2, split_point);
    wresize(maze->win, x - split_point, x - split_point);
  }
}

void free_maze(MazeDisplay *maze) { delwin(maze->win); }
