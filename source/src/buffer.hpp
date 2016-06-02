#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <string>
#include <vector>

class SCEditor;

#include <Scintilla.h>

#include <boost/log/trivial.hpp>

class Buffer
{
public:
  Buffer(const std::string& nm="", const std::string& fp="", sptr_t doc=0):
    name_(nm), file_path_(fp), document_(doc), modified_(false), mark_(1)
  {
  }

  const char* name()     const { return name_.c_str();      }
  const char* filePath() const { return file_path_.c_str(); }
  sptr_t      document() const { return document_;          }

  bool modified() const { return modified_; }
  void modified(bool is_modified) { modified_ = is_modified; }

  size_t mark() const { return mark_; }
  void   mark(size_t mark) { mark_ = mark; }

private:
  std::string name_;
  std::string file_path_;
  sptr_t      document_;
  bool        modified_;
  size_t      mark_;
};

class BufferList
{
public:
  BufferList(SCEditor& editor);
  ~BufferList();

  void init();

  void createScratch();

  void findFile(const char* file_name);

  void saveFile();

  void switchBuffer();

  void killBuffer(bool create_scratch=true);

  Buffer& current();

private:
  SCEditor& editor_;
  
  typedef std::vector<Buffer> BufferList_t;
  BufferList_t buffer_list_;
};

#endif /* _BUFFER_H_ */
