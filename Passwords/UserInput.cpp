#include "UserInput.hpp"
#include "Answer.hpp"
#include <algorithm>
#include <array>
#include <cstddef>
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

  int optimalCol = userInput.findOptimalColumToFill();

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
      if (j == optimalCol) {
        attron(COLOR_PAIR(COLOR_OPTIMAL_COL));
      }
      printw("%c", c);
      if (j == optimalCol) {
        attroff(COLOR_PAIR(COLOR_OPTIMAL_COL));
      }
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

void UserInput::moveCurser(int dx, int dy) {
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

int UserInput::findOptimalColumToFill() const {
  std::array<std::array<int, 26>, 5> characterDensity{};

  std::array<Answer, NUMBER_OF_WORDS> ans = getAnswer();

  for (int i{0}; i < characterDensity.size(); i++) {
    for (int j{0}; j < passwords.size(); j++) {
      if (ans.at(j).isPossible()) {
        characterDensity[i].at(passwords.at(j).at(i) - 97)++;
      }
    }
  }

  std::array<std::pair<int, size_t>, 5> maxCharDensity =
      [&characterDensity]<size_t... i>(std::index_sequence<i...>) {
        return std::array<std::pair<int, size_t>, 5>{std::pair<int, size_t>{
            *std::max_element(characterDensity.at(i).begin(),
                              characterDensity.at(i).end()),
            i}...};
      }(std::make_index_sequence<5>());

  std::sort(maxCharDensity.begin(), maxCharDensity.end(),
            [](std::pair<int, size_t> a, std::pair<int, size_t> b) {
              return a.first < b.first;
            });

  for (int i{0}; i < maxCharDensity.size(); i++) {
    if (!isColumFilled(maxCharDensity[i].second)) {
      return maxCharDensity[i].second;
    }
  }

  return -1;
}
