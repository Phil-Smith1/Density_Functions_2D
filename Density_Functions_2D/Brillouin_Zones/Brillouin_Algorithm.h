#pragma once

#include "Experiment_Data.h"
#include "Initialise_Pt_Cloud.h"
#include "Surrounding_Cloud.h"
#include "Compute_Brillouin_Zones.h"
#include "Draw_Brillouin_Zones.h"
#include "Extract_Data_Pts.h"
#include "Combine_And_Write_Extracted_Data.h"

void Brillouin_Algorithm ( Framework_Parameters const& f_p, Input& input, int num_inputs, int num_v, int motif_iter, int k_iter, int iter, Experiment_Data& e_d );
