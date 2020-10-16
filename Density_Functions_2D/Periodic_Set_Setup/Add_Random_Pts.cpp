#include "Input.h"

void Add_Random_Pts ( Input& input )
{
    input.frac_random_pts.clear();
    
    for (int counter = 0; counter < input.random_pts; ++counter)
    {
        double x = (rand() % 10000) / (double)10000;
        double y = (rand() % 10000) / (double)10000;
        
        input.frac_random_pts.push_back( P2( x, y ) );
    }
}
