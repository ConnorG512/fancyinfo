#pragma once

#include <print>

namespace File
{
struct SizePrinter
{
  void printSize(this auto &&self, auto byte_size) { self.print(byte_size); }
};

struct Kibibyte : public SizePrinter
{
  static constexpr float division_size{1024.0f};

  void print(const auto byte_size)
  {
    const float file_size{static_cast<float>(byte_size) / division_size};
    std::println("\tSize:{:.2}KiB ({}bytes)", file_size, byte_size);
  }
};

struct Mebibyte : public SizePrinter
{
  static constexpr float division_size{1024.0f * 1024.0f};
  void print(const auto byte_size)
  {
    const float file_size{static_cast<float>(byte_size) / division_size};
    std::println("\tSize:{:.2}MiB ({}bytes)", file_size, byte_size);
  }
};

struct Gibibyte : public SizePrinter
{
  static constexpr float division_size{1024.0f * 1024.0f * 1024.0f};
  void print(const auto byte_size)
  {
    const float file_size{static_cast<float>(byte_size) / division_size};
    std::println("\tSize{:.2}GiB ({}bytes)", file_size, byte_size);
  }
};
} // namespace File
