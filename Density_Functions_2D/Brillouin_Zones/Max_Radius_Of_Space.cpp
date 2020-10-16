#include "B_Poly.h"

using namespace std;

double Max_Radius_Of_Space ( vector<B_Poly>const& polys )
{
    double max_radius = 0;
    
    for (int counter = 0; counter < polys.size(); ++counter)
    {
        if (polys[counter].dist > max_radius) max_radius = polys[counter].dist;
    }
    
    return max_radius;
}
