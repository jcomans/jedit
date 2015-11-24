#include "editor.hpp"

#include <gtk/gtk.h>

#include <ScintillaWidget.h>

SCEditor::SCEditor(): 
  editor_(nullptr) 
{
}

void SCEditor::init(ScintillaObject* editor)
{
  editor_ = editor;

  scintilla_set_id(editor_, 0);
}

sptr_t SCEditor::sendMessage(unsigned int message, uptr_t wParam, sptr_t lParam)
{
  return scintilla_send_message(editor_, message, wParam, lParam);
}

void SCEditor::setFont(const char* font_name)
{
  sendMessage(SCI_STYLESETFONT, STYLE_DEFAULT, font_name);
}

void SCEditor::setCaretStyle(int style)
{
  sendMessage(SCI_SETCARETSTYLE, style);
}

void SCEditor::addText(const char* text)
{
  sendMessage(SCI_INSERTTEXT, -1, text);
}

void SCEditor::insertChar(char character)
{
  sendMessage(SCI_ADDTEXT, 1, &character);
  sendMessage(SCI_SCROLLCARET);
}

void SCEditor::charLeft()
{
  sendMessage(SCI_CHARLEFT);
}

void SCEditor::charRight()
{
  sendMessage(SCI_CHARRIGHT);
}

void SCEditor::nextLine()
{
  sendMessage(SCI_LINEDOWN);
}

void SCEditor::previousLine()
{
  sendMessage(SCI_LINEUP);
}

void SCEditor::lineStart()
{
  sendMessage(SCI_HOME);
}

void SCEditor::lineEnd()
{
  sendMessage(SCI_LINEEND);
}

void SCEditor::newLine()
{
  sendMessage(SCI_NEWLINE);
}

void SCEditor::backSpace()
{
  sendMessage(SCI_DELETEBACK);
}

void SCEditor::deleteChar()
{
  sendMessage(SCI_CLEAR);
}

void SCEditor::undo()
{
  sendMessage(SCI_UNDO);
}
