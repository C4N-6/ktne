CXXFLAGS += -std=c++20 $(shell pkg-config --cflags ncurses)
LDFLAGS  += $(shell pkg-config --libs ncurses)

out ?= /usr/local
BINDIR = $(out)/bin

all: out/passwords

out/passwords: passwords/main.cpp
	@mkdir -p out
	$(CXX) $(CXXFLAGS) passwords/main.cpp passwords/Answer.cpp passwords/UserInput.cpp $(LDFLAGS) -o out/passwords

install: out/passwords
	install -D out/passwords $(BINDIR)/passwords

.PHONY: clean
clean:
	rm -rf out/passwords
