#include "Input.h"
#include "Transformation_Matrix.h"
#include "Frac_To_Cart_Coords.h"

void Initialise_Lattice ( Input& input )
{
    vector<pair<string, double>> cell_shape;
    cell_shape.reserve( 3 );

    cell_shape.push_back( pair<string, double>( "_cell_length_a", input.cell_param_a ) );
    cell_shape.push_back( pair<string, double>( "_cell_length_b", input.cell_param_b ) );
    cell_shape.push_back( pair<string, double>( "_cell_angle_gamma", input.cell_param_gamma ) );
    
    input.matrix = new double *[2];
    input.matrix[0] = new double [2];
    input.matrix[1] = new double [2];

    Transformation_Matrix( cell_shape, input.matrix );
    
    P2 p1 = P2( 1, 0 );
    P2 p2 = P2( 0, 1 );
    
    Frac_To_Cart_Coords( input.matrix, p1 );
    Frac_To_Cart_Coords( input.matrix, p2 );
    
    input.lattice_vectors.push_back( p1 );
    input.lattice_vectors.push_back( p2 );
}
