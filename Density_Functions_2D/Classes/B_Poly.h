#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>

using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef Polygon_2<K> Poly;

class B_Poly
{
    public:
    
    int zone;
    double dist;
    Poly poly;
    
    B_Poly ( Poly const& p, double d, int z );
    
    B_Poly();
    ~B_Poly();
};
