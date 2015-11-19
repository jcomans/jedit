#ifndef _EDITOR_H_
#define _EDITOR_H_

#include <Scintilla.h>
#include <ScintillaWidget.h>

class SCEditor
{
public:
  SCEditor(): 
    editor_(nullptr) 
  {
  }

  void init(ScintillaObject* editor)
  {
    editor_ = editor;

    scintilla_set_id(editor_, 0);

  }

  sptr_t sendMessage(unsigned int message, uptr_t wParam=0, sptr_t lParam=0)
  {
    return scintilla_send_message(editor_, message, wParam, lParam);
  }

  template <typename T>
  sptr_t sendMessage(unsigned int message, uptr_t wParam=0, T* lParam=0)
  {
    return sendMessage(message, wParam, reinterpret_cast<sptr_t>(lParam));
  }

  void setFont(const char* font_name)
  {
    sendMessage(SCI_STYLESETFONT, STYLE_DEFAULT, font_name);
  }

  void setCaretStyle(int style)
  {
    sendMessage(SCI_SETCARETSTYLE, style);
  }

  void addText(const char* text)
  {
    sendMessage(SCI_INSERTTEXT, -1, text);
  }

  void insertChar(char character)
  {
    sendMessage(SCI_ADDTEXT, 1, &character);
    sendMessage(SCI_SCROLLCARET);
  }

  void charLeft()
  {
    sendMessage(SCI_CHARLEFT);
  }

  void charRight()
  {
    sendMessage(SCI_CHARRIGHT);
  }

  void nextLine()
  {
    sendMessage(SCI_LINEDOWN);
  }

  void previousLine()
  {
    sendMessage(SCI_LINEUP);
  }

  void lineStart()
  {
    sendMessage(SCI_HOME);
  }

  void lineEnd()
  {
    sendMessage(SCI_LINEEND);
  }

  void newLine()
  {
    sendMessage(SCI_NEWLINE);
  }

  void backSpace()
  {
    sendMessage(SCI_DELETEBACK);
  }

  void deleteChar()
  {
    sendMessage(SCI_CLEAR);
  }



private:
  ScintillaObject* editor_;
};

#endif /* _EDITOR_H_ */
