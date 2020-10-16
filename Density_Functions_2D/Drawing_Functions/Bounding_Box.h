#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangle_2.h>

#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P2;
typedef Triangle_2<K> Tri;

void Bounding_Box ( vector<vector<Tri>>const& tris, pair<Point2d, Point2d>& bounding_box );
