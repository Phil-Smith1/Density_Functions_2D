#include "Max_Distance_To_Polygon.h"
#include "Removing_Polygons.h"
#include "Line_Intersect_Polygon.h"
#include "Max_Radius_Of_Space.h"

#include <mutex>

#include <CGAL/convex_hull_2.h>

typedef K::Segment_2 S2;
typedef K::Intersect_2 I2;
typedef Poly::Edge_const_iterator edge_iterator;

void Divide_Polygon ( multimap<double, P2>const cloud, P2 const base_pt, int zone_limit, Poly poly, int starting_zone, vector<B_Poly>& final_polys )
{
    vector<B_Poly> polys;
    polys.push_back( B_Poly( poly, Max_Distance_To_Polygon( base_pt, poly ), starting_zone ) );
    
    double max_radius = 1e10;
    double line_distance = 0;
    
    vector<L2> lines;
    lines.reserve( (int)cloud.size() );
    
    double precision = 1e12;
    
    bool remove_polys = false;
    
    for (auto iter = cloud.begin(); iter != cloud.end(); ++iter)
    {
        L2 line = bisector( base_pt, (*iter).second );
        
        long double a = (long long int)(line.a() * precision + 0.5);
        long double b = (long long int)(line.b() * precision + 0.5);
        long double c = (long long int)(line.c() * precision + 0.5);
        
        a = a / (long double)precision;
        b = b / (long double)precision;
        c = c / (long double)precision;
        
        line = L2( a, b, c );
        
        line_distance = sqrt( squared_distance( base_pt, line ) );
                
        if (max_radius < line_distance + tiny_num) break;
        
        {
            mutex m1;
            
            lock_guard<mutex> lock_guard( m1 );
            
            if (remove_polys) Removing_Polygons( base_pt, line_distance, polys, final_polys, zone_limit );
        }
        
        if (line.oriented_side( base_pt ) == ON_NEGATIVE_SIDE) line = line.opposite();
        
        lines.push_back( line );
        
        if ((int)polys.size() == 0) break;
        
        int intersect = Line_Intersect_Polygon( poly, line );
        
        if (intersect == -1)
        {
            for (int counter = 0; counter < polys.size(); ++counter)
            {
                polys[counter].zone += 1;
            }
            
            remove_polys = true;
            
            continue;
        }
        
        else if (intersect == 1)
        {
            remove_polys = false;
            continue;
        }
        
        else
        {
            remove_polys = true;
            
            vector<B_Poly> new_polys;
            new_polys.reserve( (int)polys.size() );
            
            for (int counter_1 = 0; counter_1 < polys.size(); ++counter_1)
            {
                vector<P2> pos_pts;
                vector<P2> neg_pts;
                vector<P2> bdry_pts;
                
                for (vertex_iterator v = polys[counter_1].poly.vertices_begin(); v != polys[counter_1].poly.vertices_end(); ++v)
                {
                    P2 p = P2( v->x(), v->y() );
                    
                    if (squared_distance( p, line ) < tiny_num) bdry_pts.push_back( p );
                    
                    else if (line.oriented_side( p ) == ON_POSITIVE_SIDE) pos_pts.push_back( p );
                    
                    else neg_pts.push_back( p );
                }
                
                // Change: Now 1e-8 in next two lines. Was 1e-3. Reason: When drawing Brillouin zones, was missing tiny triangles, can now see them.
                
                if ((int)neg_pts.size() == 1 && squared_distance( neg_pts[0], line ) < 1e-8) continue;
                
                else if ((int)pos_pts.size() == 1 && squared_distance( pos_pts[0], line ) < 1e-8)
                {
                    ++polys[counter_1].zone;
                    continue;
                }
                
                else if ((int)neg_pts.size() == 0 || (int)pos_pts.size() == 0)
                {
                    if ((int)pos_pts.size() == 0) ++polys[counter_1].zone;
                    continue;
                }
                
                else
                {
                    vector<S2> segs;
                    
                    for (edge_iterator h = polys[counter_1].poly.edges_begin(); h != polys[counter_1].poly.edges_end(); ++h)
                    {
                        P2 p1 = h->source();
                        P2 p2 = h->target();
                        
                        long double x = (long long int)(p1.x() * precision + 0.5);
                        long double y = (long long int)(p1.y() * precision + 0.5);
                        
                        x = x / (long double)precision;
                        y = y / (long double)precision;
                        
                        p1 = P2( x, y );
                        
                        x = (long long int)(p2.x() * precision + 0.5);
                        y = (long long int)(p2.y() * precision + 0.5);
                        
                        x = x / (long double)precision;
                        y = y / (long double)precision;
                        
                        p2 = P2( x, y );
                        
                        segs.push_back( S2( p1, p2 ) );
                    }
                    
                    vector<P2> pts;
                    
                    for (int counter_2 = 0; counter_2 < segs.size(); ++counter_2)
                    {
                        if (CGAL::do_intersect( line, segs[counter_2] ))
                        {
                            cpp11::result_of<I2(L2, L2)>::type result = intersection( line, L2( segs[counter_2].source(), segs[counter_2].target() ) );
                            
                            if (result)
                            {
                                if (const P2 * p = boost::get<P2>( &*result ))
                                {
                                    if (squared_distance( *p, segs[counter_2].source() ) > tiny_num && squared_distance( *p, segs[counter_2].target() ) > tiny_num)
                                    {
                                        P2 pt = *p;
                                        
                                        long double x = (long long int)(pt.x() * precision + 0.5);
                                        long double y = (long long int)(pt.y() * precision + 0.5);
                                        
                                        x = x / (long double)precision;
                                        y = y / (long double)precision;
                                        
                                        pt = P2( x, y );
                                        
                                        pts.push_back( pt );
                                    }
                                }
                            }
                            
                            else cout << "Wrong!" << endl;
                        }
                    }
                    
                    pos_pts.insert( pos_pts.end(), pts.begin(), pts.end() );
                    pos_pts.insert( pos_pts.end(), bdry_pts.begin(), bdry_pts.end() );
                    neg_pts.insert( neg_pts.end(), pts.begin(), pts.end() );
                    neg_pts.insert( neg_pts.end(), bdry_pts.begin(), bdry_pts.end() );
                    
                    Poly pos_poly, neg_poly;
                    
                    vector<P2> results;
                    
                    convex_hull_2( pos_pts.begin(), pos_pts.end(), back_inserter( results ) );
                    
                    pos_poly = Poly( results.begin(), results.end() );
                    
                    results.clear();
                    
                    double dist_pos_poly = Max_Distance_To_Polygon( base_pt, pos_poly );
                    
                    polys[counter_1].poly = pos_poly;
                    polys[counter_1].dist = dist_pos_poly;
                    
                    if (polys[counter_1].zone + 1 <= zone_limit)
                    {
                        convex_hull_2( neg_pts.begin(), neg_pts.end(), back_inserter( results ) );
                        
                        neg_poly = Poly( results.begin(), results.end() );
                        
                        double dist_neg_poly = Max_Distance_To_Polygon( base_pt, neg_poly );
                        
                        new_polys.push_back( B_Poly( neg_poly, dist_neg_poly, polys[counter_1].zone + 1 ) );
                    }
                }
            }
            
            polys.insert( polys.end(), new_polys.begin(), new_polys.end() );
        }
        
        max_radius = Max_Radius_Of_Space( polys );
    }
    
    {
        mutex m1;
        
        lock_guard<mutex> lock_guard( m1 );
        
        Removing_Polygons( base_pt, line_distance, polys, final_polys, zone_limit );
        
        final_polys.insert( final_polys.end(), polys.begin(), polys.end() );
    }
}
