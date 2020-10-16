#pragma once

#include "Input.h"
#include "Disk_Triangle_Intersection.h"

void Data_Pts_For_Given_Radius ( Input const input, int sample, P2 const base_pt, vector<vector<Tri>>const tris, vector<double>const max_radii, vector<double>& volume );
