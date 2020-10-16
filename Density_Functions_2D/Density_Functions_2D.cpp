#include "Read_Framework_Parameters.h"
#include "Read_Experiment.h"
#include "Read_Input.h"
#include "Read_V.h"
#include "Add_Random_Pts.h"
#include "Brillouin_Algorithm.h"
#include "Produce_Variance_File.h"
#include "Plot_Graph.h"
#include "Experiment_Calculations.h"
#include "Write_Experiment_Data.h"
#include "Plot_Experiments.h"
#include "Print_Info.h"

// Sample_rate usually 20, set for 10 for hyperuniformity.
// Usually perim = zone_limit, set for 1 for hyperuniformity.

int main( int, char*[] )
{
    clock_t start_code_runtime = clock(); // Starts the clock measuring the runtime of the code.
    
    chrono::time_point<chrono::steady_clock> start_absolute_time = chrono::steady_clock::now(); // Starts the clock measuring the absolute time to complete the code.
    
    srand( (int)time( 0 ) ); // Seeding the random number generator.
    
    Framework_Parameters f_p;
    
    if (!Read_Framework_Parameters( f_p )) return 1; // Reading framework parameters.
    
    Experiment e;
    
    if (!Read_Experiment( f_p, e )) return 1; // Reading the experiment.
    
    ifstream ifs_1( f_p.input_dir + f_p.input_file );
    
    if (!ifs_1.is_open())
    {
        cout << "Input file not found!" << endl;
        return 1;
    }
    
    int num_inputs = 0;
    string line_data;
    Experiment_Data e_d( e );
    
    while (getline( ifs_1, line_data ))
    {
        ++num_inputs;
        
        Input input;
        
        if (!Read_Input( f_p, line_data, input )) return 1; // Reading the input.
        
        ifstream ifs_2( f_p.input_dir + f_p.v_file );
        
        if (!ifs_2.is_open())
        {
            cout << "V file not found!" << endl;
            return 1;
        }
        
        int num_v = 0;
        
        while (getline( ifs_2, line_data ) || num_v == 0)
        {
            ++num_v;
            
            if (f_p.uplusv && !Read_V( f_p, line_data, input )) return 1; // Reading V file.
            
            for (int motif_iter = 0; motif_iter < e.motif_sizes.size(); ++motif_iter)
            {
                input.random_pts = e.motif_sizes[motif_iter] - 1;
                
                for (int k_iter = 0; k_iter < e.k.size(); ++k_iter)
                {
                    input.zone_limit = input.perim = e.k[k_iter];
                    
                    for (int iter = 0; iter < e.repetitions; ++iter)
                    {
                        Add_Random_Pts( input );
                        
                        if (!f_p.replot) Brillouin_Algorithm( f_p, input, num_inputs, num_v, motif_iter, k_iter, iter, e_d );
                        
                        if (f_p.variance) Produce_Variance_File( f_p.output_dir + "Data/Poi/0_Data.txt" );
                        
                        if (f_p.plot_graph) Plot_Graph( input, f_p, num_v, iter );
                    }
                }
            }
        }
        
        ifs_2.close();
    }
    
    ifs_1.close();
    
    if (f_p.extract_experiment_data) Experiment_Calculations( f_p.time_vary_k, f_p.vary_k, e, e_d );
    
    if (!f_p.replot && f_p.extract_experiment_data) Write_Experiment_Data( f_p, e_d );
    
    if (f_p.plot_experiments) Plot_Experiments( f_p, e.k[0] );
    
    Print_Info( start_code_runtime, start_absolute_time );
    
    return 0;
}
