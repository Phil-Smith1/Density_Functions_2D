#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/convex_hull_2.h>

using namespace std;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P2;
typedef K::Vector_2 V2;
typedef Polygon_2<K> Poly;

void Generate_Square ( double square_size, P2 const& centre, Poly& square )
{
    V2 v = centre - ORIGIN;
    
    vector<P2> vertices;
    vertices.reserve( 4 );
    
    vertices.push_back( P2( square_size, square_size) + v );
    vertices.push_back( P2( square_size, -square_size ) + v );
    vertices.push_back( P2( -square_size, square_size ) + v );
    vertices.push_back( P2( -square_size, -square_size ) + v );
    
    vector<P2> results;
    
    convex_hull_2( vertices.begin(), vertices.end(), back_inserter( results ) );
    
    square = Poly( results.begin(), results.end() );
}
