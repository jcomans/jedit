#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <algorithm>
#include <fstream>
#include <streambuf>
#include <string>
#include <vector>

#include "editor.hpp"

#include <Scintilla.h>

#include <iostream>

struct Buffer
{
  bool        temporary;
  std::string name;
  std::string file_path;
  sptr_t      document;

  Buffer(bool tmp=false, const std::string& nm="", const std::string& fp="", sptr_t doc=0):
    temporary(tmp), name(nm), file_path(fp), document(doc)
  {
  }
};

class BufferList
{
public:
  BufferList(SCEditor& editor):
    editor_(editor)
  {
  }

  void init()
  {
    createScratch();
  }

  void createScratch()
  {
    buffer_list_.emplace_back(false, "*scratch*", "", 
                              editor_.sendMessage(SCI_CREATEDOCUMENT));
    editor_.sendMessage(SCI_SETDOCPOINTER, 0, buffer_list_.back().document);
    editor_.sendMessage(SCI_SETTEXT, 0, "This is your scratch buffer.\nFeel free to use for doodling.\n");
  }

  void findFile(const char* file_name)
  {
    auto the_file = std::ifstream(file_name);
    
    if(the_file)
    {
      buffer_list_.emplace_back(false, file_name, file_name,
                                editor_.sendMessage(SCI_CREATEDOCUMENT));

      editor_.sendMessage(SCI_SETDOCPOINTER, 0, buffer_list_.back().document);

      auto content = std::string( std::istreambuf_iterator<char>(the_file),
                                  std::istreambuf_iterator<char>() );

      editor_.sendMessage(SCI_SETTEXT, 0, content.c_str());
    }    
  }

  void switchBuffer()
  {
    if(buffer_list_.size() > 1)
    {
      std::iter_swap(buffer_list_.rbegin(), buffer_list_.rbegin()+1);
      std::cout << "Switching to: " << buffer_list_.back().name << std::endl;
      editor_.sendMessage(SCI_SETDOCPOINTER, 0, buffer_list_.back().document);
    }
  }

private:
  SCEditor& editor_;
  
  typedef std::vector<Buffer> BufferList_t;
  BufferList_t buffer_list_;
};

#endif /* _BUFFER_H_ */
