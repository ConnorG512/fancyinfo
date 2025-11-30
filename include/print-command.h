#pragma once

#include "file-size-properties.h"

#include <expected>
#include <span>
#include <string>
#include <vector>

namespace PrintCommand
{
[[nodiscard]] auto CalculateFileSizes(const std::span<char *> file_paths,
                                      const std::span<const File::Properties, 3> size_types) noexcept
    -> std::expected<std::vector<std::string>, std::string>;
};
