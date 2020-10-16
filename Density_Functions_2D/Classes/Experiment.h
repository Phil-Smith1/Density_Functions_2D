#pragma once

#include <vector>

using namespace std;

class Experiment
{
    public:
    
    int repetitions;
    vector<int> motif_sizes;
    vector<int> k;
    
    Experiment();
    ~Experiment();
};
