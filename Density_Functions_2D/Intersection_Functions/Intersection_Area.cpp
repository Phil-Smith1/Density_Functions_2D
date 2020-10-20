#include "Line_Circle_Intersections.h"
#include "Irregular_Sector_Area.h"

using namespace std;

double Intersection_Area ( Circle const& c, vector<Edge>& edges, vector<P2> const& vertices )
{
    double volume1 = 0, volume2 = 0, volume3 = 0, volume4 = 0, volume5 = 0, volume6 = 0;
    
    int intersection_1 = Line_Circle_Intersections( c, edges[0] );
    int intersection_2 = Line_Circle_Intersections( c, edges[1] );
    int intersection_3 = Line_Circle_Intersections( c, edges[2] );
    
    if (intersection_1 == 1 || intersection_1 == 0)
    {
        if (edges[0].line.oriented_side( c.c ) == ON_NEGATIVE_SIDE) volume1 = c.area;
        
        else volume1 = 0;
    }
    
    if (intersection_2 == 1 || intersection_2 == 0)
    {
        if (edges[1].line.oriented_side( c.c ) == ON_NEGATIVE_SIDE) volume2 = c.area;
        
        else volume2 = 0;
    }
    
    if (intersection_3 == 1 || intersection_3 == 0)
    {
        if (edges[2].line.oriented_side( c.c ) == ON_NEGATIVE_SIDE) volume3 = c.area;
        
        else volume3 = 0;
    }
    
    if (intersection_1 == 2)
    {
        volume1 = Segment_Area( c, edges[0].i1, edges[0].i2 );
        
        if (edges[0].line.oriented_side( c.c ) == ON_NEGATIVE_SIDE) volume1 = c.area - volume1;
    }
    
    if (intersection_2 == 2)
    {
        volume2 = Segment_Area( c, edges[1].i1, edges[1].i2 );
        
        if (edges[1].line.oriented_side( c.c ) == ON_NEGATIVE_SIDE) volume2 = c.area - volume2;
    }
    
    if (intersection_3 == 2)
    {
        volume3 = Segment_Area( c, edges[2].i1, edges[2].i2 );
        
        if (edges[2].line.oriented_side( c.c ) == ON_NEGATIVE_SIDE) volume3 = c.area - volume3;
    }
    
    edges[0].line = edges[0].line.opposite();
    edges[1].line = edges[1].line.opposite();
    edges[2].line = edges[2].line.opposite();
    
    volume4 = Irregular_Sector_Area( c, vertices[0], edges[0], edges[2], intersection_1, intersection_3);
    
    volume5 = Irregular_Sector_Area( c, vertices[1], edges[0], edges[1], intersection_1, intersection_2 );
    
    volume6 = Irregular_Sector_Area( c, vertices[2], edges[1], edges[2], intersection_2, intersection_3 );
    
    edges[0].line = edges[0].line.opposite();
    edges[1].line = edges[1].line.opposite();
    edges[2].line = edges[2].line.opposite();
    
    //cout << volume1 << endl;
    //cout << volume2 << endl;
    //cout << volume3 << endl;
    //cout << volume4 << endl;
    //cout << volume5 << endl;
    //cout << volume6 << endl;
    
    return c.area - volume1 - volume2 - volume3 + volume4 + volume5 + volume6;
}
