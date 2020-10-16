#include "Experiment_Data.h"
#include "Initialise_Pt_Cloud.h"
#include "Surrounding_Cloud.h"
#include "Compute_Brillouin_Zones.h"
#include "Draw_Brillouin_Zones.h"
#include "Extract_Data_Pts.h"
#include "Combine_And_Write_Extracted_Data.h"

void Brillouin_Algorithm ( Framework_Parameters const& f_p, Input& input, int num_inputs, int num_v, int motif_iter, int k_iter, int iter, Experiment_Data& e_d )
{
    double ** matrix;
    matrix = new double *[2];
    matrix[0] = new double [2];
    matrix[1] = new double [2];

    vector<P2> base_pts;

    Initialise_Pt_Cloud( input, matrix, f_p.uplusv, iter, base_pts );

    cout << "Computing Brillouin zones for " << base_pts.size() << " point(s):" << endl;

    vector<double> cell_volume( input.zone_limit, 0 );
    vector<vector<double>> results;

    for (int counter = 0; counter < base_pts.size(); ++counter)
    {
        clock_t check_point_1 = clock();
        
        vector<double> max_radii;
        vector<vector<Tri>> tris;
        multimap<double, P2> cloud;
        
        Surrounding_Cloud( input.perim, matrix, counter, base_pts, cloud );
        
        Compute_Brillouin_Zones( cloud, base_pts[counter], input.zone_limit, tris, max_radii, cell_volume, f_p.use_threads, f_p.extract_experiment_data, e_d.m_polys[motif_iter].second, e_d.m_edges[motif_iter].second, e_d.m_vertices[motif_iter].second, e_d.m_perim[motif_iter].second );
        
        if (f_p.draw_zones && counter == 0) Draw_Brillouin_Zones( f_p, input, num_inputs, base_pts, counter, matrix, tris );
        
        if (f_p.extract_data) Extract_Data_Pts( f_p, input, base_pts[counter], tris, cell_volume, max_radii, results );
        
        clock_t check_point_2 = clock();
        
        e_d.num_runs[motif_iter][k_iter] += 1;
        e_d.m_time[motif_iter].second[k_iter].second += check_point_2 - check_point_1;
    }
    
    /*for (int counter_2 = 0; counter_2 < cell_volume.size(); ++counter_2)
    {
        cout << counter_2 << " " << cell_volume[counter_2] << endl;
    }*/

    if (f_p.extract_data) Combine_And_Write_Extracted_Data( f_p, input, cell_volume, results, num_v, iter );

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
