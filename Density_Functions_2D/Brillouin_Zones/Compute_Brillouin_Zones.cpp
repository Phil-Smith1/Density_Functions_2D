#include "Framework_Parameters.h"
#include "Dividing_Space.h"
#include "Triangulate_Zones.h"
#include "Compute_Experiment_Data.h"

void Compute_Brillouin_Zones ( Framework_Parameters const& f_p, Input const& input, P2 const& base_pt, multimap<double, P2>const& cloud, vector<double>& zone_area, vector<double>& max_radii, vector<vector<Tri>>& tris, Experiment_Data& e_d )
{
    vector<B_Poly> polys;
    polys.reserve( 3000 );
    
    Dividing_Space( cloud, base_pt, input.zone_limit, polys, max_radii, f_p.use_threads );
    
    Triangulate_Zones( polys, input.zone_limit, tris, zone_area );
    
    //cout << "Number of polygons: " << polys.size() << "." << endl;
    
    if (f_p.extract_experiment_data) Compute_Experiment_Data( input, polys, e_d );
}
