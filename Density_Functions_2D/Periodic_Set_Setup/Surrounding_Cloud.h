#pragma once

#include "Frac_To_Cart_Coords.h"

using namespace std;

typedef K::Vector_2 V2;

void Surrounding_Cloud ( int perim, double ** matrix, int index, vector<P2>const& base_pts, multimap<double, P2>& cloud );
