#include <ncurses.h>
 
int main() {
  // Initialize ncurses
  initscr();
  clear();
 
  // Print a string on screen
  printw("Seems that you can use ncurses ...\nPress any key to exit!");
 
  // Wait until the user press a key
  getch();
 
  // Clear ncurses data structures
  endwin();
}
