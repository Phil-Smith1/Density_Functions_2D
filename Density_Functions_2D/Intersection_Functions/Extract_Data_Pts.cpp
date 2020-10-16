#include "Framework_Parameters.h"
#include "Data_Pts_For_Given_Radius.h"

#include <fstream>
#include <thread>

void Extract_Data_Pts ( Framework_Parameters const& f_p, Input& input, P2 const& base_pt, vector<vector<Tri>> tris, vector<double>const& cell_volume, vector<double>const& max_radii, vector<vector<double>>& results )
{
    double max_radius = max_radii[max_radii.size() - 1];
    
    int num_pts = max_radius * f_p.sample_rate + 1;
    
    if (num_pts < max_radius * f_p.sample_rate + 1) ++num_pts;
    
    if (input.max_radius < (num_pts - 1) / (double)f_p.sample_rate) input.max_radius = (num_pts - 1) / (double)f_p.sample_rate;
    
    if (num_pts < results.size()) num_pts = (int)results.size();
    
    if (results.size() == 0)
    {
        vector<double> vec( input.zone_limit + 1, 0 );
        
        results.push_back( vec );
    }
    
    if (num_pts > results.size())
    {
        for (int counter = (int)results.size(); counter < num_pts; ++counter)
        {
            vector<double> vec( input.zone_limit + 1 );
            vec[0] = counter / (double)f_p.sample_rate;
            
            for (int counter_2 = 0; counter_2 < input.zone_limit; ++counter_2)
            {
                vec[counter_2 + 1] = results[results.size() - 1][counter_2 + 1];
            }
            
            results.push_back( vec );
        }
    }
    
    if (f_p.use_threads)
    {
        vector<thread> thr;
        
        for (int counter = 0; counter < num_pts; ++counter)
        {
            thr.push_back( thread( Data_Pts_For_Given_Radius, input, counter, base_pt, tris, max_radii, ref( results[counter] ) ) );
        }
        
        for (int counter = 0; counter < num_pts; ++counter)
        {
            thr[counter].join();
        }
    }
    
    else
    {
        for (int counter = 0; counter < num_pts; ++counter)
        {
            results[counter].resize( input.zone_limit + 1 );
            
            Data_Pts_For_Given_Radius( input, counter, base_pt, tris, max_radii, results[counter] );
        }
    }
}
