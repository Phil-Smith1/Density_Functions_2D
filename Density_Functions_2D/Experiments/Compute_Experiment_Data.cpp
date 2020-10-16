#include "B_Poly.h"

using namespace std;

typedef K::Point_2 P2;
typedef Poly::Vertex_iterator vertex_iterator;

void Compute_Experiment_Data ( int zone_limit, vector<B_Poly>const& polys, vector<double>& num_vertices, vector<double>& num_edges, vector<double>& num_polygons, vector<double>& perimetre_length )
{
    vector<int> num_vertices_per_zone( zone_limit, 0 );
    vector<int> num_edges_per_zone( zone_limit, 0 );
    vector<int> num_polys_per_zone( zone_limit, 0 );
    vector<double> perim_length_per_zone( zone_limit, 0 );
    
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
    
    for (int counter_1 = 1; counter_1 < zone_limit; ++counter_1)
    {
        num_vertices_per_zone[counter_1] = num_edges_per_zone[counter_1] - num_polys_per_zone[counter_1];
    }
    
    for (int counter = 0; counter < zone_limit; ++counter)
    {
        num_vertices[counter] += num_vertices_per_zone[counter];
        num_edges[counter] += num_edges_per_zone[counter];
        num_polygons[counter] += num_polys_per_zone[counter];
        perimetre_length[counter] += perim_length_per_zone[counter];
    }
}
