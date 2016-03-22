#include "buffer.hpp"

#include <algorithm>
#include <fstream>
#include <streambuf>

#include "editor.hpp"

BufferList::BufferList(SCEditor& editor):
  editor_(editor)
{
  createScratch();
}

void BufferList::init()
{
  createScratch();
}

void BufferList::createScratch()
{
  buffer_list_.emplace_back("*scratch*", "", 
                            editor_.sendMessage(SCI_CREATEDOCUMENT));
  editor_.sendMessage(SCI_SETDOCPOINTER, 0, buffer_list_.back().document());
  editor_.sendMessage(SCI_SETTEXT, 0, "This is your scratch buffer.\nFeel free to use for doodling.\n");
  editor_.sendMessage(SCI_SETSAVEPOINT);
}

void BufferList::findFile(const char* file_name)
{
  auto the_file = std::ifstream(file_name);
    
  if(the_file)
  {
    buffer_list_.emplace_back(file_name, file_name,
                              editor_.sendMessage(SCI_CREATEDOCUMENT));

    editor_.sendMessage(SCI_SETDOCPOINTER, 0, buffer_list_.back().document());

    auto content = std::string( std::istreambuf_iterator<char>(the_file),
                                std::istreambuf_iterator<char>() );

    editor_.sendMessage(SCI_SETTEXT, 0, content.c_str());
    editor_.sendMessage(SCI_SETSAVEPOINT);
  }    
}

void BufferList::saveFile()
{
  size_t len = editor_.sendMessage(SCI_GETLENGTH);
  std::vector<char> buffer(len+1);
  editor_.sendMessage(SCI_GETTEXT, buffer.size(), &buffer[0]);

  auto the_file = std::ofstream(buffer_list_.back().filePath());
  the_file.write(&buffer[0], len);

  editor_.sendMessage(SCI_SETSAVEPOINT);
}

void BufferList::switchBuffer()
{
  if(buffer_list_.size() > 1)
  {
    std::iter_swap(buffer_list_.rbegin(), buffer_list_.rbegin()+1);
    editor_.sendMessage(SCI_SETDOCPOINTER, 0, buffer_list_.back().document());
  }
}

void BufferList::killBuffer()
{
  if(buffer_list_.size())
  {
    Buffer the_buffer = buffer_list_.back();
      
    buffer_list_.pop_back();
      
    if(buffer_list_.size())
      editor_.sendMessage(SCI_SETDOCPOINTER, 0, buffer_list_.back().document());
    else
      createScratch();

    editor_.sendMessage(SCI_RELEASEDOCUMENT, 0, the_buffer.document());      
  }
}

Buffer& BufferList::current()
{
  return buffer_list_.back();
}
