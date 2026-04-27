#include "maze.h"
#include "display.h"
#include "new.h"

#include "stb_ds.h"
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
                                {{{true, false, false, true, false},
                                  {false, false, true, false, true},
                                  {true, false, false, false, true},
                                  {true, false, true, false, false},
                                  {true, true, false, false, false},
                                  {false, false, false, false, false}},
                                 {{false, false, true, false, false, false},
                                  {false, true, true, true, true, false},
                                  {false, false, true, true, false, false},
                                  {false, true, false, true, true, true},
                                  {false, false, true, true, true, true}},
                                 {{2, 3}, {3, 0}}},
                                {{{true, false, false, false, false},
                                  {true, true, false, true, true},
                                  {false, false, true, false, true},
                                  {true, true, false, true, false},
                                  {true, true, true, false, true},
                                  {false, true, false, true, false}},
                                 {{false, false, true, true, false, false},
                                  {false, false, false, true, false, false},
                                  {false, true, true, false, true, false},
                                  {false, false, false, true, true, false},
                                  {false, false, false, false, false, true}},
                                 {{0, 4}, {2, 1}}}};

int cmp_point(const Point *p1, const Point *p2) {
  int temp = p2->x - p1->x;
  if (temp) {
    return temp;
  }
  return p2->y - p1->y;
}

int get_maze_side_length(int max_side_length) {
  int none_boarder_side_length = max_side_length - (2 + 5 * WALL_THICKNESS);
  if (max_side_length <= 0) {
    return -1;
  }
  return max_side_length - none_boarder_side_length % 6;
}

void init_maze_display(MazeDisplay *maze) {
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

  maze->current_maze = NULL;
}

void draw_maze_display(MazeDisplay *maze, Point start_and_end[2]) {
  wclear(maze->win);
  int x, y;
  getmaxyx(maze->win, x, y);

  int cell_size = (x - (2 + 5 * WALL_THICKNESS)) / 6;

  wattron(maze->win, COLOR_PAIR(WALL_COLOR));
  wborder(maze->win, WALL_CHAR, WALL_CHAR, WALL_CHAR, WALL_CHAR, WALL_CHAR,
          WALL_CHAR, WALL_CHAR, WALL_CHAR);
  if (maze->current_maze == NULL) {
    wattroff(maze->win, COLOR_PAIR(WALL_COLOR));
    wprintw_centered(maze->win, "no maze chosen");
    wnoutrefresh(maze->win);
    return;
  }

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
  WINDOW *w = init_cell_window(maze, &maze->current_maze->indicators[0]);
  wattron(w, COLOR_PAIR(INDICATOR_COLOR));
  draw_circle(w, 'o');
  move_cell_window(maze, w, &maze->current_maze->indicators[1]);
  draw_circle(w, 'o');
  wattroff(w, COLOR_PAIR(INDICATOR_COLOR));
  delwin(w);
  w = NULL;
  wnoutrefresh(maze->win);
}

