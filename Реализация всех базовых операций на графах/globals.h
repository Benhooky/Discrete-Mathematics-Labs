#pragma once

#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include <algorithm>
#include <iomanip> 
#include <string>
#include <regex>
#include <queue>
#include <map>
#include <numeric>
#include <fstream>
#include "MyShuffler.h"
using namespace std;

#define stop __asm nop

#define UNIFORM_DISTRIB_MAX 1000000

#define InRange(x, min, max) ((x >= min) && (x <= max))

#define OUTPUT_FILE_NAME "output.txt"

int PascalRngg(double m = 2, double p = 0.5);
void PrintMatrix(const vector<vector<int>> vec);

vector<vector<int>> matrixBoolMult(const vector<vector<int>> mxA, const vector<vector<int>> mxB);
vector<vector<int>> matrixAdd(const vector<vector<int>> mxA, const vector<vector<int>> mxB);
int factorial(int a);
int MatrixMinor(const vector<vector<int>> mx);

