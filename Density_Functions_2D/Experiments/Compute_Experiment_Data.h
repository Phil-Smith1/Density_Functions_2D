#pragma once

#include "B_Poly.h"

using namespace std;

typedef K::Point_2 P2;
typedef Poly::Vertex_iterator vertex_iterator;

void Compute_Experiment_Data ( int zone_limit, vector<B_Poly>const& polys, vector<double>& num_vertices, vector<double>& num_edges, vector<double>& num_polygons, vector<double>& perimetre_length );
