#include "clI11/CLI11.hpp"
#include "command-list.h"
#include "file-size-properties.h"
#include "print-command.h"

#include <array>
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <print>
#include <sys/stat.h>

auto main(int argc, char *argv[]) -> int
{
  auto passed_command_args{std::span(argv, argv + argc)};

  auto command_list = CommandList(passed_command_args);
  CLI11_PARSE(command_list.application, passed_command_args.size(), passed_command_args.data());
  
  const auto size_properties = command_list.human_flag == true ? File::ArrayPresets::human : File::ArrayPresets::binary; 

  if (const auto result = PrintCommand::CalculateFileSizes(passed_command_args, size_properties); !result.has_value())
    std::println("{}", result.error());
  else 
  {
    for(const auto& path : result.value())
    {
      std::println("{}", path);
    }
  }

  return EXIT_SUCCESS;
}
