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
enum class SizeType
{
  kibibyte,
  mebibyte,
  gibibyte,
};
auto printSize = [](const auto byte_size, SizeType size_type)
{
  switch (size_type)
  {
    case SizeType::kibibyte:
      {
        const float file_size{static_cast<float>(byte_size) / 1024.0f};
        std::println("\tSize: Kibibyte: {:.2}KiB ({}bytes)", file_size, byte_size);
        break;
      }
    case SizeType::mebibyte:
      {
        const float file_size{static_cast<float>(byte_size) / (1024.0f * 1024.0f)};
        std::println("\tSize: Mebibyte: {:.2}MiB ({}bytes)", file_size, byte_size);
        break;
      }
    case SizeType::gibibyte:
      {
        const float file_size{static_cast<float>(byte_size) / (1024.0f * 1024.0f * 1024.0f)};
        std::println("\tSize: Mebibyte: {:.2}MiB ({}bytes)", file_size, byte_size);
        break;
      }
  }
};
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
    { // Kibibyte
      printSize(stat_struct.st_size, SizeType::kibibyte);
      continue;
    }
    else if (stat_struct.st_size > 1024 * 1024)
    { // Mebibyte
      printSize(stat_struct.st_size, SizeType::mebibyte);
      continue;
    }
    std::println("\tSize: {}bytes", stat_struct.st_size);
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
