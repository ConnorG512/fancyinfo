#pragma once

#include <string_view>

template<typename T>
struct FileSizeProperty {
    FileSizeProperty(const std::string_view name, double division_size)
      : name {name}
      , division_size{division_size} {}

    std::string_view name {""};
    T division_size {0};
};
