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

namespace
{
} // namespace

auto processCommands(std::span<const char *> passed_arguments) -> std::expected<std::monostate, std::string>
{
  for (const auto &arg : passed_arguments.subspan(1))
  {
    struct stat stat_struct{};

    std::println("\033[1mFile:\033[0m {}", arg);
    if (stat(arg, &stat_struct) == -1)
      return std::unexpected(std::format("Failed to stat file! Error: {}.", strerror(errno)));

    if (stat_struct.st_size > 1024)
    { 
      File::Kibibyte{}.printSize(stat_struct.st_size); 
      continue;
    }
    else if (stat_struct.st_size > 1024 * 1024)
    { 
      File::Mebibyte{}.printSize(stat_struct.st_size); 
      continue;
    }
    else if (stat_struct.st_size > 1024 * 1024)
    { 
      File::Gibibyte{}.printSize(stat_struct.st_size); 
      continue;
    }
    std::println("\tSize:{}bytes", stat_struct.st_size);
  }
  return std::monostate{};
}

auto main(const int argc, const char *argv[]) -> int
{
  if (const auto result = processCommands(std::span(argv, argc + argv)); !result.has_value())
  {
    std::println("{}", result.error());
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
