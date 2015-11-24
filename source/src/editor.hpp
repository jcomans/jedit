#ifndef _EDITOR_H_
#define _EDITOR_H_

#include <Scintilla.h>

struct _ScintillaObject;
typedef _ScintillaObject ScintillaObject;;

class SCEditor
{
public:
  SCEditor();

  void init(ScintillaObject* editor);

  sptr_t sendMessage(unsigned int message, uptr_t wParam=0, sptr_t lParam=0);

  template <typename T>
  sptr_t sendMessage(unsigned int message, uptr_t wParam=0, T* lParam=0);

  void setFont(const char* font_name);

  void setCaretStyle(int style);

  void addText(const char* text);

  void insertChar(char character);

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
  ScintillaObject* editor_;
};

template <typename T>
sptr_t SCEditor::sendMessage(unsigned int message, uptr_t wParam, T* lParam)
{
  return sendMessage(message, wParam, reinterpret_cast<sptr_t>(lParam));
}

#endif /* _EDITOR_H_ */
