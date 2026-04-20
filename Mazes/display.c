#include "display.h"
#include "input.h"
#include "maze.h"
#include <ncurses.h>
#include <string.h>

void wprintw_centered(WINDOW *win, char *str) {
  int x, y;
  getmaxyx(win, x, y);
  wmove(win, y / 2, (x - strlen(str)) / 2);
  wprintw(win, "%s", str);
}

void init_display(Display *disp) {
  init_input(&disp->input);
  init_maze(&disp->maze);
}

void draw_display(Display *disp) {
  draw_maze(&disp->maze, disp->input.points + 2);
  draw_input(&disp->input);
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

void find_maze(Display *disp) {
  Point p[2] = {{disp->input.indicators[0].x, disp->input.indicators[0].y},
                {disp->input.indicators[1].x, disp->input.indicators[1].y}};

  point_convert_to_top_left_ref(&p[0], disp->input.reference_frame);
  point_convert_to_top_left_ref(&p[1], disp->input.reference_frame);

  for (int i = 0; i < sizeof(possible_mazes) / sizeof(Maze); i++) {
    if ((!point_cmp(&possible_mazes[i].indicators[0], &p[0]) ||
         !point_cmp(&possible_mazes[i].indicators[0], &p[1])) &&
        (!point_cmp(&possible_mazes[i].indicators[1], &p[0]) ||
         !point_cmp(&possible_mazes[i].indicators[1], &p[1]))) {
      disp->maze.current_maze = &possible_mazes[i];
      return;
    }
  }

  disp->maze.current_maze = NULL;
}
