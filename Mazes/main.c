#include "display.h"
#include "input.h"
#include "maze.h"
#include "new.h"
#include <ctype.h>
#include <locale.h>
#include <ncurses.h>

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

  wnoutrefresh(stdscr); // I do not know why I have to call this but it is
                        // making my output showing so I am calling it

  Display disp;
  init_display(&disp);

  draw_display(&disp);

  int input;
  do {
    input = getch();
    if (input == KEY_RESIZE) {
      resize_display(&disp);
    } else if (input == 'j') {
      disp.input.curser_pos.y = MOD(disp.input.curser_pos.y + 1, 5);
      update_input_curser(&disp.input);
      doupdate();
    } else if (input == 'k') {
      disp.input.curser_pos.y = MOD(disp.input.curser_pos.y - 1, 5);
      update_input_curser(&disp.input);
      doupdate();
    } else if (input == 'l') {
      disp.input.curser_pos.x = MOD(disp.input.curser_pos.x + 1, 2);
      update_input_curser(&disp.input);
      doupdate();
    } else if (input == 'h') {
      disp.input.curser_pos.x = MOD(disp.input.curser_pos.x - 1, 2);
      update_input_curser(&disp.input);
      doupdate();
    } else if (input == 'r') {
      int replace_input = getch();
      if (disp.input.curser_pos.y == 0) { // change frame of reference
        if (replace_input == 't') {
          disp.input.reference_frame &= top_right;
        } else if (replace_input == 'b') {
          disp.input.reference_frame |= bottom_left;
        } else if (replace_input == 'l') {
          disp.input.reference_frame &= bottom_left;
        } else if (replace_input == 'r') {
          disp.input.reference_frame |= top_right;
        }
      } else { // change any points
        replace_input -= '0';
        if (replace_input >= 0 && replace_input <= 5) {
          // indexes into the exact curser position will change and replaces
          // that value with replace_input
          ((int *)&disp.input
               .points[disp.input.curser_pos.y - 1])[disp.input.curser_pos.x] =
              replace_input;
        }
      }
      find_maze(&disp);
      draw_display(&disp);
    } else if (input == 'J') {
      if (disp.input.curser_pos.y == 0) { // change frame of reference
        disp.input.reference_frame |= bottom_left;
      } else { // change any points
        Point *temp = disp.input.points + disp.input.curser_pos.y - 1;
        temp->y = MOD(temp->y - 1, 6);
      }
      find_maze(&disp);
      draw_display(&disp);
    } else if (input == 'K') {
      if (disp.input.curser_pos.y == 0) { // change frame of reference
        disp.input.reference_frame &= top_right;
      } else { // change any points
        Point *temp = disp.input.points + disp.input.curser_pos.y - 1;
        temp->y = MOD(temp->y + 1, 6);
      }
      find_maze(&disp);
      draw_display(&disp);
    } else if (input == 'L') {
      if (disp.input.curser_pos.y == 0) { // change frame of reference
        disp.input.reference_frame &= bottom_left;
      } else { // change any points
        // indexes into the exact curser position will change and replaces
        // that value with replace_input
        Point *temp = disp.input.points + disp.input.curser_pos.y - 1;
        temp->x = MOD(temp->x + 1, 6);
      }
      find_maze(&disp);
      draw_display(&disp);
    } else if (input == 'H') {
      if (disp.input.curser_pos.y == 0) { // change frame of reference
        disp.input.reference_frame |= top_right;
      } else { // change any points
        // indexes into the exact curser position will change and replaces
        // that value with replace_input
        Point *temp = disp.input.points + disp.input.curser_pos.y - 1;
        temp->x = MOD(temp->x - 1, 6);
      }
      find_maze(&disp);
      draw_display(&disp);
    }
  } while (input != 'q');

  endwin();
  return EXIT_SUCCESS;
}
