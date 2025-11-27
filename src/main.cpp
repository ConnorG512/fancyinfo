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

auto parseFilePaths(std::span<const char *> passed_arguments) -> std::expected<std::monostate, std::string>
{
  for (const auto &arg : passed_arguments.subspan(1))
  {
    struct stat stat_struct{};

    std::println("\033[1mFile:\033[0m {}", arg);
    if (stat(arg, &stat_struct) == -1)
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
  }
  return std::monostate{};
}

auto main(const int argc, const char *argv[]) -> int
{
  if (const auto result = parseFilePaths(std::span(argv, argc + argv)); !result.has_value())
  {
    std::println(stderr, "{}", result.error());
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
