#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P2;
typedef K::Line_2 L2;
typedef Polygon_2<K> Poly;
typedef Poly::Vertex_iterator vertex_iterator;

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

int Line_Intersect_Polygon ( Poly& poly, L2 const& line )
{
    bool pos = false, neg = false;
    
    for (vertex_iterator v = poly.vertices_begin(); v != poly.vertices_end(); ++v)
    {
        P2 p = P2( v->x(), v->y() );
        
        if (squared_distance( p, line ) < tiny_num) continue;
        
        else if (line.oriented_side( p ) == ON_POSITIVE_SIDE) pos = true;
        
        else neg = true;
        
        if (pos && neg) break;
    }
    
    if (!pos || !neg)
    {
        if (!pos) return -1;
        
        else return 1;
    }
    
    else return 0;
}
