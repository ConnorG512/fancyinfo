#include "file-size-properties.h"
#include "print-command.h"

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <print>
#include <ranges>
#include <sys/stat.h>
#include <filesystem>

[[nodiscard]] auto PrintCommand::CalculateFileSizes(const std::span<char *> file_paths,
                                                    const std::span<const File::Properties, 3> size_types) noexcept
    -> std::expected<std::vector<std::string>, std::string>
{
  std::vector<std::string> file_results{};

  for (const char *path : file_paths.subspan(1) 
                              | std::views::filter([](const char *command) { return std::memcmp(command, "-", 1) != 0; })
                              | std::views::filter([](const char *path){ return !std::filesystem::is_directory(path);}))
  {
    file_results.push_back(std::format("\033[1mFile: {}\033[0m", path));
    for (const auto &type : size_types)
    {
      const double file_size{std::filesystem::file_size(path) / type.division_size};
      if (std::filesystem::file_size(path) > type.division_size)
        file_results.push_back(std::format("\t{}({:.2f}{}) | bytes: ({}).", type.name, file_size, type.short_name, std::filesystem::file_size(path)));
      else 
        continue;
    }
  }

  return std::move(file_results);
}
