#include "display.h"
#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "");
  initscr();
  cbreak();
  noecho();
  if (has_colors() == FALSE) {
    endwin();
    fprintf(stderr, "Your terminal does not support color\n");
    return 1;
  }
  start_color();
  refresh();

  Display disp;
  init_display(&disp);

  draw_display(&disp);

  getch();

  endwin();
  return EXIT_SUCCESS;
}
