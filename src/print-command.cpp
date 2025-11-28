#include "file-size-properties.h"
#include "print-command.h"

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <print>
#include <ranges>
#include <sys/stat.h>

[[nodiscard]] auto PrintCommand::CalculateFileSizes(const std::span<char *> file_paths,
                                                    const std::span<SizeType::Properties> size_types) noexcept
    -> std::expected<void, std::string>
{
  struct stat stat_struct{};

  std::println("\033[1mFile:\033[0m");
  for (const char *path :
       file_paths | std::views::filter([](const char *command) { return std::memcmp(command, "-", 1) != 0; }))
  {
    if (stat(path, &stat_struct) == -1)
      return std::unexpected(std::format("Failed to stat file! Error: {}.", strerror(errno)));

    for (const auto &type : size_types)
    {
      const double file_size{stat_struct.st_size / type.DivisionSize()};
      if (stat_struct.st_size < type.DivisionSize())
        continue;

      std::println("\t{}{}", file_size, type.Name());
    }
  }

  return {};
}

// [[nodiscard]] auto parseFilePaths(std::span<char *> file_path) noexcept -> std::expected<std::monostate, std::string>
// {
//   struct stat stat_struct{};
//
//   for (const auto &file :
//        file_path.subspan(1) | std::views::filter([](const char *command) { return std::memcmp(command, "-", 1) != 0;
//        }))
//   {
//     if (stat(file, &stat_struct) == -1)
//       return std::unexpected(std::format("Failed to stat file! Error: {}.", strerror(errno)));
//
//     std::println("\033[1mFile:\033[0m {}", file);
//     if (stat_struct.st_size > File::Sizes::Gibibyte{}.division_size)
//     {
//       File::Sizes::Gibibyte{}.printSize(stat_struct.st_size);
//     }
//     else if (stat_struct.st_size > File::Sizes::Mebibyte{}.division_size)
//     {
//       File::Sizes::Mebibyte{}.printSize(stat_struct.st_size);
//     }
//     else if (stat_struct.st_size > File::Sizes::Kibibyte{}.division_size)
//     {
//       File::Sizes::Kibibyte{}.printSize(stat_struct.st_size);
//     }
//     else
//     {
//       std::println("\tSize:{}bytes", stat_struct.st_size);
//     }
//   }
//
//   return std::monostate{};
// }
