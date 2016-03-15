#include "editor.hpp"

#include <algorithm>

#include <gtk/gtk.h>

#include <SciLexer.h>
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

const char* SCEditor::getText()
{
  size_t len = sendMessage(SCI_GETLENGTH);
  tmp_buffer_.resize(len);
  sendMessage(SCI_GETTEXT, tmp_buffer_.size()+1, &tmp_buffer_[0]);
  return tmp_buffer_.c_str();
}

unsigned int SCEditor::currentPos()
{
  return static_cast<unsigned int>(sendMessage(SCI_GETCURRENTPOS));
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

void SCEditor::insertText(unsigned int pos, const char* text)
{
  sendMessage(SCI_INSERTTEXT, pos, text);
}

void SCEditor::deleteRange(unsigned int pos, unsigned int length)
{
  sendMessage(SCI_DELETERANGE, pos, length);
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
