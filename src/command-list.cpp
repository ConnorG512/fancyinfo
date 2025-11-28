#include "clI11/CLI11.hpp"
#include "command-list.h"

CommandList::CommandList(std::span<char *> command_args) : argument_list(command_args)
{
  application.add_option("-d,--directory", directory_arg, "Path to directory");
  application.add_flag("--human", human_flag, "Use 1000 instead of 1024 sizing.");
  
  application.set_help_flag("");
  application.set_help_all_flag("-h, --help");
  application.allow_extras();
}
