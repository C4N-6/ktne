CXXFLAGS += -std=c++20 $(shell pkg-config --cflags ncurses)
CFLAGS   += $(shell pkg-config --cflags ncurses)
LDFLAGS  += $(shell pkg-config --libs ncurses)

out ?= /usr/local
BINDIR = $(out)/bin

all: out/passwords out/mazes

out/passwords: out/obj/passwords/Answer.o out/obj/passwords/UserInput.o out/obj/passwords/main.o
	@mkdir -p out
	$(CXX) $^ $(LDFLAGS) -o $@

out/obj/passwords/%.o: Passwords/%.cpp
	@mkdir -p out/obj/passwords
	$(CXX) $(CXXFLAGS) -c $< -o $@

out/mazes: out/obj/mazes/main.o
	@mkdir -p out
	$(CC) $^ $(LDFLAGS) -o $@

out/obj/mazes/%.o: Mazes/%.c
	@mkdir -p out/obj/mazes
	$(CC) $(CFLAGS) -c $< -o $@

install: all
	install -D out/passwords $(BINDIR)/ktne-passwords
	install -D out/mazes $(BINDIR)/ktne-mazes

.PHONY: clean install
clean:
	rm -rf out/passwords
