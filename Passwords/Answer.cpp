#include <ncurses.h>

#include "Answer.hpp"
#include "UserInput.hpp"

Answer::Answer(std::string_view word, const UserInput &input) : m_word{word} {
  for (int i = 0; i < m_charStatus.size(); i++) {
    m_charStatus.at(i) = CharStatus::WRONG;
    for (int j = 0; j < 6; j++) {
      char c = input.getCharAt(i, j);
      if (c == m_word.at(i)) {
        m_charStatus.at(i) = CharStatus::CORRECT;
        break;
      } else if (c == '\0') {
        m_charStatus.at(i) = CharStatus::WE_DO_KNOW;
      }
    }
  }
}
void Answer::display() const {
  int posible = statusCount(CharStatus::WRONG);
  for (int i = 0; i < m_word.size(); i++) {
    switch (m_charStatus[i]) {
    case CharStatus::WE_DO_KNOW:
      if (posible) {
        attron(COLOR_PAIR(COLOR_IMPOSSIBLE));
      }
      printw("%c", m_word.at(i));
      if (posible) {
        attroff(COLOR_PAIR(COLOR_IMPOSSIBLE));
      }
      break;
    case CharStatus::CORRECT:
      attron(COLOR_PAIR(COLOR_CORRECT));
      printw("%c", m_word.at(i));
      attroff(COLOR_PAIR(COLOR_CORRECT));
      break;
    case CharStatus::WRONG:
      attron(COLOR_PAIR(COLOR_WRONG));
      printw("%c", m_word.at(i));
      attroff(COLOR_PAIR(COLOR_WRONG));
      break;
    }
  }
}
