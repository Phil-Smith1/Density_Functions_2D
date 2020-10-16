#pragma once

#include "Generate_Square.h"
#include "Divide_Polygon.h"

#include <thread>

void Dividing_Space ( multimap<double, P2>const& cloud, P2 const& base_pt, int zone_limit, vector<B_Poly>& final_polys, vector<double>& max_radii, bool use_threads );
