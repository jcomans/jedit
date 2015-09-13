//#include <cstdlib>
#include <iostream>
#include <sstream>

// #include <boost/asio.hpp>
// #include <boost/bind.hpp>

#include "script_engine.hpp"
#include "backend/backend.hpp"
#include "frontend/frontend.hpp"



int main(int argc, char** argv)
{
  jedit::Backend backend;
  jedit::Frontend frontend{backend};

  jedit::ScriptEngine se;
  se.load("../data/init.py");

  bool running = true;

  frontend.redraw();

  while(running)
  {
    
    const char ch = frontend.getChar();

    if(ch == 27)
    {
      running = false;
    }
 
    se.run(ch);

    frontend.redraw();
  }
}

















