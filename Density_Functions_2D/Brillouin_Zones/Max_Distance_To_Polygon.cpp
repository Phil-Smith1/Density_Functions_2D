#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>

using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P2;
typedef Polygon_2<K> Poly;
typedef Poly::Vertex_iterator vertex_iterator;

double Max_Distance_To_Polygon ( P2 const& base_pt, Poly& poly )
{
    double max_radius = 0;
    
    for (vertex_iterator v = poly.vertices_begin(); v != poly.vertices_end(); ++v)
    {
        P2 p = P2( v->x(), v->y() );
        
        double dist = squared_distance( p, base_pt );
        
        if (dist > max_radius) max_radius = dist;
    }
    
    return sqrt( max_radius );
}
