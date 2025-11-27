#include "clI11/CLI11.hpp"
#include "command-list.h"
#include "file-size-printer.h"

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <expected>
#include <format>
#include <print>
#include <span>
#include <string>
#include <sys/stat.h>
#include <variant>

auto parseFilePaths(const std::string &file_path) -> std::expected<std::monostate, std::string>
{
  struct stat stat_struct{};

  std::println("\033[1mFile:\033[0m {}", file_path);
  if (stat(file_path.c_str(), &stat_struct) == -1)
    return std::unexpected(std::format("Failed to stat file! Error: {}.", strerror(errno)));

  if (stat_struct.st_size > File::Sizes::Kibibyte{}.division_size)
  {
    File::Sizes::Kibibyte{}.printSize(stat_struct.st_size);
  }
  else if (stat_struct.st_size > File::Sizes::Mebibyte{}.division_size)
  {
    File::Sizes::Mebibyte{}.printSize(stat_struct.st_size);
  }
  else if (stat_struct.st_size > File::Sizes::Gibibyte{}.division_size)
  {
    File::Sizes::Gibibyte{}.printSize(stat_struct.st_size);
  }
  else
  {
    std::println("\tSize:{}bytes", stat_struct.st_size);
  }
  return std::monostate{};
}

auto main(int argc, char *argv[]) -> int
{
  auto command_list = CommandList(std::span(argv, argc + argv));
  
  try
  {
    if (const auto result = parseFilePaths(command_list.directory_arg_); !result.has_value())
    {
      std::println(stderr, "{}", result.error());
      return EXIT_FAILURE;
    }
  }
  catch (const CLI::CallForHelp &e)
  {
    std::println("{}", e.what());
  }
  catch (const CLI::ParseError &e)
  {
    std::println("{}", e.what());
  }
  catch (...)
  {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
