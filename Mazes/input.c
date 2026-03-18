#include "input.h"
#include "display.h"
#include "new.h"
#include <string.h>

void init_input(Input *input) {
  int x, y;
  getmaxyx(stdscr, y, x);
  int split_point = x / SCREEN_SPLIT_RATIO;
  input->win = newwin(y, split_point, 0, 0);

  zero(input->curser_pos);
  zero(input->indicators);
  zero(input->start_pos);
  zero(input->end_pos);
}

void draw_input(Input *input) {
  wclear(input->win);
  int x, y;
  getmaxyx(input->win, x, y);

  wborder(input->win, WALL_CHAR, WALL_CHAR, WALL_CHAR, WALL_CHAR, WALL_CHAR,
          WALL_CHAR, WALL_CHAR, WALL_CHAR);

  wprintw(input->win, "Indicators:");
  wprintw(input->win, "1. (%d, %d)", input->indicators[0].x,
          input->indicators[0].y);
  wprintw(input->win, "2. (%d, %d)", input->indicators[1].x,
          input->indicators[1].y);
  wprintw(input->win, "Start and end:");
  wprintw(input->win, "Start: (%d, %d)", input->start_pos.x,
          input->start_pos.y);
  wprintw(input->win, "End:   (%d, %d)", input->end_pos.x, input->end_pos.y);

  wnoutrefresh(input->win);
}

void resize_input(Input *input) {
  int x, y;
  getmaxyx(stdscr, y, x);
  int split_point = x / SCREEN_SPLIT_RATIO;
  wresize(input->win, y, split_point);
}

void free_input(Input *input) { delwin(input->win); }
