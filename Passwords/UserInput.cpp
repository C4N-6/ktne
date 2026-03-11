#include "UserInput.hpp"
#include "Answer.hpp"
#include <ncurses.h>
#include <utility>
std::array<Answer, NUMBER_OF_WORDS> UserInput::getAnswer() const {
  std::array<Answer, NUMBER_OF_WORDS> ans = [this]<std::size_t... Is>(
                                                std::index_sequence<Is...>) {
    return std::array<Answer, NUMBER_OF_WORDS>{Answer(passwords[Is], *this)...};
  }(std::make_index_sequence<NUMBER_OF_WORDS>());

  std::sort(ans.begin(), ans.end(),
            [&](const Answer a, const Answer b) -> bool {
              int ia{a.statusCount(Answer::CharStatus::WRONG)},
                  ib{b.statusCount(Answer::CharStatus::WRONG)};
              if (ia != ib) {
                return ia > ib;
              }
              ia = a.statusCount(Answer::CharStatus::WE_DO_KNOW);
              ib = b.statusCount(Answer::CharStatus::WE_DO_KNOW);
              if (ia != ib) {
                return ia > ib;
              }
              return a.statusCount(Answer::CharStatus::CORRECT) <
                     b.statusCount(Answer::CharStatus::CORRECT);
            });

  return ans;
}

void drawFrame(const UserInput &userInput) {
  std::array<Answer, NUMBER_OF_WORDS> ans = userInput.getAnswer();

  int rows, cols;
  getmaxyx(stdscr, rows, cols);

  int wordsPerLine = cols / (5 + NUMBER_OF_SPACES_BETWEEN_WORDS);
  int padding =
      (cols - wordsPerLine * (5 + NUMBER_OF_SPACES_BETWEEN_WORDS)) / 2;

  clear();
  for (int j = 0; j < padding; j++) {
    printw(" ");
  }

  for (int i = 0; i < ans.size(); i++) {
    ans[i].display();
    if (i % wordsPerLine == wordsPerLine - 1) {
      for (int j = 0; j < NUMBER_OF_NEWLINES_BETWEEN_WORDS; j++) {
        printw("\n");
      }
      for (int j = 0; j < padding; j++) {
        printw(" ");
      }
    } else {
      for (int j = 0; j < NUMBER_OF_SPACES_BETWEEN_WORDS; j++) {
        printw(" ");
      }
    }
  }

  for (int j = 0; j < NUMBER_OF_NEWLINES_BETWEEN_INPUT_CHARS; j++) {
    printw("\n");
  }

  padding = (cols - 5 * (1 + NUMBER_OF_SPACES_BETWEEN_INPUT_CHARS)) / 2;

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < padding; j++) {
      printw(" ");
    }
    for (int j = 0; j < 5; j++) {
      char c = userInput.getCharAt(j, i);
      if (c == '\0') {
        c = EMPTY_CHAR;
      }
      printw("%c", c);
      if (j != 4) {
        for (int k = 0; k < NUMBER_OF_SPACES_BETWEEN_INPUT_CHARS; k++) {
          printw(" ");
        }
      }
    }
    for (int j = 0; j < NUMBER_OF_NEWLINES_BETWEEN_INPUT_CHARS; j++) {
      printw("\n");
    }
  }

  auto p = userInput.getCurserPosition();
  move((NUMBER_OF_WORDS / wordsPerLine) * NUMBER_OF_NEWLINES_BETWEEN_WORDS +
           (p.y + 1) * NUMBER_OF_NEWLINES_BETWEEN_INPUT_CHARS,
       padding + p.x * (1 + NUMBER_OF_SPACES_BETWEEN_INPUT_CHARS));
  refresh();
}
