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
    
    if (Norm( c.c, vertices[0] ) < c.r + tiny_num && Norm( c.c, vertices[1] ) < c.r + tiny_num && Norm( c.c, vertices[2] ) < c.r + tiny_num) return tri_area;
    
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
    
    double area = Intersection_Area( c, edges, vertices );
    
    if (area > tri_area)
    {
        if (area > tri_area + 5e-4) // This seems to happen when c.r is large (>100).
        {
            cout << "Warning: area computed significantly greater than the triangle area." << endl;
            cout << "Computed area: " << area << " Triangle area: " << tri_area << endl;
        }
        
        return tri_area;
    }
    
    if (area < tiny_num)
    {
        if (area < tiny_num - 5e-4) // This seems to happen when c.r is large (>100).
        {
            cout << "Warning: area computed significantly negative." << endl;
            cout << "Computed area: " << area << " Triangle area: " << tri_area << endl;
        }
        
        return 0;
    }
    
    return area;
}
