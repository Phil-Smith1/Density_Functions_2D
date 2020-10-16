#pragma once

#include "Framework_Parameters.h"
#include "Input.h"
#include "Surrounding_Cloud.h"
#include "Scale_Drawing.h"
#include "Colour.h"

#include <opencv2/imgcodecs.hpp>

void Draw_Brillouin_Zones ( Framework_Parameters const& f_p, Input const& input, int num_inputs, vector<P2> base_pts, int base_pt, double ** matrix, vector<vector<Tri>>const& tris );
