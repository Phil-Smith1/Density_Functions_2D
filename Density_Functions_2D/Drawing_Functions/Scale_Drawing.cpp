#include "Bounding_Box.h"

pair<double, Point2d> Scale_Drawing ( cv::Point const& image_sizes, vector<vector<Tri>>const& tris )
{
    pair<Point2d, Point2d> bounding_box;
    
    Bounding_Box( tris, bounding_box ); // Finds the bounding box of the vertices.
    
    Point2d drawing_sizes( bounding_box.second.x - bounding_box.first.x, bounding_box.second.y - bounding_box.first.y );
    drawing_sizes *= 1.05; // Add a 5% border.
    
    Point2d drawing_centre( bounding_box.second.x + bounding_box.first.x, bounding_box.second.y + bounding_box.first.y );
    drawing_centre /= (double)2; // Central point of the bounding box.
    
    Point2d image_centre( image_sizes.x / (double)2, image_sizes.y / (double)2 ); // Centre of the image.
    
    double scale = std::min( image_sizes.x / (double)drawing_sizes.x, image_sizes.y / (double)drawing_sizes.y ); // Scale value.
    
    // Transformation: point -> scale * (point - cloud_centre) + image_centre.
    
    Point2d shift = image_centre - scale * drawing_centre; // Shift value.
    
    return pair<double, Point2d>( scale, shift );
}
