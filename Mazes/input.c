#include "input.h"
#include "display.h"
#include "new.h"
#include <string.h>

char *frame_of_ref_to_string(enum frame_of_ref ref) {
  switch (ref) {
  case top_left:
    return "top left";
  case top_right:
    return "top right";
  case bottom_right:
    return "bottom right";
  case bottom_left:
    return "bottom left";
  default:
    return "unknown";
  }
}

void init_input(Input *input) {
  int x, y;
  getmaxyx(stdscr, y, x);
  int split_point = x / SCREEN_SPLIT_RATIO;
  input->win = newwin(y, split_point, 0, 0);

  zero(input->curser_pos);
  zero(input->indicators);
  zero(input->start_pos);
  zero(input->end_pos);
  input->reference_frame = top_left;
}

void draw_input(Input *input) {
  wclear(input->win);
  int x, y;
  getmaxyx(input->win, y, x);

  wborder(input->win, WALL_CHAR, WALL_CHAR, WALL_CHAR, WALL_CHAR, WALL_CHAR,
          WALL_CHAR, WALL_CHAR, WALL_CHAR);

  int xpading = (x <= 27) ? 2 : 4;
  int ypading = (y - 9) / 2;
  WINDOW *win =
      derwin(input->win, y - ypading * 2, x - xpading * 2, ypading, xpading);
  wprintw(win, "frame of reference:\n  %s\n\n",
          frame_of_ref_to_string(input->reference_frame));
  wprintw(win, "Indicators:\n");
  wprintw(win, "1. (%d, %d)\n", input->indicators[0].x, input->indicators[0].y);
  wprintw(win, "2. (%d, %d)\n\n", input->indicators[1].x,
          input->indicators[1].y);
  wprintw(win, "Start and end:\n");
  wprintw(win, "Start: (%d, %d)\n", input->start_pos.x, input->start_pos.y);
  wprintw(win, "End:   (%d, %d)\n", input->end_pos.x, input->end_pos.y);
  delwin(win);

  update_input_curser(input);

  wnoutrefresh(input->win);
}

void update_input_curser(Input *input) {
  int x, y;
  getmaxyx(input->win, y, x);

  int xpading = (x <= 27) ? 2 : 4;
  int ypading = (y - 9) / 2;

  wmove(input->win, 0, 0);
  if (input->curser_pos.y == 0) {
    wmove(input->win, ypading + 1,
          xpading + 2 +
              (input->reference_frame == top_right ||
                       input->reference_frame == top_left
                   ? 4
                   : 7) *
                  MIN(input->curser_pos.x, 1));
  } else if (input->curser_pos.y >= 1 && input->curser_pos.y <= 2) {
    wmove(input->win, ypading + 3 + input->curser_pos.y,
          xpading + 4 + 3 * MIN(input->curser_pos.x, 1));
  } else if (input->curser_pos.y >= 3 && input->curser_pos.y <= 4) {
    wmove(input->win, ypading + 5 + input->curser_pos.y,
          xpading + 8 + 3 * MIN(input->curser_pos.x, 1));
  }

  wnoutrefresh(input->win);
}

void resize_input(Input *input) {
  int x, y;
  getmaxyx(stdscr, y, x);
  int split_point = x / SCREEN_SPLIT_RATIO;
  wresize(input->win, y, split_point);
}

void free_input(Input *input) { delwin(input->win); }
