#pragma once

#include <format>
#include <string_view>

struct DetailFormatter{};

template<>
struct std::formatter<DetailFormatter>
{};

