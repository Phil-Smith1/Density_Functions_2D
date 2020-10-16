#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>

using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P2;
typedef Polygon_2<K> Poly;
typedef Poly::Vertex_iterator vertex_iterator;

double Max_Distance_To_Polygon ( P2 const& base_pt, Poly& poly );
