#include "Input.h"
#include "Transformation_Matrix.h"
#include "Frac_To_Cart_Coords.h"

void Initialise_Pt_Cloud ( Input const& input, double ** matrix, bool uplusv, int iter, vector<P2>& base_pts )
{
    vector<pair<string, double>> cell_shape;
    cell_shape.reserve( 3 );

    cell_shape.push_back( pair<string, double>( "_cell_length_a", input.cell_param_a ) );
    cell_shape.push_back( pair<string, double>( "_cell_length_b", input.cell_param_b ) );
    cell_shape.push_back( pair<string, double>( "_cell_angle_gamma", input.cell_param_gamma ) );

    Transformation_Matrix( cell_shape, matrix );
    
    if (uplusv)
    {
        for (int counter_1 = 0; counter_1 < input.frac_base_pts.size(); ++counter_1)
        {
            for (int counter_2 = 0; counter_2 < input.frac_V.size(); ++counter_2)
            {
                double x,y;
                
                if (iter % 2 == 0)
                {
                    x = to_double( input.frac_base_pts[counter_1].x() + input.frac_V[counter_2].x() );
                    y = to_double( input.frac_base_pts[counter_1].y() + input.frac_V[counter_2].y() );
                }
                
                else
                {
                    x = to_double( input.frac_base_pts[counter_1].x() - input.frac_V[counter_2].x() );
                    y = to_double( input.frac_base_pts[counter_1].y() - input.frac_V[counter_2].y() );
                }
                
                while (x > 1) x -= 1;
                while (x < 0) x += 1;
                while (y > 1) y -= 1;
                while (y < 0) y += 1;
                
                P2 p = P2( x, y );
                
                base_pts.push_back( p );
            }
        }
    }
    
    else
    {
        for (int counter = 0; counter < input.frac_base_pts.size(); ++counter)
        {
            base_pts.push_back( input.frac_base_pts[counter] );
        }
        
        for (int counter = 0; counter < input.frac_random_pts.size(); ++counter)
        {
            base_pts.push_back( input.frac_random_pts[counter] );
        }
    }
    
    for (int counter = 0; counter < base_pts.size(); ++counter)
    {
        Frac_To_Cart_Coords( matrix, base_pts[counter] );
    }
}
