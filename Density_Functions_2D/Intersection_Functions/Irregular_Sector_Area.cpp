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
                    P2 intersect_1 = e1.i1;
                    
                    if (Norm( e1.i2, vertex ) > Norm( e1.i1, vertex )) intersect_1 = e1.i2;
                    
                    P2 intersect_2 = e2.i1;
                    
                    if (Norm( e2.i2, vertex ) > Norm( e2.i1, vertex )) intersect_2 = e2.i2;
                    
                    V2 v3 = intersect_1 - vertex;
                    V2 v4 = intersect_2 - vertex;
                    
                    v3 = v3 / (double)Norm( v3 );
                    v4 = v4 / (double)Norm( v4 );
                    
                    P2 midpoint = P2( vertex.x() + v3.x() + v4.x(), vertex.y() + v3.y() + v4.y() );
                    
                    double dist = Norm( midpoint, vertex );
                                     
                    double d1 = Norm( vertex + (v1 + v2) * 0.5 * dist / (double)Norm( v1 + v2 ), midpoint );
                    double d2 = Norm( vertex + (v1 - v2) * 0.5 * dist / (double)Norm( v1 - v2 ), midpoint );
                    double d3 = Norm( vertex - (v1 - v2) * 0.5 * dist / (double)Norm( v1 - v2 ), midpoint );
                    double d4 = Norm( vertex - (v1 + v2) * 0.5 * dist / (double)Norm( v1 + v2 ), midpoint );
                    
                    if (d1 >= d2 && d1 >= d3 && d1 >= d4) return vol1;
                    else if (d2 >= d3 && d2 >= d4) return vol1 + vol2 - c.area;
                    else if (d3 >= d4) return 0;
                    else return vol2;
                    
                    /*double d1 = Norm( vertex + (v1 + v2), c.c );
                    double d2 = Norm( vertex + (v1 - v2), c.c );
                    double d3 = Norm( vertex - (v1 - v2), c.c );
                    double d4 = Norm( vertex - (v1 + v2), c.c );
                     
                    if (d1 >= d2 && d1 >= d3 && d1 >= d4) return vol1;
                    else if (d2 >= d3 && d2 >= d4) return vol1 + vol2 - c.area;
                    else if (d3 >= d4) return 0;
                    else return vol2;*/
                }
                
                else if (e2.line.oriented_side( vertex + v1 ) == ON_POSITIVE_SIDE)
                {
                    P2 intersect_1 = e1.i1;
                    
                    if (Norm( e1.i2, vertex ) > Norm( e1.i1, vertex )) intersect_1 = e1.i2;
                    
                    P2 intersect_2 = e2.i1;
                    
                    if (Norm( e2.i2, vertex ) > Norm( e2.i1, vertex )) intersect_2 = e2.i2;
                    
                    V2 v3 = intersect_1 - vertex;
                    V2 v4 = intersect_2 - vertex;
                    
                    v3 = v3 / (double)Norm( v3 );
                    v4 = v4 / (double)Norm( v4 );
                    
                    P2 midpoint = P2( vertex.x() + v3.x() + v4.x(), vertex.y() + v3.y() + v4.y() );
                    
                    double dist = Norm( midpoint, vertex );
                                     
                    double d1 = Norm( vertex + (v1 + v2) * 0.5 * dist / (double)Norm( v1 + v2 ), midpoint );
                    double d2 = Norm( vertex + (v1 - v2) * 0.5 * dist / (double)Norm( v1 - v2 ), midpoint );
                    double d3 = Norm( vertex - (v1 - v2) * 0.5 * dist / (double)Norm( v1 - v2 ), midpoint );
                    double d4 = Norm( vertex - (v1 + v2) * 0.5 * dist / (double)Norm( v1 + v2 ), midpoint );
                    
                    if (d1 >= d2 && d1 >= d3 && d1 >= d4) return vol2;
                    else if (d2 >= d3 && d2 >= d4) return 0;
                    else if (d3 >= d4) return vol1 + vol2 - c.area;
                    else return vol1;
                    
                    /*double d1 = Norm( vertex + (v1 + v2), c.c );
                    double d2 = Norm( vertex + (v1 - v2), c.c );
                    double d3 = Norm( vertex - (v1 - v2), c.c );
                    double d4 = Norm( vertex - (v1 + v2), c.c );
                     
                    if (d1 >= d2 && d1 >= d3 && d1 >= d4) return vol2;
                    else if (d2 >= d3 && d2 >= d4) return 0;
                    else if (d3 >= d4) return vol1 + vol2 - c.area;
                    else return vol1;*/
                    
                    /*if (abs( d1 - d4) > abs( d2 - d3 ))
                    {
                        if (d1 > d4) return vol2;
                        else return vol1;
                    }
                    
                    else if (d2 > d3) return 0;
                    else return vol1 + vol2 - c.area;*/
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
                    /*double d1 = Norm( vertex + (v1 + v2), c.c );
                    double d2 = Norm( vertex + (v1 - v2), c.c );
                    double d3 = Norm( vertex - (v1 - v2), c.c );
                    double d4 = Norm( vertex - (v1 + v2), c.c );
                     
                    if (d1 >= d2 && d1 >= d3 && d1 >= d4) return vol1;
                    else if (d2 >= d3 && d2 >= d4) return vol1 + vol2 - c.area;
                    else if (d3 >= d4) return 0;
                    else return vol2;*/
                    
                    P2 intersect_1 = e1.i1;
                    
                    if (Norm( e1.i2, vertex ) > Norm( e1.i1, vertex )) intersect_1 = e1.i2;
                    
                    P2 intersect_2 = e2.i1;
                    
                    if (Norm( e2.i2, vertex ) > Norm( e2.i1, vertex )) intersect_2 = e2.i2;
                    
                    V2 v3 = intersect_1 - vertex;
                    V2 v4 = intersect_2 - vertex;
                    
                    //cout << v3 << endl;
                    //cout << v4 << endl;
                    
                    v3 = v3 / (double)Norm( v3 );
                    v4 = v4 / (double)Norm( v4 );
                    
                    //cout << v3 << endl;
                    //cout << v4 << endl;
                    //cout << intersect_1 << endl;
                    //cout << intersect_2 << endl;
                    //cout << vertex << endl;
                    
                    P2 midpoint = P2( vertex.x() + v3.x() + v4.x(), vertex.y() + v3.y() + v4.y() );
                    
                    //cout << midpoint << endl;
                    
                    double dist = Norm( midpoint, vertex );
                    
                    //cout << dist << endl;
                                     
                    double d1 = Norm( vertex + (v1 + v2) * 0.5 * dist / (double)Norm( v1 + v2 ), midpoint );
                    double d2 = Norm( vertex + (v1 - v2) * 0.5 * dist / (double)Norm( v1 - v2 ), midpoint );
                    double d3 = Norm( vertex - (v1 - v2) * 0.5 * dist / (double)Norm( v1 - v2 ), midpoint );
                    double d4 = Norm( vertex - (v1 + v2) * 0.5 * dist / (double)Norm( v1 + v2 ), midpoint );
                    
                    if (d1 >= d2 && d1 >= d3 && d1 >= d4) return vol1;
                    else if (d2 >= d3 && d2 >= d4) return vol1 + vol2 - c.area;
                    else if (d3 >= d4) return 0;
                    else return vol2;
                }
                
                else if (e2.line.oriented_side( vertex + v1 ) == ON_POSITIVE_SIDE)
                {
                    /*double d1 = Norm( vertex + (v1 + v2), c.c );
                    double d2 = Norm( vertex + (v1 - v2), c.c );
                    double d3 = Norm( vertex - (v1 - v2), c.c );
                    double d4 = Norm( vertex - (v1 + v2), c.c );
                     
                    if (d1 >= d2 && d1 >= d3 && d1 >= d4) return vol2;
                    else if (d2 >= d3 && d2 >= d4) return 0;
                    else if (d3 >= d4) return vol1 + vol2 - c.area;
                    else return vol1;*/
                    
                    P2 intersect_1 = e1.i1;
                    
                    if (Norm( e1.i2, vertex ) > Norm( e1.i1, vertex )) intersect_1 = e1.i2;
                    
                    P2 intersect_2 = e2.i1;
                    
                    if (Norm( e2.i2, vertex ) > Norm( e2.i1, vertex )) intersect_2 = e2.i2;
                    
                    V2 v3 = intersect_1 - vertex;
                    V2 v4 = intersect_2 - vertex;
                    
                    v3 = v3 / (double)Norm( v3 );
                    v4 = v4 / (double)Norm( v4 );
                    
                    P2 midpoint = P2( vertex.x() + v3.x() + v4.x(), vertex.y() + v3.y() + v4.y() );
                    
                    double dist = Norm( midpoint, vertex );
                                     
                    double d1 = Norm( vertex + (v1 + v2) * 0.5 * dist / (double)Norm( v1 + v2 ), midpoint );
                    double d2 = Norm( vertex + (v1 - v2) * 0.5 * dist / (double)Norm( v1 - v2 ), midpoint );
                    double d3 = Norm( vertex - (v1 - v2) * 0.5 * dist / (double)Norm( v1 - v2 ), midpoint );
                    double d4 = Norm( vertex - (v1 + v2) * 0.5 * dist / (double)Norm( v1 + v2 ), midpoint );
                    
                    if (d1 >= d2 && d1 >= d3 && d1 >= d4) return vol2;
                    else if (d2 >= d3 && d2 >= d4) return 0;
                    else if (d3 >= d4) return vol1 + vol2 - c.area;
                    else return vol1;
                    
                    /*double d1 = Norm( vertex + (v1 + v2) * 0.1 * c.r / (double)Norm( v1 + v2 ), c.c );
                    double d2 = Norm( vertex + (v1 - v2) * 0.1 * c.r / (double)Norm( v1 - v2 ), c.c );
                    double d3 = Norm( vertex - (v1 - v2) * 0.1 * c.r / (double)Norm( v1 - v2 ), c.c );
                    double d4 = Norm( vertex - (v1 + v2) * 0.1 * c.r / (double)Norm( v1 + v2 ), c.c );
                    
                    if (abs( d1 - d4) > abs( d2 - d3 ))
                    {
                        if (d1 > d4) return vol2;
                        else return vol1;
                    }
                    
                    else if (d2 > d3) return 0;
                    else return vol1 + vol2 - c.area;*/
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
                    double vol2 = Segment_Area( c, e2.i1, e2.i2 );
                    
                    if (e2.line.oriented_side( c.c ) == ON_POSITIVE_SIDE) return c.area - vol2;
                    
                    else return vol2;
                }
            }
            
            else return 0;
        }
        
        else
        {
            double vol1 = Segment_Area( c, e1.i1, e1.i2 );
            
            if (e1.line.oriented_side( c.c ) == ON_POSITIVE_SIDE) vol1 = c.area - vol1;
            
            if (intersection_2 == 1 || intersection_2 == 0)
            {
                if (e2.line.oriented_side( c.c ) == ON_POSITIVE_SIDE) return vol1;
                
                else return 0;
            }
            
            P2 intersection1 = e1.i1;
            
            //cout << e1.line.oriented_side(e2.i1) << endl;
            //cout << e1.line.oriented_side(e2.i2) << endl;
            //cout << squared_distance( e2.i1, e1.line) << endl;
            //cout << squared_distance( e2.i2, e1.line) << endl;
            //cout << e2.i1 << endl;
            //cout << e2.i2 << endl;
            
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
            
            //cout << intersection_1 << endl;
            //cout << intersection_2 << endl;
            //cout << vertex << endl;
            //cout << triangle_area << endl;
            //cout << segment_area << endl;
            //cout << triangle_area - segment_area + c.area << endl;
            
            //cout << Norm( intersection1, c.c ) - c.r << endl;
            //cout << Norm( intersection2, c.c ) - c.r << endl;
            //cout << triangle_area + segment_area << endl;
            
            L2 l( intersection1, intersection2 );
            
            //cout << l.oriented_side( c.c ) << " " << squared_distance( c.c, l ) << endl;
            //cout << l.oriented_side( vertex ) << " " << squared_distance( vertex, l ) << endl;
            //cout << e1.line.oriented_side( c.c ) << " " << squared_distance( c.c, e1.line ) << endl;
            //cout << e2.line.oriented_side( c.c ) << " " << squared_distance( c.c, e2.line ) << endl;
            
            if (e1.line.oriented_side( c.c ) == ON_POSITIVE_SIDE && e2.line.oriented_side( c.c ) == ON_POSITIVE_SIDE)
            {
                if (l.oriented_side( c.c ) == l.oriented_side( vertex ) && squared_distance( c.c, l ) < squared_distance( vertex, l )) return triangle_area + segment_area;
                
                else return triangle_area + c.area - segment_area;
            }
            
            else return triangle_area + segment_area;
            
            /*if (l.oriented_side( c.c ) == l.oriented_side( vertex )) return triangle_area + segment_area;
            
            if (e1.line.oriented_side( c.c ) != ON_POSITIVE_SIDE || e2.line.oriented_side( c.c ) != ON_POSITIVE_SIDE) return triangle_area + segment_area;
            
            else return triangle_area + c.area - segment_area;*/
        }
    }
}
