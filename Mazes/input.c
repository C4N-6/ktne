#include "input.h"

void init_input(Input *input) {
  int x, y;
  getmaxyx(stdscr, y, x);
  int split_point = x / 2;
  input->win = newwin(0, split_point, 0, 0);
}

void draw_input(Input *input) {
  int x, y;
  getmaxyx(input->win, x, y);

  wrefresh(input->win);
}
void free_input(Input *input) { delwin(input->win); }
