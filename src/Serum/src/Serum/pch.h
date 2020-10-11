#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <memory>
#include <utility>

#include <GLFW/glfw3.h>

#define BIND_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }