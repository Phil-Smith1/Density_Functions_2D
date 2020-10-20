#pragma once

#include "Input.h"
#include "B_Poly.h"
#include "Experiment_Data.h"

typedef Poly::Vertex_iterator vertex_iterator;

void Compute_Experiment_Data ( Input const& input, vector<B_Poly>const& polys, Experiment_Data& e_d );