void resize_maze_display(MazeDisplay *maze) {
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

void free_maze_display(MazeDisplay *maze) { delwin(maze->win); }

int find_point_in_paths(const Path *path_array, const Point *p) {
  for (int i = 0; i < arrlen(path_array); i++) {
    if (cmp_point(p, &path_array[i].p)) {
      return i;
    }
  }
  return -1;
}

bool pathfind_recursive(const Maze *m, const Point *end, const Point *curr,
                        Path *path) {
  if (cmp_point(end, curr) == 0) {
    return true;
  }
  for (enum direction d = direction_up; d <= direction_right; d++) {
    if (true /* TODO: check if there is a wall at that direction */) {
      Point nextPoint;

      // TODO: set nextPoint to the next point

      if (find_point_in_paths(path, &nextPoint) != -1 &&
          pathfind_recursive(m, end, &nextPoint, path)) {
        return true;
      }
    }
  }
  return false;
}

Path *pathfind(const Maze *m, Point start_and_end[2]) {
  Path *path = NULL;
  pathfind_recursive(m, &start_and_end[1], &start_and_end[0], path);
  return path;
}

WINDOW *init_cell_window(const MazeDisplay *maze, const Point *p) {
  int x = getmaxx(maze->win);
  int cell_size = (x - (2 + 5 * WALL_THICKNESS)) / 6;
  return derwin(maze->win, cell_size, cell_size,
                1 + p->y * (cell_size + WALL_THICKNESS),
                1 + p->x * (cell_size + WALL_THICKNESS));
}
void move_cell_window(const MazeDisplay *maze, WINDOW *win, const Point *p) {
  int x = getmaxx(maze->win);
  int cell_size = (x - (2 + 5 * WALL_THICKNESS)) / 6;
  mvderwin(win, 1 + p->y * (cell_size + WALL_THICKNESS),
           1 + p->x * (cell_size + WALL_THICKNESS));
}

void draw_circle(WINDOW *win, char c) {
  int x_max = getmaxx(win);

  int center = x_max / 2;
  int radius = (x_max - 2) / 2;

  int x = radius;
  int y = 0;
  int err = CIRCLE_ERROR;

  while (x >= y) {
    mvwaddch(win, center + y, center + x, c);
    mvwaddch(win, center + x, center + y, c);
    mvwaddch(win, center + x, center - y, c);
    mvwaddch(win, center + y, center - x, c);
    mvwaddch(win, center - y, center - x, c);
    mvwaddch(win, center - x, center - y, c);
    mvwaddch(win, center - x, center + y, c);
    mvwaddch(win, center - y, center + x, c);

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

void draw_triangle(WINDOW *win, char c) {
  int x, y;
  getmaxyx(win, y, x);

  Point corners[3] = {{x / 2, 1}, {1, y - 1}, {x - 1, y - 1}};

  draw_line(win, &corners[0], &corners[1], c);
  draw_line(win, &corners[1], &corners[2], c);
  draw_line(win, &corners[2], &corners[0], c);
}

void draw_arrow(WINDOW *win, enum direction d, char c) {
  int x, y;
  getmaxyx(win, y, x);

  Point start;
  Point ends[3];

  if (d == direction_up) {
    start.x = x / 2;
    start.y = 1;

    ends[0].x = x / 2;
    ends[0].y = y - 1;

    ends[1].x = x / 4;
    ends[1].y = x / 4;

    ends[2].x = 3 * x / 4;
    ends[2].y = x / 4;
  } else if (d == direction_down) {
    start.x = x / 2;
    start.y = y - 1;

    ends[0].x = x / 2;
    ends[0].y = 1;

    ends[1].x = x / 4;
    ends[1].y = 3 * x / 4;

    ends[2].x = 3 * x / 4;
    ends[2].y = 3 * x / 4;
  } else if (d == direction_right) {
    start.x = x - 1;
    start.y = y / 2;

    ends[0].x = 1;
    ends[0].y = y / 2;

    ends[1].x = 3 * x / 4;
    ends[1].y = x / 4;

    ends[1].x = 3 * x / 4;
    ends[1].y = 3 * x / 4;
  } else if (d == direction_left) {
    start.x = 1;
    start.y = y / 2;

    ends[0].x = x - 1;
    ends[0].y = y / 2;

    ends[1].x = x / 4;
    ends[1].y = x / 4;

    ends[1].x = x / 4;
    ends[1].y = 3 * x / 4;
  }

  for (int i = 0; i < ARRAY_SIZE(ends); i++) {
    draw_line(win, &start, &ends[i], c);
  }
}

void draw_line(WINDOW *win, const Point *p1, const Point *p2, char c) {
  if (p1->x > p2->x) {
    const Point *temp = p1;
    p1 = p2;
    p2 = temp;
  }

  int dx = p2->x - p1->x;
  int dy = p2->y - p1->y;

  float m = dy / (float)dx;

  if (m > 0) {
    int lastY = p1->y;
    for (int i = p1->x - 1; i <= p2->x; i++) {
      int y = m * (i - p1->x) + p1->y;
      for (int j = lastY; j < y; j += 1) {
        mvwaddch(win, j, i, c);
      }
      lastY = y;
    }
  } else if (m < 0) {
    int lastY = p2->y;
    for (int i = p1->x; i <= p2->x + 2; i++) {
      int y = m * (i - p1->x) + p1->y;
      for (int j = lastY; j > y; j -= 1) {
        mvwaddch(win, j, i - 2, c);
      }
      lastY = y;
    }
  } else {
    for (int i = p1->x - 1; i <= p2->x; i++) {
      mvwaddch(win, p1->y, i, c);
    }
  }
}
