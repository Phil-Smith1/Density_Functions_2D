#include "Frac_To_Cart_Coords.h"

using namespace std;

typedef K::Vector_2 V2;

void Surrounding_Cloud ( int perim, double ** matrix, int index, vector<P2>const& base_pts, multimap<double, P2>& cloud )
{
    P2 p1 = P2( 1, 0 );
    P2 p2 = P2( 0, 1 );
    
    Frac_To_Cart_Coords( matrix, p1 );
    Frac_To_Cart_Coords( matrix, p2 );
    
    V2 v1 = V2( p1.x(), p1.y() );
    V2 v2 = V2( p2.x(), p2.y() );
    
    for (int counter_1 = -perim; counter_1 < perim + 1; ++counter_1)
    {
        for (int counter_2 = -perim; counter_2 < perim + 1; ++counter_2)
        {
            V2 v = counter_1 * v1 + counter_2 * v2;
            
            for (int counter_3 = 0; counter_3 < base_pts.size(); ++counter_3)
            {
                if (counter_1 == 0 && counter_2 == 0 && counter_3 == index) continue;
                
                P2 p = base_pts[counter_3] + v;
                
                double dist = squared_distance( base_pts[index], p );
                
                cloud.insert( pair<double, P2>( dist, p ) );
            }
        }
    }
}
