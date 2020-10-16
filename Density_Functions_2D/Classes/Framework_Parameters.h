#pragma once

#include <string>

using namespace std;

class Framework_Parameters
{
    public:
    
    bool replot, draw_zones, extract_data, densigram, variance, plot_graph, title, extract_experiment_data, plot_experiments, time_vary_k, time_vary_m, vary_k, vary_m, uplusv, superimposed, use_threads;
    int sample_rate;
    string input_dir, output_dir, input_file, experiment_file, v_file, title_str;
    
    Framework_Parameters();
    ~Framework_Parameters();
};
