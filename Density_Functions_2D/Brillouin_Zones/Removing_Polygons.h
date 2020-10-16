#pragma once

#include "B_Poly.h"

using namespace std;

typedef K::Point_2 P2;

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

void Removing_Polygons ( P2 const& base_pt, double line_distance, vector<B_Poly>& polys, vector<B_Poly>& final_polys, int zone_limit );
