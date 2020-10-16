#pragma once

#include "Input.h"
#include "Transformation_Matrix.h"
#include "Frac_To_Cart_Coords.h"

void Initialise_Pt_Cloud ( Input const& input, double ** matrix, bool uplusv, int iter, vector<P2>& base_pts );
