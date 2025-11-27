#pragma once

#include "clI11/CLI11.hpp"

#include <span>

struct CommandList   
{
  explicit CommandList(std::span<char*> command_args);
  ~CommandList() = default;

  std::span<char*> argument_list_{};
  CLI::App application_{"finfo"};
  std::string file_arg_{};
};
