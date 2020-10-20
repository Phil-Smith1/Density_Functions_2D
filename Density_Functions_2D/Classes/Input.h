#pragma once

#include <string>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P2;

class Input
{
    public:
    
    int zone_limit, perim, random_pts, num_input, num_v = 0, motif_iter, k_iter, rep_iter;
    double cell_param_a, cell_param_b, cell_param_gamma, max_radius = 0;
    double ** matrix;
    string data_file, graph_file, drawing_file;
    vector<P2> frac_base_pts, frac_random_pts, frac_V, lattice_vectors, base_pts;
    
    Input();
    ~Input();
};

