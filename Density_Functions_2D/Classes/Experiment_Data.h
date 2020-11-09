// This class contains all the statistics about the experiment.

// num_runs contains the motif_size x k_size "matrix" of the number of runs performed in each configuration.

// m_time contains a motif_size x k_size "matrix", with each entry having the motif index, the k index and the mean time for this configuration.

// m_polys etc. contains a motif_size x k matrix, with each entry having the motif index and the mean number of specified objects.

// For time_vary_k, can vary m and k.
// For time_vary_m, can vary m and k, but only takes into account first k.
// For vary_k, can vary m but just 1 value of k.
// For vary_m, can vary m but just 1 value of k.

#pragma once

#include "Experiment.h"

class Experiment_Data
{
    public:
    
    vector<vector<double>> num_runs;
    vector<pair<int, vector<double>>> m_vertices, m_edges, m_polys, m_perim;
    vector<pair<int, vector<pair<int, double>>>> m_time;
    
    Experiment_Data ( Experiment const& e );
    
    Experiment_Data();
    ~Experiment_Data();
};
