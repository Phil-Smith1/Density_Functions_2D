#include "Input.h"

typedef K::Vector_2 V2;

void Surrounding_Cloud ( Input const& input, int index, multimap<double, P2>& cloud )
{
    V2 v1 = input.lattice_vectors[0] - ORIGIN;
    V2 v2 = input.lattice_vectors[1] - ORIGIN;
    
    for (int counter_1 = -input.perim; counter_1 < input.perim + 1; ++counter_1)
    {
        for (int counter_2 = -input.perim; counter_2 < input.perim + 1; ++counter_2)
        {
            V2 v = counter_1 * v1 + counter_2 * v2;
            
            for (int counter_3 = 0; counter_3 < input.base_pts.size(); ++counter_3)
            {
                if (counter_1 == 0 && counter_2 == 0 && counter_3 == index) continue;
                
                P2 p = input.base_pts[counter_3] + v;
                
                double dist = squared_distance( input.base_pts[index], p );
                
                cloud.insert( pair<double, P2>( dist, p ) );
            }
        }
    }
}
