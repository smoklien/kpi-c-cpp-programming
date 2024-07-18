#pragma once

#include <iostream>
#include <limits>
#include <cmath>

namespace colors {
	const std::string reset = "\033[0m";
	const std::string red = "\033[31m";
	const std::string yellow = "\033[33m";
	const std::string green = "\033[1;32m";
};

const float kMaxSideLength = 1e+9f;
const float kMinSideLength = 1e-5f;