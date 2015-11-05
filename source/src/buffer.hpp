#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <string>
#include <vector>

#include "editor.hpp"

#include <Scintilla.h>

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
    editor_.sendMessage(SCI_SETDOCPOINTER, buffer_list_.back().document);
    editor_.sendMessage(SCI_SETTEXT, 0, "This is your scratch buffer.\nFeel free to use for doodling.\n");
  }

private:
  SCEditor& editor_;
  
  typedef std::vector<Buffer> BufferList_t;
  BufferList_t buffer_list_;
};

#endif /* _BUFFER_H_ */
