#ifndef _GUI_FACTORY_H_
#define _GUI_FACTORY_H_

#include <cassert>

#include <functional>
#include <map>
#include <memory>

#include "gui.hpp"

class GUIFactory
{
public:
  using GUICreator = std::function<GuiPtr(int,char**)>;

  static void AddCreator(const char* name, GUICreator creator)
  {
    creator_map()[name] = creator;
  }

  static GuiPtr Create(int argc, char** argv, const char* name="")
  {
    assert(creator_map().size());

    auto the_name = std::string{name};

    if(the_name.size() && creator_map().count(name))
    {
      return creator_map()[name](argc, argv);
    }
    else
    {
      return creator_map().begin()->second(argc, argv);
    }
  }

private:
  using CreatorMap = std::map<std::string, GUICreator>;

  static CreatorMap& creator_map()
  {
    static CreatorMap the_map;
    return the_map;
  }
};

template<class T>
struct RegisterGUI
{
  RegisterGUI(const char* name) 
  { 
    GUIFactory::AddCreator(name, 
                           [this](int argc, char** argv)
                           {
                             return this->create(argc, argv);
                           } ); 
  }

  GuiPtr create(int argc, char** argv) 
  { 
    return std::make_shared<T>(argc, argv); 
  }
};

#endif /* _GUI_FACTORY_H_ */
