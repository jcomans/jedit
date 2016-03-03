#include "editor.hpp"

#include <gtk/gtk.h>

#include <SciLexer.h>
#include <ScintillaWidget.h>

#include <iostream>
using std::cout;
using std::endl;

namespace
{
  const int SCE_STYLE_GREEN = 11;
}

SCEditor::SCEditor(): 
  editor_(nullptr) 
{
}

void SCEditor::init(ScintillaObject* editor)
{
  editor_ = editor;

  scintilla_set_id(editor_, 0);

  sendMessage(SCI_SETLEXER, SCLEX_CONTAINER);

  
  sendMessage(SCI_STYLESETFORE, STYLE_DEFAULT, 0x000000);
  sendMessage(SCI_STYLESETBACK, STYLE_DEFAULT, 0xffffff);
  sendMessage(SCI_STYLECLEARALL);

  sendMessage(SCI_STYLESETFORE, SCE_STYLE_GREEN, 0x00ff00);
}

void SCEditor::handleStyle(const int end_pos)
{
  const auto start_pos   = sendMessage(SCI_GETENDSTYLED);
  const auto line_number = sendMessage(SCI_LINEFROMPOSITION, start_pos);
  const auto line_pos    = sendMessage(SCI_POSITIONFROMLINE, line_number);

  const auto line_length = sendMessage(SCI_LINELENGTH, line_number);

  if(line_length>0)
  {
    const auto first_char = static_cast<char>(sendMessage(SCI_GETCHARAT, line_pos));

    sendMessage(SCI_STARTSTYLING, start_pos, 0);

    switch(first_char)
    {
    case '#':
      sendMessage(SCI_SETSTYLING, line_length, SCE_STYLE_GREEN);
    default:
      sendMessage(SCI_SETSTYLING, line_length, STYLE_DEFAULT);
    }
  }
}

sptr_t SCEditor::sendMessage(unsigned int message, uptr_t wParam, sptr_t lParam)
{
  return scintilla_send_message(editor_, message, wParam, lParam);
}

void SCEditor::setFont(const char* font_name)
{
  sendMessage(SCI_STYLESETFONT, STYLE_DEFAULT, font_name);
  sendMessage(SCI_STYLESETFONT, SCE_STYLE_GREEN, font_name);
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
