#include <array>
#include <iostream>
#include <ncurses.h>
#include <string>
#include <string_view>

const char *help{"passwords <COLUMN1> <COLUMN2> <COLUMN3> <COLUMN4> <COLUMN5>"};

const std::array<std::string_view, 35> passwords{
    "about", "after", "again", "below", "could", "every", "first",
    "found", "great", "house", "large", "learn", "never", "other",
    "place", "plant", "point", "right", "small", "sound", "spell",
    "still", "study", "their", "there", "these", "thing", "think",
    "three", "water", "where", "which", "world", "would", "write"};

bool isPassword(std::string_view str) {
  for (std::string_view strs : passwords) {
    if (str == strs) {
      return true;
    }
  }
  return false;
}

int main(int argc, char *argv[]) {
  if (argc != 6) {
    std::cerr << help << std::endl;
    return 1;
  }
  for (char c1 : std::string{argv[1]}) {
    for (char c2 : std::string{argv[2]}) {
      for (char c3 : std::string{argv[3]}) {
        for (char c4 : std::string{argv[4]}) {
          for (char c5 : std::string{argv[5]}) {
            std::string s{c1, c2, c3, c4, c5};
            if (isPassword(s)) {
              std::cout << s << std::endl;
              return 0;
            }
          }
        }
      }
    }
  }
  std::cerr << "no password found" << std::endl;
  return 1;
}
