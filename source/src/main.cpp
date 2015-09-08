#include <cstdlib>
#include <iostream>
#include <sstream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "backend/backend.hpp"
#include "frontend/frontend.hpp"

class SigHandler
{
public:
  SigHandler():io_service_{}, signal_set_{io_service_, SIGINT, SIGTERM},got_signal_{false} 
  {
    signal_set_.async_wait(boost::bind(&SigHandler::signalHandler, this, _1, _2));
  }

  bool receivedSignal() const { return got_signal_; }

private:
  void signalHandler( const boost::system::error_code& error, int signal_number)
  {
    got_signal_ = true;
    clear();
    printw("Exiting");
    std::exit(0);
  }

  boost::asio::io_service io_service_;
  boost::asio::signal_set signal_set_;
  bool got_signal_;
};

int main(int argc, char** argv)
{
  jedit::Backend backend;
  jedit::Frontend frontend{backend};

  SigHandler sig_handler;

  bool running = true;

  frontend.redraw();

  while(running)
  {
    char ch = frontend.getChar();

    if(ch == 27)
    {
      running = false;
    }
    else if(ch == 10 || (ch>31 && ch<127) )
    {
      backend.currentBuffer().addChar(ch);
    }
    else if(ch == 7)
    {
      backend.currentBuffer().removeChar();
    }
    else
    {
      std::stringstream ss;
      ss << "|" << +ch << "|";
      for(auto c: ss.str())
        backend.currentBuffer().addChar(c);
    }

    frontend.redraw();
  }
}

















