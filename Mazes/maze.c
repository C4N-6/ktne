#include "maze.h"

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
                                {{}, {}, {{}, {}}},
                                {{}, {}, {{}, {}}},
                                {{}, {}, {{}, {}}},
                                {{}, {}, {{}, {}}},
                                {{}, {}, {{}, {}}},
                                {{}, {}, {{}, {}}},
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
  int split_point = x / 2 + 1;

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

  maze->current_maze = &possible_mazes[0];
}

void draw_maze(MazeDisplay *maze) {
  wclear(maze->win);
  int x, y;
  getmaxyx(maze->win, x, y);

  int cell_size = (x - (2 + 5 * WALL_THICKNESS)) / 6;

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
      } else { // is a cell
      }
    }
  }
  wnoutrefresh(maze->win);
}
void resize_maze(MazeDisplay *maze) {
  int x, y;
  getmaxyx(stdscr, y, x);
  int split_point = x / 2 + 1;

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
