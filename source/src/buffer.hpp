#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <string>
#include <vector>

class SCEditor;

#include <Scintilla.h>

struct Buffer
{
  std::string name;
  std::string file_path;
  sptr_t      document;

  Buffer(const std::string& nm="", const std::string& fp="", sptr_t doc=0):
    name(nm), file_path(fp), document(doc)
  {
  }
};

class BufferList
{
public:
  BufferList(SCEditor& editor);

  void init();

  void createScratch();

  void findFile(const char* file_name);

  void saveFile();

  void switchBuffer();

  void killBuffer();

private:
  SCEditor& editor_;
  
  typedef std::vector<Buffer> BufferList_t;
  BufferList_t buffer_list_;
};

#endif /* _BUFFER_H_ */
