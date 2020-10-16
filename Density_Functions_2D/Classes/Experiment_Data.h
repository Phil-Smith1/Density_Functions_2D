#pragma once

#include "Experiment.h"

class Experiment_Data
{
    public:
    
    vector<vector<double>> num_runs;
    vector<pair<int, vector<pair<int, double>>>> m_time;
    vector<pair<int, vector<double>>> m_polys, m_edges, m_vertices, m_perim;
    
    Experiment_Data ( Experiment const& e );
    
    Experiment_Data();
    ~Experiment_Data();
};
