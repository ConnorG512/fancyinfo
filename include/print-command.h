#pragma once

#include "file-size-properties.h"

#include <expected>
#include <span>
#include <string>

namespace PrintCommand
{
[[nodiscard]] auto CalculateFileSizes(const std::span<char *> file_paths,
                                      const std::span<const FileSizeProperty<double>> size_types) noexcept
    -> std::expected<void, std::string>;
};
