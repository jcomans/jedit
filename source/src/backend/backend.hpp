#ifndef _BACKEND_H_
#define _BACKEND_H_

#include <string>

namespace jedit
{
  ////////////////////////////////////////////////////////////
  // A buffer
  class Buffer
  {
  public:
    typedef std::string CharBuffer;

    Buffer():charbuffer_{"Hello, World!\nThis is your first buffer.\n"}
    {
    }
    
    const CharBuffer& charBuffer() const { return charbuffer_; }

    void addChar(char ch) { charbuffer_.push_back(ch); }
    void removeChar()     { charbuffer_.pop_back();    }

  private:
    CharBuffer charbuffer_;
  };

  ////////////////////////////////////////////////////////////
  // The backend
  class Backend
  {
  public:
    Buffer& currentBuffer() { return buffer_; }
    const Buffer& currentBuffer() const { return buffer_; }
  private:
    Buffer buffer_;
  };

  
}

#endif /* _BACKEND_H_ */












