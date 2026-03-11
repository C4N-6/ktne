#include <cctype>
#include <ncurses.h>

#include "Answer.hpp"
#include "UserInput.hpp"

const char *help{"passwords <COLUMN1> <COLUMN2> <COLUMN3> <COLUMN4> <COLUMN5>"};

int main(int argc, char *argv[]) {
  initscr();
  noecho();
  if (has_colors() == FALSE) {
    endwin();
    printf("Your terminal does not support color\n");
    return 1;
  }
  start_color();

  use_default_colors();
  init_pair(COLOR_WRONG, COLOR_RED, -1);
  init_pair(COLOR_CORRECT, COLOR_CORRECT, -1);
  init_color(COLOR_YELLOW, 420, 557, 137);
  init_pair(COLOR_OPTIMAL_COL, -1, COLOR_YELLOW);
  init_color(COLOR_BLACK, 412, 412, 412);
  init_pair(COLOR_IMPOSSIBLE, COLOR_BLACK, -1);

  int input;
  UserInput user{argc, argv};

  drawFrame(user);
  do {
    input = getch();
    if (input == 'j') {
      user.moveCurser(0, 1);
    } else if (input == 'k') {
      user.moveCurser(0, -1);
    } else if (input == 'l') {
      user.moveCurser(1, 0);
    } else if (input == 'h') {
      user.moveCurser(-1, 0);
    } else if (input == 'r') {
      user.setChar(getch());
    } else if (input == 'd') {
      user.delChar();
    } else if (input == KEY_RESIZE) {
      drawFrame(user);
    }
  } while (input != 'q');
  endwin();
  return 0;
}
