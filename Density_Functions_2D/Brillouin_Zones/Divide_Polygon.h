#pragma once

#include "Max_Distance_To_Polygon.h"
#include "Removing_Polygons.h"
#include "Line_Intersect_Polygon.h"
#include "Max_Radius_Of_Space.h"

#include <mutex>

#include <CGAL/convex_hull_2.h>

typedef K::Segment_2 S2;
typedef K::Intersect_2 I2;
typedef Poly::Edge_const_iterator edge_iterator;

void Divide_Polygon ( multimap<double, P2>const cloud, P2 const base_pt, int zone_limit, Poly poly, int starting_zone, vector<B_Poly>& final_polys );
