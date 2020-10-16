#pragma once

#include <string>
#include <vector>
#include <cmath>

using namespace std;

#ifndef Pi
#define Pi
const double PI = 3.14159265359;
#endif

void Transformation_Matrix ( vector<pair<string, double>>const& cell_shape, double ** matrix );
