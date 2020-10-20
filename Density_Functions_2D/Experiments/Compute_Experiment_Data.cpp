#include "Input.h"
#include "B_Poly.h"
#include "Experiment_Data.h"

typedef Poly::Vertex_iterator vertex_iterator;

void Compute_Experiment_Data ( Input const& input, vector<B_Poly>const& polys, Experiment_Data& e_d )
{
    vector<int> num_vertices_per_zone( input.zone_limit, 0 );
    vector<int> num_edges_per_zone( input.zone_limit, 0 );
    vector<int> num_polys_per_zone( input.zone_limit, 0 );
    vector<double> perim_length_per_zone( input.zone_limit, 0 );
    
    for (int counter = 0; counter < polys.size(); ++counter)
    {
        num_polys_per_zone[polys[counter].zone - 1] += 1;
        
        num_edges_per_zone[polys[counter].zone - 1] += (int)polys[counter].poly.size();
        
        for (vertex_iterator v = polys[counter].poly.vertices_begin(); v != polys[counter].poly.vertices_end() - 1; ++v)
        {
            P2 p1 = P2( v->x(), v->y() );
            
            ++v;
            
            P2 p2 = P2( v->x(), v->y() );
            
            --v;
            
            double dist = sqrt( squared_distance( p1, p2 ) );
            
            perim_length_per_zone[polys[counter].zone - 1] += dist;
        }
        
        vertex_iterator v = polys[counter].poly.vertices_begin();
        
        P2 p1 = P2( v->x(), v->y() );
        
        v = polys[counter].poly.vertices_end() - 1;
        
        P2 p2 = P2( v->x(), v->y() );
        
        double dist = sqrt( squared_distance( p1, p2 ) );
        
        perim_length_per_zone[polys[counter].zone - 1] += dist;
    }
    
    num_vertices_per_zone[0] = 1 + num_edges_per_zone[0] - num_polys_per_zone[0];
    
    for (int counter_1 = 1; counter_1 < input.zone_limit; ++counter_1)
    {
        num_vertices_per_zone[counter_1] = num_edges_per_zone[counter_1] - num_polys_per_zone[counter_1];
    }
    
    for (int counter = 0; counter < input.zone_limit; ++counter)
    {
        e_d.m_vertices[input.motif_iter].second[counter] += num_vertices_per_zone[counter];
        e_d.m_edges[input.motif_iter].second[counter] += num_vertices_per_zone[counter];
        e_d.m_polys[input.motif_iter].second[counter] += num_vertices_per_zone[counter];
        e_d.m_perim[input.motif_iter].second[counter] += num_vertices_per_zone[counter];
    }
}
