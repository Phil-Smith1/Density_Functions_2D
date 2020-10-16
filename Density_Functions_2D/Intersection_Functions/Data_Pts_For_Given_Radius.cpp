#include "Input.h"
#include "Disk_Triangle_Intersection.h"

void Data_Pts_For_Given_Radius ( Input const input, int sample, P2 const base_pt, vector<vector<Tri>>const tris, vector<double>const max_radii, vector<double>& volume )
{
    double radius = volume[0];
    
    Circle c( base_pt, radius );
        
    for (int counter_1 = 0; counter_1 < input.zone_limit; ++counter_1)
    {
        if (max_radii[counter_1] < radius + tiny_num)
        {
            for (int counter_2 = 0; counter_2 < tris[counter_1].size(); ++counter_2)
            {
                volume[counter_1 + 1] += tris[counter_1][counter_2].area();
            }
        }
        
        else
        {
            for (int counter_2 = 0; counter_2 < tris[counter_1].size(); ++counter_2)
            {
                volume[counter_1 + 1] += Disk_Triangle_Intersection( c, tris[counter_1][counter_2], max_radii[counter_1] );
            }
        }
    }
}
