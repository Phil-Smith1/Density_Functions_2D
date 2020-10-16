#pragma once

#include "Intersection_Area.h"

#include <CGAL/Triangle_2.h>

typedef K::Triangle_2 Tri;

double Disk_Triangle_Intersection ( Circle const& c, Tri const& t, double max_dist );
