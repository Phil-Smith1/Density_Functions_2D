#pragma once

#include "Dividing_Space.h"
#include "Triangulate_Zones.h"
#include "Compute_Experiment_Data.h"

void Compute_Brillouin_Zones ( multimap<double, P2>const& cloud, P2 const& base_pt, int zone_limit, vector<vector<Tri>>& tris, vector<double>& max_radii, vector<double>& cell_volume, bool use_threads, bool extract_experiment_data, vector<double>& num_polygons, vector<double>& num_edges, vector<double>& num_vertices, vector<double>& perimetre_length );
