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
                                                    const std::span<const FileSizeProperty<double>> size_types) noexcept
    -> std::expected<void, std::string>
{
  struct stat stat_struct{};

  for (const char *path : file_paths.subspan(1) |
                              std::views::filter([](const char *command) { return std::memcmp(command, "-", 1) != 0; }))
  {
    if (stat(path, &stat_struct) == -1)
      return std::unexpected(std::format("Failed to stat file! Error: {}.", strerror(errno)));

    std::println("\033[1mFile: {}\033[0m", path);
    for (const auto &type : size_types)
    {
      const double file_size{stat_struct.st_size / type.division_size};
      if (stat_struct.st_size > type.division_size)
        std::println("\tSize({:.2}): {} | {}(bytes)", file_size, type.name, stat_struct.st_size);
      else 
        continue;
    }
  }

  return {};
}
