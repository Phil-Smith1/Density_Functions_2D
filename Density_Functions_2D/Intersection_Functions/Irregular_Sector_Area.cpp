#include "Edge.h"
#include "Segment_Area.h"
#include "Triangle_Area.h"

using namespace std;

double Irregular_Sector_Area ( Circle const& c, P2 const& vertex, Edge const& e1, Edge const& e2, int intersection_1, int intersection_2 )
{
    if (abs( Norm( vertex, c.c ) - c.r ) < tiny_num)
    {
        double vol1 = 0, vol2 = 0;
        
        if (intersection_1 == 1 || intersection_1 == 0)
        {
            if (e1.line.oriented_side( c.c ) == ON_POSITIVE_SIDE)
            {
                if (intersection_2 == 1 || intersection_2 == 0)
                {
                    if (e2.line.oriented_side( c.c ) == ON_POSITIVE_SIDE) return c.area;
                    
                    else return 0;
                }
                
                else
                {
                    vol2 = Segment_Area( c, e2.i1, e2.i2 );
                    
                    if (e2.line.oriented_side( c.c ) == ON_POSITIVE_SIDE) return c.area - vol2;
                    
                    else return vol2;
                }
            }
            
            else return 0;
        }
        
        else
        {
            vol1 = Segment_Area( c, e1.i1, e1.i2 );
            
            if (e1.line.oriented_side( c.c ) == ON_POSITIVE_SIDE) vol1 = c.area - vol1;
            
            if (intersection_2 == 1 || intersection_2 == 0)
            {
                if (e2.line.oriented_side( c.c ) == ON_POSITIVE_SIDE) return vol1;
                
                else return 0;
            }
            
            else
            {
                vol2 = Segment_Area( c, e2.i1, e2.i2 );
                
                if (e2.line.oriented_side( c.c ) == ON_POSITIVE_SIDE) vol2 = c.area - vol2;
                
                V2 v1 = e1.line.to_vector() / Norm( e1.line.to_vector() );
                V2 v2 = e2.line.to_vector() / Norm( e2.line.to_vector() );
                
                if (e1.line.oriented_side( vertex + v2 ) == ON_POSITIVE_SIDE)
                {
                    double d1 = Norm( vertex + v1 + v2, c.c );
                    double d2 = Norm( vertex + v1 - v2, c.c );
                    double d3 = Norm( vertex - v1 + v2, c.c );
                    double d4 = Norm( vertex - v1 - v2, c.c );
                    
                    if (d1 >= d2 && d1 >= d3 && d1 >= d4) return vol1;
                    else if (d2 >= d3 && d2 >= d4) return vol1 + vol2 - c.area;
                    else if (d3 >= d4) return 0;
                    else return vol2;
                }
                
                else if (e2.line.oriented_side( vertex + v1 ) == ON_POSITIVE_SIDE)
                {
                    double d1 = Norm( vertex + v1 + v2, c.c );
                    double d2 = Norm( vertex + v1 - v2, c.c );
                    double d3 = Norm( vertex - v1 + v2, c.c );
                    double d4 = Norm( vertex - v1 - v2, c.c );
                    
                    if (d1 >= d2 && d1 >= d3 && d1 >= d4) return vol2;
                    else if (d2 >= d3 && d2 >= d4) return 0;
                    else if (d3 >= d4) return vol1 + vol2 - c.area;
                    else return vol1;
                }
                
                if (((e1.line.oriented_side( e2.i1 ) == ON_NEGATIVE_SIDE && Norm( e2.i1, vertex ) > 1e-8) || (e1.line.oriented_side( e2.i2 ) == ON_NEGATIVE_SIDE && Norm( e2.i2, vertex ) > 1e-8)) && ((e2.line.oriented_side( e1.i1 ) == ON_NEGATIVE_SIDE && Norm( e1.i1, vertex ) > 1e-8) || (e2.line.oriented_side( e1.i2 ) == ON_NEGATIVE_SIDE && Norm( e1.i2, vertex ) > 1e-8))) return 0;
                
                else if (((e1.line.oriented_side( e2.i1 ) == ON_NEGATIVE_SIDE && Norm( e2.i1, vertex ) > 1e-8) || (e1.line.oriented_side( e2.i2 ) == ON_NEGATIVE_SIDE && Norm( e2.i2, vertex ) > 1e-8)) || ((e2.line.oriented_side( e1.i1 ) == ON_NEGATIVE_SIDE && Norm( e1.i1, vertex ) > 1e-8) || (e2.line.oriented_side( e1.i2 ) == ON_NEGATIVE_SIDE && Norm( e1.i2, vertex ) > 1e-8)))
                {
                    if ((e1.line.oriented_side( e2.i1 ) == ON_NEGATIVE_SIDE && Norm( e2.i1, vertex ) > 1e-8) || (e1.line.oriented_side( e2.i2 ) == ON_NEGATIVE_SIDE && Norm( e2.i2, vertex ) > 1e-8)) return vol1;
                    
                    else return vol2;
                }
                
                else return vol1 + vol2 - c.area;
            }
        }
    }
    
    else if (Norm( vertex, c.c ) > c.r)
    {
        double vol1 = 0, vol2 = 0;
        
        if (intersection_1 == 1 || intersection_1 == 0)
        {
            if (e1.line.oriented_side( c.c ) == ON_POSITIVE_SIDE)
            {
                if (intersection_2 == 1 || intersection_2 == 0)
                {
                    if (e2.line.oriented_side( c.c ) == ON_POSITIVE_SIDE) return c.area;
                    
                    else return 0;
                }
                
                else
                {
                    vol2 = Segment_Area( c, e2.i1, e2.i2 );
                    
                    if (e2.line.oriented_side( c.c ) == ON_POSITIVE_SIDE) return c.area - vol2;
                    
                    else return vol2;
                }
            }
            
            else return 0;
        }
        
        else
        {
            vol1 = Segment_Area( c, e1.i1, e1.i2 );
            
            if (e1.line.oriented_side( c.c ) == ON_POSITIVE_SIDE) vol1 = c.area - vol1;
            
            if (intersection_2 == 1 || intersection_2 == 0)
            {
                if (e2.line.oriented_side( c.c ) == ON_POSITIVE_SIDE) return vol1;
                
                else return 0;
            }
            
            else
            {
                vol2 = Segment_Area( c, e2.i1, e2.i2 );
                
                if (e2.line.oriented_side( c.c ) == ON_POSITIVE_SIDE) vol2 = c.area - vol2;
                
                V2 v1 = e1.line.to_vector() / Norm( e1.line.to_vector() );
                V2 v2 = e2.line.to_vector() / Norm( e2.line.to_vector() );
                
                if (e1.line.oriented_side( vertex + v2 ) == ON_POSITIVE_SIDE)
                {
                    double d1 = Norm( vertex + v1 + v2, c.c );
                    double d2 = Norm( vertex + v1 - v2, c.c );
                    double d3 = Norm( vertex - v1 + v2, c.c );
                    double d4 = Norm( vertex - v1 - v2, c.c );
                    
                    if (d1 >= d2 && d1 >= d3 && d1 >= d4) return vol1;
                    else if (d2 >= d3 && d2 >= d4) return vol1 + vol2 - c.area;
                    else if (d3 >= d4) return 0;
                    else return vol2;
                }
                
                else if (e2.line.oriented_side( vertex + v1 ) == ON_POSITIVE_SIDE)
                {
                    double d1 = Norm( vertex + v1 + v2, c.c );
                    double d2 = Norm( vertex + v1 - v2, c.c );
                    double d3 = Norm( vertex - v1 + v2, c.c );
                    double d4 = Norm( vertex - v1 - v2, c.c );
                    
                    if (d1 >= d2 && d1 >= d3 && d1 >= d4) return vol2;
                    else if (d2 >= d3 && d2 >= d4) return 0;
                    else if (d3 >= d4) return vol1 + vol2 - c.area;
                    else return vol1;
                }
                
                if (e1.line.oriented_side( e2.i1 ) == ON_NEGATIVE_SIDE && e2.line.oriented_side( e1.i1 ) == ON_NEGATIVE_SIDE) return 0;
                
                else if (e1.line.oriented_side( e2.i1 ) == ON_NEGATIVE_SIDE || e2.line.oriented_side( e1.i1 ) == ON_NEGATIVE_SIDE)
                {
                    if (e1.line.oriented_side( e2.i1 ) == ON_NEGATIVE_SIDE) return vol1;
                    
                    else return vol2;
                }
                
                else return vol1 + vol2 - c.area;
            }
        }
    }
    
    else
    {
        P2 intersection1 = e1.i1;
        
        if (e2.line.oriented_side( e1.i1 ) == ON_POSITIVE_SIDE && e2.line.oriented_side( e1.i2 ) == ON_POSITIVE_SIDE)
        {
            if (squared_distance( e1.i1, e2.line) < squared_distance( e1.i2, e2.line)) intersection1 = e1.i2;
        }
        
        else
        {
            if (e2.line.oriented_side( intersection1 ) == ON_NEGATIVE_SIDE) intersection1 = e1.i2;
            
            if (e2.line.oriented_side( intersection1 ) == ON_NEGATIVE_SIDE)
            {
                if (squared_distance( e1.i1, e2.line) < squared_distance( e1.i2, e2.line)) intersection1 = e1.i1;
            }
        }
        
        P2 intersection2 = e2.i1;
        
        if (e1.line.oriented_side( e2.i1 ) == ON_POSITIVE_SIDE && e1.line.oriented_side( e2.i2 ) == ON_POSITIVE_SIDE)
        {
            if (squared_distance( e2.i1, e1.line) < squared_distance( e2.i2, e1.line)) intersection2 = e2.i2;
        }
        
        else
        {
            if (e1.line.oriented_side( intersection2 ) == ON_NEGATIVE_SIDE) intersection2 = e2.i2;
            
            if (e1.line.oriented_side( intersection2 ) == ON_NEGATIVE_SIDE)
            {
                if (squared_distance( e2.i1, e1.line) < squared_distance( e2.i2, e1.line)) intersection2 = e2.i1;
            }
        }
        
        double triangle_area = Triangle_Area( vertex, intersection1, intersection2 );
        double segment_area = Segment_Area( c, intersection1, intersection2 );
        
        L2 l( intersection1, intersection2 );
        
        if (l.oriented_side( c.c ) == l.oriented_side( vertex )) return triangle_area + segment_area;
        
        if (e1.line.oriented_side( c.c ) != ON_POSITIVE_SIDE || e2.line.oriented_side( c.c ) != ON_POSITIVE_SIDE) return triangle_area + segment_area;
        
        else return triangle_area + c.area - segment_area;
    }
}
