#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P2;

void Frac_To_Cart_Coords ( double ** matrix, P2& p )
{
    double cart_coords_x = matrix[0][0] * p.x() + matrix[0][1] * p.y();
    double cart_coords_y = matrix[1][0] * p.x() + matrix[1][1] * p.y();
    
    p = P2( cart_coords_x, cart_coords_y );
}
