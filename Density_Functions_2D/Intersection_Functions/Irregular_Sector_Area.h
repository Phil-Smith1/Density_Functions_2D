#pragma once

#include "Edge.h"
#include "Segment_Area.h"
#include "Triangle_Area.h"

double Irregular_Sector_Area ( Circle const& c, P2 const& vertex, Edge const& e1, Edge const& e2, int intersection_1, int intersection_2 );
