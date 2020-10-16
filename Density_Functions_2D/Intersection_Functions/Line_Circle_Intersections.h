#pragma once

#include "Circle.h"
#include "Edge.h"

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

int Line_Circle_Intersections ( Circle const& circle, Edge& e );
