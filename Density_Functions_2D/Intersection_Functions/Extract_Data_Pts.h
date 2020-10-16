#pragma once

#include "Framework_Parameters.h"
#include "Data_Pts_For_Given_Radius.h"

#include <fstream>
#include <thread>

void Extract_Data_Pts ( Framework_Parameters const& f_p, Input& input, P2 const& base_pt, vector<vector<Tri>> tris, vector<double>const& cell_volume, vector<double>const& max_radii, vector<vector<double>>& results );
