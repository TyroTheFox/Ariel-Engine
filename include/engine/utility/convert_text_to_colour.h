#pragma once

#include <string>
#include <raylibcpp/raylib-cpp.hpp>
#include <raylib.h>

#include <cstdint>
#include <string_view>
#include <iostream>

constexpr uint64_t hash(std::string_view str);

constexpr uint64_t operator"" _hash(const char* str, size_t len);

Color convertTextToColour(std::string stringColour);