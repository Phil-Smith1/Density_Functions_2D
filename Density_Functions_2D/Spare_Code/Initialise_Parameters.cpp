/*#include "Input.h"

#include <cmath>
#include <fstream>
#include <sstream>

void Initialise_Parameters( Input& input )
{
    if (input.hyperuniformity)
    {
        input.cell_param_a = 100;
        input.cell_param_b = 100;
        input.cell_param_gamma = 90;
        
        string hyper_file = "/Users/philsmith/Documents/Work/Hyperuniformity/Poisson-pp/2D-Poi-1-step-0.xyz";
        string line_data;
        
        ifstream ifs( hyper_file );
        
        getline( ifs, line_data );
        getline( ifs, line_data );
        
        while(getline( ifs, line_data ))
        {
            double x, y;
            string P;
            stringstream stream;
            
            stream << line_data;
            
            stream >> P >> x >> y;
            
            P2 pt = P2( x / (double)100, y / (double)100 );
            
            input.frac_base_pts.push_back( pt );
        }
    }
    
    else if (input.superhomo)
    {
        input.cell_param_a = 32;
        input.cell_param_b = 1;
        input.cell_param_gamma = 90;
        
        if (input.set_type == "a")
        {
            input.frac_base_pts.push_back( P2( 0 / (double)32, 0 ) );
            input.frac_base_pts.push_back( P2( 7 / (double)32, 0 ) );
            input.frac_base_pts.push_back( P2( 8 / (double)32, 0 ) );
            input.frac_base_pts.push_back( P2( 9 / (double)32, 0 ) );
            input.frac_base_pts.push_back( P2( 12 / (double)32, 0 ) );
            input.frac_base_pts.push_back( P2( 15 / (double)32, 0 ) );
            input.frac_base_pts.push_back( P2( 17 / (double)32, 0 ) );
            input.frac_base_pts.push_back( P2( 18 / (double)32, 0 ) );
            input.frac_base_pts.push_back( P2( 19 / (double)32, 0 ) );
            input.frac_base_pts.push_back( P2( 20 / (double)32, 0 ) );
            input.frac_base_pts.push_back( P2( 21 / (double)32, 0 ) );
            input.frac_base_pts.push_back( P2( 22 / (double)32, 0 ) );
            input.frac_base_pts.push_back( P2( 26 / (double)32, 0 ) );
            input.frac_base_pts.push_back( P2( 27 / (double)32, 0 ) );
            input.frac_base_pts.push_back( P2( 29 / (double)32, 0 ) );
            input.frac_base_pts.push_back( P2( 30 / (double)32, 0 ) );
        }
        
        else if (input.set_type == "b")
        {
            input.frac_base_pts.push_back( P2( 0 / (double)32, 0 ) );
            input.frac_base_pts.push_back( P2( 1 / (double)32, 0 ) );
            input.frac_base_pts.push_back( P2( 8 / (double)32, 0 ) );
            input.frac_base_pts.push_back( P2( 9 / (double)32, 0 ) );
            input.frac_base_pts.push_back( P2( 10 / (double)32, 0 ) );
            input.frac_base_pts.push_back( P2( 12 / (double)32, 0 ) );
            input.frac_base_pts.push_back( P2( 13 / (double)32, 0 ) );
            input.frac_base_pts.push_back( P2( 15 / (double)32, 0 ) );
            input.frac_base_pts.push_back( P2( 18 / (double)32, 0 ) );
            input.frac_base_pts.push_back( P2( 19 / (double)32, 0 ) );
            input.frac_base_pts.push_back( P2( 20 / (double)32, 0 ) );
            input.frac_base_pts.push_back( P2( 21 / (double)32, 0 ) );
            input.frac_base_pts.push_back( P2( 22 / (double)32, 0 ) );
            input.frac_base_pts.push_back( P2( 23 / (double)32, 0 ) );
            input.frac_base_pts.push_back( P2( 27 / (double)32, 0 ) );
            input.frac_base_pts.push_back( P2( 30 / (double)32, 0 ) );
        }
    }
}*/
