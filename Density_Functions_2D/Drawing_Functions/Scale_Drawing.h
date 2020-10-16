#pragma once

#include "Bounding_Box.h"

pair<double, Point2d> Scale_Drawing ( cv::Point const& image_sizes, vector<vector<Tri>>const& tris );
