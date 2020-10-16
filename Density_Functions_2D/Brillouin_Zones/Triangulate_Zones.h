#pragma once

#include <CGAL/Triangle_2.h>
#include <CGAL/Triangulation_2.h>

#include "B_Poly.h"

using namespace std;

typedef K::Point_2 P2;
typedef Triangle_2<K> Tri;
typedef Triangulation_2<K> Triangulation;
typedef Poly::Vertex_iterator vertex_iterator;
typedef Triangulation::Finite_faces_iterator faces_iterator;

void Triangulate_Zones ( vector<B_Poly>& polys, int zone_limit, vector<vector<Tri>>& tris, vector<double>& cell_volume );
