#include "Surrounding_Cloud.h"
#include "Compute_Brillouin_Zones.h"
#include "Draw_Brillouin_Zones.h"
#include "Extract_Data_Pts.h"
#include "Combine_And_Write_Extracted_Data.h"

void Brillouin_Algorithm ( Framework_Parameters const& f_p, Input& input, Experiment_Data& e_d )
{
    cout << "Computing Brillouin zones for " << input.base_pts.size() << " point(s):" << endl;

    vector<double> zone_area( input.zone_limit, 0 ); // Records the area of the zone for each k.
    vector<vector<double>> results; // Will contains sampled values of the density functions.

    for (int counter = 0; counter < input.base_pts.size(); ++counter) // Looping over base points.
    {
        clock_t check_point_1 = clock(); // Starts the clock that measures the time of Brillouin zone computations.
        
        vector<double> max_radii; // Contains the maximum radius of each zone from the base point.
        vector<vector<Tri>> tris; // Contains the Brillouin zones, stored as a vector of triangles for each zone.
        multimap<double, P2> cloud; // The cloud surrounding the base point.
        
        Surrounding_Cloud( input, counter, cloud ); // Computing the surrounding cloud.
        
        Compute_Brillouin_Zones( f_p, input, input.base_pts[counter], cloud, zone_area, max_radii, tris, e_d ); // Computing the Brillouin zones.
        
        if (f_p.draw_zones && counter == 0) Draw_Brillouin_Zones( f_p, input, counter, cloud, tris ); // Drawing the Brillouin zones.
        
        if (f_p.extract_data) Extract_Data_Pts( f_p, input, input.base_pts[counter], max_radii, tris, results ); // Computing the intersection of the base point with its Brillouin zones for varying radii.
        
        clock_t check_point_2 = clock();
        
        e_d.num_runs[input.motif_iter][input.k_iter] += 1;
        e_d.m_time[input.motif_iter].second[input.k_iter].second += check_point_2 - check_point_1;
    }

    if (f_p.extract_data) Combine_And_Write_Extracted_Data( f_p, input, zone_area, results ); // Writing results.

    /*if (f_p.use_threads)
    {
        vector<thread> thr;
        
        for (int counter = 0; counter < base_pts.size(); ++counter)
        {
            thr.push_back( thread( Compute_Brillouin_Zones, clouds[counter], base_pts[counter], input.zone_limit, ref( tris[counter] ), ref( max_radii[counter] ), ref( cell_volume ), true ) );
        }
        
        for (int counter = 0; counter < base_pts.size(); ++counter)
        {
            thr[counter].join();
        }
    }

    else
    {
        for (int counter = 0; counter < base_pts.size(); ++counter)
        {
            Compute_Brillouin_Zones( clouds[counter], base_pts[counter], input.zone_limit, tris[counter], max_radii[counter], ref( cell_volume ), false );
        }
    }*/
}
