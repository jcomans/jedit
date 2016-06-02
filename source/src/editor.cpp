#include "editor.hpp"

#include <algorithm>

SCEditor::SCEditor(Gui::ScintillaSender sci_sender): 
  sci_sender_(sci_sender)
{
  sendMessage(SCI_SETWRAPMODE, SC_WRAP_CHAR);
  sendMessage(SCI_SETMARGINWIDTHN, 0, 32);
  sendMessage(SCI_SETMARGINTYPEN, 0, SC_MARGIN_NUMBER);
}

sptr_t SCEditor::sendMessage(unsigned int message, uptr_t wParam, sptr_t lParam)
{
  return sci_sender_(message, wParam, lParam);
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

void SCEditor::setCurrentPos(unsigned int pos)
{
  sendMessage(SCI_GOTOPOS, pos);
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

void SCEditor::wordLeft()
{
  sendMessage(SCI_WORDLEFT);
}

void SCEditor::wordRight()
{
  sendMessage(SCI_WORDRIGHT);
}

void SCEditor::nextLine()
{
  sendMessage(SCI_LINEDOWN);
}

void SCEditor::previousLine()
{
  sendMessage(SCI_LINEUP);
}

void SCEditor::pageDown()
{
  sendMessage(SCI_PAGEDOWN);
}

void SCEditor::documentStart()
{
  sendMessage(SCI_DOCUMENTSTART);
}

void SCEditor::documentEnd()
{
  sendMessage(SCI_DOCUMENTEND);
}

void SCEditor::pageUp()
{
  sendMessage(SCI_PAGEUP);
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
