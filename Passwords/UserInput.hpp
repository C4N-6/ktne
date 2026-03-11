#pragma once

#include <array>
#include <ncurses.h>

#include "Answer.hpp"

#define NUMBER_OF_WORDS 35

#define EMPTY_CHAR '_'

#define NUMBER_OF_SPACES_BETWEEN_WORDS 4
#define NUMBER_OF_NEWLINES_BETWEEN_WORDS 2

#define NUMBER_OF_SPACES_BETWEEN_INPUT_CHARS 9
#define NUMBER_OF_NEWLINES_BETWEEN_INPUT_CHARS 2

void drawFrame(const UserInput &userInput);

constexpr std::array<std::string_view, NUMBER_OF_WORDS> passwords{
    "about", "after", "again", "below", "could", "every", "first",
    "found", "great", "house", "large", "learn", "never", "other",
    "place", "plant", "point", "right", "small", "sound", "spell",
    "still", "study", "their", "there", "these", "thing", "think",
    "three", "water", "where", "which", "world", "would", "write"};

class UserInput {
  struct Point {
    int x;
    int y;
  } m_curserPos = {0, 0};
  std::array<std::array<char, 6>, 5> m_input{};

public:
  UserInput(int x, int y) : m_curserPos{x, y} {}
  UserInput(int argc, char *argv[]) {
    m_input.at(0);
    for (int i = 1; i < argc; i++) {
      for (int j = 0; j < 6 && argv[i][j] != '\0'; j++) {
        m_input.at(i - 1).at(j) = argv[i][j];
      }
    }
  }

  void moveCurser(int dx, int dy) {
    int temp = m_curserPos.x + dx;
    if (temp >= 0 && temp < 5) {
      m_curserPos.x += dx;
    }
    temp = m_curserPos.y + dy;
    if (temp >= 0 && temp < 6) {
      m_curserPos.y += dy;
    }

    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    move((NUMBER_OF_WORDS / (cols / (5 + NUMBER_OF_SPACES_BETWEEN_WORDS))) *
                 NUMBER_OF_NEWLINES_BETWEEN_WORDS +
             (m_curserPos.y + 1) * NUMBER_OF_NEWLINES_BETWEEN_INPUT_CHARS,
         ((cols - 5 * (1 + NUMBER_OF_SPACES_BETWEEN_INPUT_CHARS)) / 2) +
             m_curserPos.x * (1 + NUMBER_OF_SPACES_BETWEEN_INPUT_CHARS));
  }
  void setChar(char c) {
    c = std::tolower(c);
    if (std::isalpha(c)) {
      m_input.at(m_curserPos.x).at(m_curserPos.y) = c;
      drawFrame(*this);
    }
  }
  void delChar() {
    m_input.at(m_curserPos.x).at(m_curserPos.y) = '\0';
    drawFrame(*this);
  }

  char getCharAt(int x, int y) const { return m_input.at(x).at(y); }
  const Point &getCurserPosition() const { return m_curserPos; }
  std::array<Answer, NUMBER_OF_WORDS> getAnswer() const;
};
