#pragma once

#include "clI11/CLI11.hpp"

#include <span>

struct CommandList   
{
  explicit CommandList(std::span<char*> command_args);
  ~CommandList() = default;

  std::span<char*> argument_list{};
  CLI::App application{"finfo"};
  
  bool human_flag{false};
  bool count_flag{false};
};
