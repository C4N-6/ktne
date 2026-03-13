#pragma once

#include <array>
#include <string_view>

#define COLOR_WRONG 1
#define COLOR_CORRECT 2
#define COLOR_IMPOSSIBLE 3
#define COLOR_OPTIMAL_COL 4

class UserInput;

class Answer {
public:
  enum class CharStatus {
    WE_DO_KNOW,
    CORRECT,
    WRONG,
  };

private:
  std::string_view m_word;
  std::array<CharStatus, 5> m_charStatus;

public:
  Answer(std::string_view word, const UserInput &input);
  void display() const;
  int statusCount(CharStatus s) const {
    int count{0};
    for (CharStatus c : m_charStatus) {
      if (c == s) {
        count++;
      }
    }
    return count;
  }
  bool isPossible() const {
    for (CharStatus c : m_charStatus) {
      if (c == CharStatus::WRONG) {
        return false;
      }
    }
    return true;
  }
};
