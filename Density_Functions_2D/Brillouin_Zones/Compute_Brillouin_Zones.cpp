#include "Dividing_Space.h"
#include "Triangulate_Zones.h"
#include "Compute_Experiment_Data.h"

void Compute_Brillouin_Zones ( multimap<double, P2>const& cloud, P2 const& base_pt, int zone_limit, vector<vector<Tri>>& tris, vector<double>& max_radii, vector<double>& cell_volume, bool use_threads, bool extract_experiment_data, vector<double>& num_polygons, vector<double>& num_edges, vector<double>& num_vertices, vector<double>& perimetre_length )
{
    vector<B_Poly> polys;
    polys.reserve( 3000 );
    
    Dividing_Space( cloud, base_pt, zone_limit, polys, max_radii, use_threads );
    
    Triangulate_Zones( polys, zone_limit, tris, cell_volume );
    
    //cout << "Number of polygons: " << polys.size() << "." << endl;
    
    if (extract_experiment_data) Compute_Experiment_Data( zone_limit, polys, num_vertices, num_edges, num_polygons, perimetre_length );
}
