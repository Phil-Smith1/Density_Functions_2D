#include "Intersection_Area.h"

#include <CGAL/Triangle_2.h>

typedef K::Triangle_2 Tri;

double Disk_Triangle_Intersection ( Circle const& c, Tri const& t, double max_dist )
{
    double tri_area = t.area();
    
    if (tri_area < tiny_num) return 0;
    
    vector<P2> vertices;
    
    vertices.push_back( t.vertex( 0 ) );
    vertices.push_back( t.vertex( 1 ) );
    vertices.push_back( t.vertex( 2 ) );
    
    double precision = 1e12;
    
    long double x = (long long int)(vertices[0].x() * precision + 0.5);
    long double y = (long long int)(vertices[0].y() * precision + 0.5);
    
    x = x / (long double)precision;
    y = y / (long double)precision;
    
    vertices[0] = P2( x, y );
    
    x = (long long int)(vertices[1].x() * precision + 0.5);
    y = (long long int)(vertices[1].y() * precision + 0.5);
    
    x = x / (long double)precision;
    y = y / (long double)precision;
    
    vertices[1] = P2( x, y );
    
    x = (long long int)(vertices[2].x() * precision + 0.5);
    y = (long long int)(vertices[2].y() * precision + 0.5);
    
    x = x / (long double)precision;
    y = y / (long double)precision;
    
    vertices[2] = P2( x, y );
    
    vector<Edge> edges;
    
    edges.push_back( Edge( L2( vertices[0], vertices[1] ), vertices[0], vertices[1] ) );
    edges.push_back( Edge( L2( vertices[1], vertices[2] ), vertices[1], vertices[2] ) );
    edges.push_back( Edge( L2( vertices[2], vertices[0] ), vertices[2], vertices[0] ) );
    
    if (edges[0].line.oriented_side( vertices[2] ) == ON_NEGATIVE_SIDE)
    {
        edges[0].line = edges[0].line.opposite();
        edges[0].startpt = vertices[1];
        edges[0].endpt = vertices[0];
    }
    
    if (edges[1].line.oriented_side( vertices[0] ) == ON_NEGATIVE_SIDE)
    {
        edges[1].line = edges[1].line.opposite();
        edges[1].startpt = vertices[2];
        edges[1].endpt = vertices[1];
    }
    
    if (edges[2].line.oriented_side( vertices[1] ) == ON_NEGATIVE_SIDE)
    {
        edges[2].line = edges[2].line.opposite();
        edges[2].startpt = vertices[0];
        edges[2].endpt = vertices[2];
    }
    
    Circle large_circle( c.c, max_dist * 1.1 );
    
    double max_area = Intersection_Area( large_circle, edges, vertices );
    
    if (max_area < tiny_num) return 0;
    //if (max_area > tri_area + 0.0001) return 0;
    
    double area = Intersection_Area( c, edges, vertices );
    
    return area;
}
