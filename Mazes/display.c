#include "display.h"
#include "input.h"
#include "maze.h"
#include <ncurses.h>

void init_display(Display *disp) {
  init_input(&disp->input);
  init_maze(&disp->maze);
}

void draw_display(Display *disp) {
  draw_input(&disp->input);
  draw_maze(&disp->maze);
  doupdate();
}

void resize_display(Display *disp) {
  resize_input(&disp->input);
  resize_maze(&disp->maze);
  clear();
  wnoutrefresh(stdscr);
  draw_display(disp);
}

void free_display(Display *disp) {
  free_input(&disp->input);
  free_maze(&disp->maze);
}
