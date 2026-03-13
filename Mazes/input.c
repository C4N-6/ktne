#include "input.h"

void init_input(Input *input) {
  int x, y;
  getmaxyx(stdscr, y, x);
  int split_point = x / 2;
  input->win = newwin(y, split_point, 0, 0);
}

void draw_input(Input *input) {
  wclear(input->win);
  int x, y;
  getmaxyx(input->win, x, y);

  for (int i = 0; i < x * y; i++) {
    wprintw(input->win, "I");
  }

  wnoutrefresh(input->win);
}

void resize_input(Input *input) {
  int x, y;
  getmaxyx(stdscr, y, x);
  int split_point = x / 2;
  wresize(input->win, y, split_point);
}

void free_input(Input *input) { delwin(input->win); }
