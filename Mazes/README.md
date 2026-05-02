# KTNE Maze Solver

A C-based interactive tool for navigating the "Mazes" module. It uses a specialized display and input system to help experts guide the defuser through the grid.

## dependence

- ncurses to render the maze grid directly in your terminal. (this needs to be installed on your system)

- stb_ds.h for dynamic arrays in C. (nothing has to be done already in project files)

## Building & Running

### How to Build:

Ensure you have gcc, ncurses, and pkg-config installed.

```Bash
make out/mazes
```

### How To run:

```Bash
./out/mazes
```
