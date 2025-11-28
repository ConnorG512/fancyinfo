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

  if (command_list.human_flag)
  {
    const auto size_properties = std::array<FileSizeProperty<double>, 3>{
        FileSizeProperty<double>("Gigabyte", 1000.0f * 1000.0f * 1000.0f),
        FileSizeProperty<double>("Megabyte", 1000.0f * 1000.0f),
        FileSizeProperty<double>("Kilobyte", 1000.0f),
    };
    if (const auto result = PrintCommand::CalculateFileSizes(passed_command_args, size_properties); !result.has_value())
    {
      std::println("{}", result.error());
    }
  }
  else
  {
    const auto size_properties = std::array<FileSizeProperty<double>, 3>{
        FileSizeProperty<double>("Gibibyte", 1024.0f * 1024.0f * 1024.0f),
        FileSizeProperty<double>("Mebibyte", 1024.0f * 1024.0f),
        FileSizeProperty<double>("Kibibyte", 1024.0f),
    };
    if (const auto result = PrintCommand::CalculateFileSizes(passed_command_args, size_properties); !result.has_value())
    {
      std::println("{}", result.error());
    }
  }

  return EXIT_SUCCESS;
}
