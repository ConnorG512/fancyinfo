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
#include <ranges>
#include <span>
#include <string>
#include <sys/stat.h>
#include <variant>

[[nodiscard]] auto parseFilePaths(std::span<char *> file_path) noexcept -> std::expected<std::monostate, std::string>
{
  struct stat stat_struct{};

  for (const auto &file :
       file_path.subspan(1) | std::views::filter([](const char *command) { return std::memcmp(command, "-", 1) != 0; }))
  {
    if (stat(file, &stat_struct) == -1)
      return std::unexpected(std::format("Failed to stat file! Error: {}.", strerror(errno)));
    
    std::println("\033[1mFile:\033[0m {}", file);
    if (stat_struct.st_size > File::Sizes::Gibibyte{}.division_size)
    {
      File::Sizes::Gibibyte{}.printSize(stat_struct.st_size);
    }
    else if (stat_struct.st_size > File::Sizes::Mebibyte{}.division_size)
    {
      File::Sizes::Mebibyte{}.printSize(stat_struct.st_size);
    }
    else if (stat_struct.st_size > File::Sizes::Kibibyte{}.division_size)
    {
      File::Sizes::Kibibyte{}.printSize(stat_struct.st_size);
    }
    else
    {
      std::println("\tSize:{}bytes", stat_struct.st_size);
    }
  }

  return std::monostate{};
}

[[nodiscard]] auto parseFilePathsHuman(std::span<char *> file_path) noexcept
    -> std::expected<std::monostate, std::string>
{
  struct stat stat_struct{};

  for (const auto &file :
       file_path.subspan(1) | std::views::filter([](const char *command) { return std::memcmp(command, "-", 1) != 0; }))
  {
    if (stat(file, &stat_struct) == -1)
      return std::unexpected(std::format("Failed to stat file! Error: {}.", strerror(errno)));

    std::println("\033[1mFile:\033[0m {}", file);
    if (stat_struct.st_size > File::Sizes::Gigabyte{}.division_size)
    {
      File::Sizes::Gigabyte{}.printSize(stat_struct.st_size);
    }
    else if (stat_struct.st_size > File::Sizes::Megabyte{}.division_size)
    {
      File::Sizes::Megabyte{}.printSize(stat_struct.st_size);
    }
    else if (stat_struct.st_size > File::Sizes::Kilobyte{}.division_size)
    {
      File::Sizes::Kilobyte{}.printSize(stat_struct.st_size);
    }
    else
    {
      std::println("\tSize:{}bytes", stat_struct.st_size);
    }
  }

  return std::monostate{};
}

auto main(int argc, char *argv[]) -> int
{
  auto passed_command_args{std::span(argv, argv + argc)};

  auto command_list = CommandList(passed_command_args);
  CLI11_PARSE(command_list.application, passed_command_args.size(), passed_command_args.data());

  if (command_list.human_flag)
  {
    std::println("Human!");
    if (const auto result = parseFilePathsHuman(passed_command_args); !result.has_value())
    {
      std::println(stderr, "{}", result.error());
      return EXIT_FAILURE;
    }
  }
  else
  {
    if (const auto result = parseFilePaths(passed_command_args); !result.has_value())
    {
      std::println(stderr, "{}", result.error());
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}
