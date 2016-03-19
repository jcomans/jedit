#ifndef _EDITOR_H_
#define _EDITOR_H_

#include "gui/gui.hpp"
#include <string>

class SCEditor
{
public:
  SCEditor(Gui::ScintillaSender sci_sender);

  sptr_t sendMessage(unsigned int message, uptr_t wParam=0, sptr_t lParam=0);

  template <typename T>
  sptr_t sendMessage(unsigned int message, uptr_t wParam=0, T* lParam=0);

  const char* getText();

  unsigned int currentPos();

  void setFont(const char* font_name);

  void setCaretStyle(int style);

  void addText(const char* text);

  void insertChar(char character);

  void insertText(unsigned int pos, const char* text);

  void deleteRange(unsigned int pos, unsigned int length);

  void charLeft();

  void charRight();

  void nextLine();

  void previousLine();

  void lineStart();

  void lineEnd();

  void newLine();

  void backSpace();

  void deleteChar();

  void undo();

private:
  Gui::ScintillaSender sci_sender_;
  std::string tmp_buffer_;
};

template <typename T>
sptr_t SCEditor::sendMessage(unsigned int message, uptr_t wParam, T* lParam)
{
  return sendMessage(message, wParam, reinterpret_cast<sptr_t>(lParam));
}

#endif /* _EDITOR_H_ */
