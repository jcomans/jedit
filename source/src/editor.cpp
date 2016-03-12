#include "editor.hpp"

#include <algorithm>

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

void SCEditor::handleStyle(const unsigned int end_pos)
{
  using uint = unsigned int;

  const auto start_pos   = static_cast<uint>(sendMessage(SCI_GETENDSTYLED));
  const auto line_number = static_cast<uint>(sendMessage(SCI_LINEFROMPOSITION, start_pos));
  const auto line_start  = static_cast<uint>(sendMessage(SCI_POSITIONFROMLINE, line_number));

  const auto line_length = static_cast<uint>(sendMessage(SCI_LINELENGTH, line_number));

  const auto line_end = line_start + line_length;

  const auto style_length = std::min(end_pos, line_end) - start_pos;

  if(style_length>0)
  {
    const auto first_char = static_cast<char>(sendMessage(SCI_GETCHARAT, line_start));

    sendMessage(SCI_STARTSTYLING, start_pos, 0);

    switch(first_char)
    {
    case '#':
      sendMessage(SCI_SETSTYLING, style_length, SCE_STYLE_GREEN);
      break;
    default:
      sendMessage(SCI_SETSTYLING, style_length, STYLE_DEFAULT);
      break;
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
