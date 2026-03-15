#include "maze.h"
#include "display.h"
#include <stdbool.h>

const Maze possible_mazes[9] = {{{{false, false, true, false, false},
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
                                {{{false, false, true, false, false},
                                  {false, true, false, true, false},
                                  {true, false, true, false, false},
                                  {false, true, false, true, true},
                                  {true, true, true, false, true},
                                  {true, false, true, false, false}},
                                 {{true, false, true, false, false, true},
                                  {false, true, false, true, true, false},
                                  {false, false, true, false, true, false},
                                  {false, true, false, true, false, false},
                                  {false, false, false, false, true, false}},
                                 {{4, 1}, {1, 3}}},
                                {{{false, false, true, true, false},
                                  {true, true, true, false, true},
                                  {false, true, true, false, true},
                                  {true, true, true, true, true},
                                  {true, false, true, true, true},
                                  {false, false, false, true, false}},
                                 {{false, true, false, false, false, false},
                                  {true, false, false, true, true, false},
                                  {false, false, false, false, false, false},
                                  {false, false, false, false, false, false},
                                  {false, true, true, false, false, false}},
                                 {{3, 3}, {5, 3}}},
                                {{{false, true, false, false, false},
                                  {true, true, false, false, false},
                                  {true, false, true, false, true},
                                  {true, false, false, false, false},
                                  {false, false, false, false, true},
                                  {false, false, true, false, true}},
                                 {{false, false, true, true, true, false},
                                  {false, false, false, true, true, false},
                                  {false, true, true, false, true, false},
                                  {false, true, true, true, true, false},
                                  {false, true, true, true, false, false}},
                                 {{0, 0}, {0, 3}}},
                                {{{false, false, false, false, false},
                                  {false, false, false, false, true},
                                  {false, true, false, true, false},
                                  {true, false, false, true, true},
                                  {true, false, false, false, true},
                                  {true, false, false, false, false}},
                                 {{true, true, true, true, false, false},
                                  {false, true, true, false, true, true},
                                  {false, false, true, true, false, false},
                                  {false, true, true, false, true, false},
                                  {false, false, true, true, true, false}},
                                 {{4, 2}, {3, 5}}},
                                {{{true, false, true, false, false},
                                  {true, true, true, false, true},
                                  {false, true, true, true, false},
                                  {false, true, false, true, true},
                                  {false, true, true, true, false},
                                  {false, false, false, true, false}},
                                 {{false, false, false, true, false, false},
                                  {false, false, false, false, true, false},
                                  {false, true, true, false, false, true},
                                  {true, false, false, false, false, false},
                                  {false, true, true, false, true, false}},
                                 {{4, 0}, {2, 4}}},
                                {{{false, false, false, true, false},
                                  {true, false, true, false, true},
                                  {false, true, false, true, false},
                                  {false, true, false, false, true},
                                  {true, true, false, false, true},
                                  {false, false, false, false, false}},
                                 {{false, true, true, false, false, false},
                                  {false, false, true, true, true, false},
                                  {true, true, false, true, false, true},
                                  {false, false, false, true, true, false},
                                  {false, true, true, true, false, false}},
                                 {{1, 0}, {1, 5}}},
                                {{}, {}, {{}, {}}},
                                {{}, {}, {{}, {}}}};

int get_maze_side_length(int max_side_length) {
  int none_boarder_side_length = max_side_length - (2 + 5 * WALL_THICKNESS);
  if (max_side_length <= 0) {
    return -1;
  }
  return max_side_length - none_boarder_side_length % 6;
}

void init_maze(MazeDisplay *maze) {
  int x, y;
  getmaxyx(stdscr, y, x);
  int split_point = x / SCREEN_SPLIT_RATIO + 1;

  int side_length, x_pos, y_pos;

  if (x - split_point > y) {
    side_length = get_maze_side_length(y);
    y_pos = (y - side_length) / 2;
    x_pos = split_point + (x - split_point - side_length) / 2;
  } else {
    side_length = get_maze_side_length(x - split_point);
    y_pos = (y - side_length) / 2;
    x_pos = split_point + (x - split_point - side_length) / 2;
  }
  maze->win = newwin(side_length, side_length, y_pos, x_pos);

  maze->current_maze = &possible_mazes[6];
}

void draw_maze(MazeDisplay *maze) {
  wclear(maze->win);
  int x, y;
  getmaxyx(maze->win, x, y);

  int cell_size = (x - (2 + 5 * WALL_THICKNESS)) / 6;

  wattron(maze->win, COLOR_PAIR(WALL_COLOR));
  wborder(maze->win, WALL_CHAR, WALL_CHAR, WALL_CHAR, WALL_CHAR, WALL_CHAR,
          WALL_CHAR, WALL_CHAR, WALL_CHAR);

  for (int r = 1; r < y - 1; r++) {
    for (int c = 1; c < x - 1; c++) {
      Point pos = {(c - 1) / (cell_size + WALL_THICKNESS),
                   (r - 1) / (cell_size + WALL_THICKNESS)};
      bool is_vertical_wall = c % (cell_size + WALL_THICKNESS) < WALL_THICKNESS;
      bool is_horizontal_wall =
          r % (cell_size + WALL_THICKNESS) < WALL_THICKNESS;

      if (is_vertical_wall && is_horizontal_wall) {
        mvwaddch(maze->win, r, c, WALL_INTERSECT_CHAR);
      } else if (is_vertical_wall) {
        if (maze->current_maze->vertical_walls[pos.y][pos.x]) {
          mvwaddch(maze->win, r, c, WALL_CHAR);
        }
      } else if (is_horizontal_wall) {
        if (maze->current_maze->horizontal_walls[pos.y][pos.x]) {
          mvwaddch(maze->win, r, c, WALL_CHAR);
        }
      }
    }
  }
  wattroff(maze->win, COLOR_PAIR(WALL_COLOR));

  WINDOW *w = derwin(
      maze->win, cell_size, cell_size,
      1 + maze->current_maze->indicator[0].y * (cell_size + WALL_THICKNESS),
      1 + maze->current_maze->indicator[0].x * (cell_size + WALL_THICKNESS));
  wattron(w, COLOR_PAIR(INDICATOR_COLOR));
  draw_circle(w);
  mvderwin(
      w, 1 + maze->current_maze->indicator[1].y * (cell_size + WALL_THICKNESS),
      1 + maze->current_maze->indicator[1].x * (cell_size + WALL_THICKNESS));
  draw_circle(w);
  wattroff(w, COLOR_PAIR(INDICATOR_COLOR));
  delwin(w);
  w = NULL;
  wnoutrefresh(maze->win);
}
void resize_maze(MazeDisplay *maze) {
  int x, y;
  getmaxyx(stdscr, y, x);
  int split_point = x / SCREEN_SPLIT_RATIO + 1;

  int side_length, x_pos, y_pos;

  if (x - split_point > y) {
    side_length = get_maze_side_length(y);
    y_pos = (y - side_length) / 2;
    x_pos = split_point + (x - split_point - side_length) / 2;
  } else {
    side_length = get_maze_side_length(x - split_point);
    y_pos = (y - side_length) / 2;
    x_pos = split_point + (x - split_point - side_length) / 2;
  }
  mvwin(maze->win, y_pos, x_pos);
  wresize(maze->win, side_length, side_length);
}

void free_maze(MazeDisplay *maze) { delwin(maze->win); }

#define CIRCLE_ERROR 1;
void draw_circle(WINDOW *win) {
  int x_max, y_max;
  getmaxyx(win, x_max, y_max);

  int center = x_max / 2;
  int radius = (x_max - 2) / 2;

  int x = radius;
  int y = 0;
  int err = CIRCLE_ERROR;

  while (x >= y) {
    mvwaddch(win, center + y, center + x, 'o');
    mvwaddch(win, center + x, center + y, 'o');
    mvwaddch(win, center + x, center - y, 'o');
    mvwaddch(win, center + y, center - x, 'o');
    mvwaddch(win, center - y, center - x, 'o');
    mvwaddch(win, center - x, center - y, 'o');
    mvwaddch(win, center - x, center + y, 'o');
    mvwaddch(win, center - y, center + x, 'o');

    if (err <= 0) {
      y += 1;
      err += 2 * y + 1;
    }

    if (err > 0) {
      x -= 1;
      err -= 2 * x + 1;
    }
  }
}
