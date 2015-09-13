#ifndef _FRONTEND_H_
#define _FRONTEND_H_

#include <ncurses.h>

#include "../backend/backend.hpp"

namespace jedit
{
  ////////////////////////////////////////////////////////////
  // An ncurses wrapper
  class NCurses
  {
  public:
    NCurses() 
    {
      initscr();
      clear();
      noecho();
      raw();
      meta (stdscr, true);
      intrflush (stdscr, false);
      keypad(stdscr, TRUE);
      curs_set(0);
    }

    ~NCurses()
    {
      endwin();
    }

    char getChar() const { return getch(); }
  };

  ////////////////////////////////////////////////////////////
  // The frontend
  class Frontend
  {
  public:
    Frontend(const Backend &backend) : backend_{backend}, ncurses_{} {}

    void redraw() const
    {
      clear();
      const auto& buffer = backend_.currentBuffer().charBuffer();
      for(const auto& character: buffer)
        addch(character);
    }

    char getChar() const
    {
      return ncurses_.getChar();
    }

  private:
    const Backend& backend_;
    NCurses ncurses_;
  };
}

#endif /* _FRONTEND_H_ */












