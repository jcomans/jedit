#ifndef _MINIBUFFER_H_
#define _MINIBUFFER_H_

struct _GtkWidget;
typedef _GtkWidget GtkWidget;

#include <functional>
#include <string>

class MiniBuffer
{
public:
  MiniBuffer();

  void init(GtkWidget* status_bar_widget);

  bool isActive() const;

  void setMessage(const char* message);

  void clearMessage();

  void cancel();

  const char* getDynamic() const;

  void setDynamic(const char* dyn);

  void backSpace();

  void insertChar(char character);

  void startCapture(const char* read_only, const char* callback);

  //int handle(unsigned int keyval, unsigned int state, bool is_modifier);

private:
  GtkWidget* status_bar_widget_;
  bool is_active_;

  std::string read_only_;
  std::string dynamic_;

  std::string callback_;
};

#endif /* _MINIBUFFER_H_ */
