#pragma once

#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <boost/regex.hpp>
#include <locale>
#include <vector>

using std::cout;
using std::cin;
using std::ostream;
using std::setw;
using std::string;
using std::transform;
using std::vector;

#define stop __asm nop

#define TEXT_COLOR_DEFAULT FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE

#define IS_IN_RANGE_CLOSED(x, min, max) ((x >= min) && (x <= max))

