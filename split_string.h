#pragma once

#include <vector>
#include <string>
#include <string_view>

std::vector<std::string> split_string(const std::string& s, char delimiter);

std::vector<std::string_view> split_string(std::string_view s, char delimiter);
