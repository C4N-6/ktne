#pragma once
#include "maze.h"
#include <ncurses.h>

enum frame_of_ref {
  top_left = 0b00,
  top_right = 0b01,
  bottom_left = 0b10,
  bottom_right = 0b11,
};

char *frame_of_ref_to_string(enum frame_of_ref ref);

typedef struct _INPUT {
  WINDOW *win;
  Point curser_pos;
  union {
    struct {
      Point indicators[2];
      Point start_pos;
      Point end_pos;
    };
    Point points[4];
  };
  enum frame_of_ref reference_frame;
} Input;

void init_input(Input *input);
void draw_input(Input *input);
void update_input_curser(Input *input);
void resize_input(Input *input);
void free_input(Input *input);
