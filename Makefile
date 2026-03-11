CXXFLAGS += $(shell pkg-config --cflags ncurses)
LDFLAGS  += $(shell pkg-config --libs ncurses)

all: passwords/passwords

passwords/passwords: passwords/main.cpp
	@mkdir -p out
	g++ $(CXXFLAGS) passwords/main.cpp $(LDFLAGS) -o out/passwords

.PHONY: clean
clean:
	rm -rf out/passwords