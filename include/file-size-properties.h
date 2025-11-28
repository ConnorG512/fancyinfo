#pragma once

#include <string_view>

namespace SizeType
{
struct Properties
{
  double DivisionSize(this auto &&self) { self.DivisionSize(); }
  std::string_view Name(this auto &&self) { self.Name(); }
};

struct Kibibyte : public Properties
{
  consteval double DivisionSize() { return 1024.0f; };
  consteval std::string_view Name() { return "Kibibyte"; };
};

struct Mebibyte : public Properties
{
  consteval double DivisionSize() { return 1024.0f * 1024.0f; };
  consteval std::string_view Name() { return "Mebibyte"; };
};

struct Gibibyte : public Properties
{
  consteval double DivisionSize() { return 1024.0f * 1024.0f * 1024.0f; };
  consteval std::string_view Name() { return "Gibibyte"; };
};

struct Kilobyte : public Properties
{
  consteval double DivisionSize() { return 1000.0f; };
  consteval std::string_view Name() { return "Kilobyte"; };
};

struct Megabyte : public Properties
{
  consteval double DivisionSize() { return 1000.0f * 1000.0f; };
  consteval std::string_view Name() { return "Megabyte"; };
};

struct Gigabyte : public Properties
{
  consteval double DivisionSize() { return 1000.0f * 1000.0f * 1000.0f; };
  consteval std::string_view Name() { return "Gigabyte"; };
};
} // namespace SizeType
