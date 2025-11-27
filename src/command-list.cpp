#include "command-list.h"
#include "clI11/CLI11.hpp"
#include <print>

CommandList::CommandList(std::span<char*> command_args) 
  : argument_list_(command_args) 
{
  [[maybe_unused]] CLI::Option *opt = application_.add_option("-f,--file", file_arg_, "File name");

  application_.parse(argument_list_.size(), argument_list_.data());
  std::println("{}", file_arg_);
}

