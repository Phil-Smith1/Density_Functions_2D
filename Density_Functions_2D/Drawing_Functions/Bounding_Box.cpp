#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangle_2.h>

#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;
using namespace CGAL;

typedef Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P2;
typedef Triangle_2<K> Tri;

void Bounding_Box ( vector<vector<Tri>>const& tris, pair<Point2d, Point2d>& bounding_box )
{
    bounding_box.first = Point2d( 1e10, 1e10 ); // Will be the most left and lowest points.
    bounding_box.second = Point2d( -1e10, -1e10 ); // Will be the most right and highest points.
    
    int tris_size = (int)tris.size() - 1;
    
    for (int counter_1 = 0; counter_1 < tris[tris_size].size(); ++counter_1)
    {
        for (int counter_2 = 0; counter_2 < 3; ++counter_2)
        {
            P2 p = tris[tris_size][counter_1].vertex( counter_2 );
            
            if (bounding_box.first.x > p.x()) bounding_box.first.x = to_double( p.x() );
            if (bounding_box.first.y > -p.y()) bounding_box.first.y = to_double( -p.y() );
            if (bounding_box.second.x < p.x()) bounding_box.second.x = to_double( p.x() );
            if (bounding_box.second.y < -p.y()) bounding_box.second.y = to_double( -p.y() );
        }
    }
}
