#include <iostream>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include "app.hpp"

int main(int argc, char** argv)
{  
  namespace logging = boost::log;

  logging::core::get()->add_global_attribute("TimeStamp", logging::attributes::local_clock());
  logging::register_simple_formatter_factory< logging::trivial::severity_level, char >("Severity");


  logging::add_console_log(std::cerr,
                       logging::keywords::filter = logging::trivial::severity > logging::trivial::info,
                       logging::keywords::format = "[%TimeStamp%] <%Severity%>\t%Message%" );

  logging::add_console_log(std::cout,
                           logging::keywords::filter = logging::trivial::severity > logging::trivial::trace,
                           logging::keywords::format = "[%TimeStamp%] <%Severity%>\t%Message%" );

  App the_app(argc, argv);
  the_app.run();
}
