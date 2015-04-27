#include <ncurses.h>

void game_loop(char main_char, int row, int col, int ch);
void erase (int y, int x);
 
int main() {
  // Initialize ncurses
  initscr();
  clear();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);
  curs_set(0);	
 
  // Define the main character initial position and symbol:
  int row = 10, col = 10;
  char main_char = '@';
 
  // Print a welcome message on screen
  printw("Welcome to the RR game.\nPress any key to start.\nIf you want to quit press \"q\" or \"Q\"");
 
  // Wait until the user press a key
  int ch = getch();
 
  // Clear the screen
  clear();

  // Start the game loop
  game_loop(main_char, row, col, ch);
 	
  // Start the game loop
  while(1) {
    if(ch == 'q' || ch == 'Q') {
      break;
    }
    // If the user choses to stay, show the main character at position (row,col)
    else {
      mvaddch(row, col, main_char);
      ch = getch();
    }
  }
 
  // Clear ncurses data structures
  endwin();
}

void game_loop(char main_char, int row, int col, int ch) {
  // Check if the user wishes to play the game
  if(ch == 'q' || ch =='Q') return;
 
  // Show the main character on the screen
  mvaddch(row, col, main_char);
  refresh();
 
  for(;;) {
    ch = getch();
 
    if(ch == KEY_LEFT) {
      erase(row, col);
      col = col - 1;
      mvaddch(row, col, main_char);
      refresh();
    }
    else if(ch == KEY_RIGHT) {
      erase(row, col);
      col = col + 1;
      mvaddch(row, col, main_char);
      refresh();
    }
    else if(ch == KEY_UP) {
      erase(row, col);
      row = row - 1;
      mvaddch(row, col, main_char);
      refresh();
    }
    else if(ch == KEY_DOWN) {
      erase(row, col);
      row = row + 1;
      mvaddch(row, col, main_char);
      refresh();
    }
    else if(ch == 'q' || ch == 'Q') {
      break;
    }
  }
}

void erase (int y, int x) {
  mvaddch(y, x, '#');
}
