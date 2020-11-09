#include "Read_Framework_Parameters.h"
#include "Read_Experiment.h"
#include "Read_Input.h"
#include "Initialise_Lattice.h"
#include "Read_V.h"
#include "Add_Random_Pts.h"
#include "Initialise_Pt_Cloud.h"
#include "Brillouin_Algorithm.h"
#include "Produce_Variance_File.h"
#include "Plot_Graph.h"
#include "Experiment_Calculations.h"
#include "Write_Experiment_Data.h"
#include "Plot_Experiments.h"
#include "Print_Info.h"

int main( int, char*[] )
{
    clock_t start_code_runtime = clock(); // Starts the clock measuring the runtime of the code.
    
    chrono::time_point<chrono::steady_clock> start_absolute_time = chrono::steady_clock::now(); // Starts the clock measuring the absolute time to complete the code.
    
    srand( (int)time( 0 ) ); // Seeding the random number generator.
    
    Framework_Parameters f_p; // Class containing details of what functions to run etc.
    
    if (!Read_Framework_Parameters( f_p )) return 1; // Reading the framework parameters.
    
    Experiment e; // Class containing information about the type of experiment to be performed.
    
    if (!Read_Experiment( f_p, e )) return 1; // Reading the experiment.
    
    ifstream ifs_1( f_p.input_dir + f_p.input_file ); // Opening the input file.
    
    if (!ifs_1.is_open())
    {
        cout << "Input file not found!" << endl;
        return 1;
    }
    
    int num_inputs = 0; // Counter for the number of inputs.
    string line_data; // Generic string.
    Experiment_Data e_d( e ); // Class containing all the statistics about the experiment.
    
    while (getline( ifs_1, line_data )) // Looping over the inputs.
    {
        ++num_inputs; // Increase number of inputs counter.
        
        Input input; // Class containing all the information about the input.
        input.num_input = num_inputs;
        
        if (!Read_Input( f_p, line_data, input )) return 1; // Reading the input.
        
        Initialise_Lattice( input ); // Computing the transformation matrix and the lattice vectors.
        
        ifstream ifs_2( f_p.input_dir + f_p.v_file ); // Opening the file containing 'V' point sets.
        
        if (!ifs_2.is_open())
        {
            cout << "V file not found!" << endl;
            return 1;
        }
        
        while ((f_p.uplusv && getline( ifs_2, line_data )) || input.num_v == 0) // If uplusv, looping over V, else goes once through.
        {
            ++input.num_v;
            
            if (f_p.uplusv && !Read_V( f_p, line_data, input )) return 1; // Reading the V file.
            
            for (int motif_iter = 0; motif_iter < e.motif_sizes.size(); ++motif_iter) // Looping over motif sizes.
            {
                input.motif_iter = motif_iter;
                input.random_pts = e.motif_sizes[motif_iter] - (int)input.frac_base_pts.size();
                
                for (int k_iter = 0; k_iter < e.k.size(); ++k_iter) // Looping over maximum zone k.
                {
                    input.k_iter = k_iter;
                    input.zone_limit = input.perim = e.k[k_iter];
                    
                    for (int rep_iter = 0; rep_iter < e.repetitions; ++rep_iter) // Repeating e.repetitions times.
                    {
                        input.rep_iter = rep_iter;
                        
                        Add_Random_Pts( input ); // Adding input.random_pts number of random points.
                        
                        Initialise_Pt_Cloud( input, f_p.uplusv ); // Producing the vector of base points in Cartesian coordinates.
                        
                        if (!f_p.replot) Brillouin_Algorithm( f_p, input, e_d ); // Main computations occur here.
                        
                        if (f_p.variance) Produce_Variance_File( f_p, input ); // Producing the variance file.
                        
                        if (f_p.plot_graph) Plot_Graph( f_p, input ); // Plotting the graph.
                    }
                }
            }
        }
        
        ifs_2.close();
    }
    
    ifs_1.close();
    
    if (!f_p.replot && f_p.extract_experiment_data) Experiment_Calculations( f_p, e_d ); // Experiment calculations, e.g. taking the average over all iterations.
    
    if (!f_p.replot && f_p.extract_experiment_data) Write_Experiment_Data( f_p, e_d ); // Writing the experiment statistics to a txt file.
    
    if (f_p.plot_experiments) Plot_Experiments( f_p, e.k[0] ); // Plotting experiment results in a graph.
    
    Print_Info( start_code_runtime, start_absolute_time );
    
    return 0;
}
