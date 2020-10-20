#pragma once

#include "Framework_Parameters.h"
#include "Input.h"
#include "Scale_Drawing.h"
#include "Colour.h"

#include <opencv2/imgcodecs.hpp>

void Draw_Brillouin_Zones ( Framework_Parameters const& f_p, Input const& input, int base_pt, multimap<double, P2>const& cloud, vector<vector<Tri>>const& tris );
