#include "display.h"
#include "maze.h"
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
  use_default_colors();

  init_pair(WALL_COLOR, COLOR_RED, -1);
  init_pair(INDICATOR_COLOR, COLOR_GREEN, -1);

  refresh(); // I do not know why I have to call this but it is making my output
             // showing so I am calling it

  Display disp;
  init_display(&disp);

  draw_display(&disp);

  int input;
  do {
    input = getch();
    if (input == KEY_RESIZE) {
      resize_display(&disp);
    }

  } while (input != 'q');

  endwin();
  return EXIT_SUCCESS;
}
