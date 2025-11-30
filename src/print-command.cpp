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
                                                    const std::span<const File::Properties, 3> size_types) noexcept
    -> std::expected<std::vector<std::string>, std::string>
{
  struct stat stat_struct{};
  std::vector<std::string> file_results{};

  for (const char *path : file_paths.subspan(1) |
                              std::views::filter([](const char *command) { return std::memcmp(command, "-", 1) != 0; }))
  {
    if (stat(path, &stat_struct) == -1)
      return std::unexpected(std::format("PATH ERROR: {}, {}", path, strerror(errno)));

    file_results.push_back(std::format("\033[1mFile: {}\033[0m", path));
    for (const auto &type : size_types)
    {
      const double file_size{stat_struct.st_size / type.division_size};
      if (stat_struct.st_size > type.division_size)
        file_results.push_back(std::format("\t{}({:.2f}{}) | bytes: ({}).", type.name, file_size, type.short_name, stat_struct.st_size));
      else 
        continue;
    }
  }

  return std::move(file_results);
}
