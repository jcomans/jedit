#ifndef _GUI_FACTORY_H_
#define _GUI_FACTORY_H_

#include <cassert>

#include <functional>
#include <map>
#include <memory>

#include <boost/asio.hpp>

#include "gui.hpp"

class GUIFactory
{
public:
  using GUICreator = std::function<GuiPtr(int,char**,boost::asio::io_service&)>;

  static void AddCreator(const char* name, GUICreator creator)
  {
    creator_map()[name] = creator;
  }

  static GuiPtr Create(int argc, char** argv, boost::asio::io_service& io_service, const char* name="")
  {
    assert(creator_map().size());

    auto the_name = std::string{name};

    if(the_name.size() && creator_map().count(name))
    {
      return creator_map()[name](argc, argv, io_service);
    }
    else
    {
      return creator_map().begin()->second(argc, argv, io_service);
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
                           [this](int argc, char** argv, boost::asio::io_service& io_service)
                           {
                             return this->create(argc, argv, io_service);
                           } ); 
  }

  GuiPtr create(int argc, char** argv, boost::asio::io_service& io_service) 
  { 
    return std::make_shared<T>(argc, argv, io_service); 
  }
};

#endif /* _GUI_FACTORY_H_ */
