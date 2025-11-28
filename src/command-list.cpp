#include "clI11/CLI11.hpp"
#include "command-list.h"

#include <print>

CommandList::CommandList(std::span<char *> command_args) : argument_list_(command_args)
{
  application_.add_option("-d,--directory", directory_arg_, "Path to directory");
  application_.add_flag("--human", human_flag_, "Use 1000 instead of 1024 sizing.");
  
  application_.set_help_flag("");
  application_.set_help_all_flag("-h, --help");
}
