#pragma once

#include "string_view"
    #include <array>

namespace File {
  struct Properties {
    consteval Properties(const std::string_view name, const std::string_view short_name, const float division_size = 1)
      : name {name}
      , short_name {short_name} 
      , division_size {division_size} {}
  
      const std::string_view name{""};
      const std::string_view short_name{""};
      const double division_size {1};
  };

  namespace ArrayPresets {
    constexpr auto human = std::to_array<File::Properties>
    ({
     {"Gibabyte", "GB", 1000.0f * 1000.0f * 1000.0f},
     {"Megabyte", "MB", 1000.0f * 1000.0f },
     {"Kilobyte", "KB", 1000.0f },
    });
    
    constexpr auto binary = std::to_array<File::Properties>
    ({
     {"Gibibyte", "GiB", 1024.0f * 1024.0f * 1024.0f},
     {"Mebibyte", "MiB", 1024.0f * 1024.0f },
     {"Kibibyte", "KiB", 1024.0f },
    });
  }
}

