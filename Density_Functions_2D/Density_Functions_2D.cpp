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
    //return 0;
    
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
                        
                        if (f_p.variance) Produce_Variance_File( f_p, input );
                        
                        if (f_p.plot_graph) Plot_Graph( f_p, input );
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
    
    /*P2 p1 = P2( 50, -15 );
    P2 p2 = P2( 51.1538, -13.4615 );
    P2 p3 = P2( 50, -10 );
    Circle c = Circle( P2( 30, 0 ), 25 );
    double max_dist = 26.8742;*/
    
    /*P2 p1 = P2( 88.333333339259, -18.333333284811 );
    P2 p2 = P2( 89.99999996, -20.000000000001 );
    P2 p3 = P2( 89.999999979998, -15.000000000003 );
    Circle c = Circle( P2( 109.99999998, 0 ), 25 );
    double max_dist = 28.3823;*/
    
    /*P2 p1 = P2( 137.5, 15 );
    P2 p2 = P2( 139.999999980009, 10 );
    P2 p3 = P2( 140.000000010002, 15 );
    Circle c = Circle( P2( 120, 0 ), 25 );
    double max_dist = 28.382310605278;*/
    
    /*P2 p1 = P2( 50.000000016501, -21.000000005399 );
    P2 p2 = P2( 52.500000027502, -19.999999999998 );
    P2 p3 = P2( 50.000000018751, -19.999999999998 );
    Circle c = Circle( P2( 30.00000003, 0 ), 29 );
    double max_dist = 32.3406611763159;*/
    
    /*P2 p1 = P2( 49.999999951251, 19.999999999998 );
    P2 p2 = P2( 51.666666681801, 21.666666693054 );
    P2 p3 = P2( 49.999999953501, 21.0000000054 );
    Circle c = Circle( P2( 69.99999994, 0 ), 29 );
    double max_dist = 33.5790264996836;*/
    
    /*P2 p1 = P2( 47.307692241921, -20.384615366536 );
    P2 p2 = P2( 49.999999955749, -21.999999989448 );
    P2 p3 = P2( 49.999999953499, -21.000000005399);
    Circle c = Circle( P2( 69.99999994, 0 ), 29 );
    double max_dist = 35.4597863461711;*/
    
    /*Tri t = Tri( p1, p2, p3 );
    
    cout << Disk_Triangle_Intersection( c, t, max_dist ) << endl;*/
    
    Print_Info( start_code_runtime, start_absolute_time );
    
    return 0;
}
