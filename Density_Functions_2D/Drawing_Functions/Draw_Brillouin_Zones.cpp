#include "Framework_Parameters.h"
#include "Input.h"
#include "Surrounding_Cloud.h"
#include "Scale_Drawing.h"
#include "Colour.h"

#include <opencv2/imgcodecs.hpp>

void Draw_Brillouin_Zones ( Framework_Parameters const& f_p, Input const& input, int num_inputs, vector<P2> base_pts, int base_pt, double ** matrix, vector<vector<Tri>>const& tris )
{
    multimap<double, P2> drawn_cloud;
    
    Surrounding_Cloud( 3, matrix, base_pt, base_pts, drawn_cloud );
    
    vector<P2> lattice_pts;
    
    P2 p1 = P2( 1, 0 );
    P2 p2 = P2( 0, 1 );
    
    Frac_To_Cart_Coords( matrix, p1 );
    Frac_To_Cart_Coords( matrix, p2 );
    
    lattice_pts.push_back( p1 );
    lattice_pts.push_back( p2 );
    
    cv::Point image_sizes( 1600, 1600 );
    Mat image( image_sizes, CV_8UC3, CV_RGB( 255, 255, 255 ) );
    
    pair<double, Point2d> scale_shift;
    
    scale_shift = Scale_Drawing( image_sizes, tris );
    
    for (int counter_1 = 0; counter_1 < tris.size(); ++counter_1)
    {
        for (int counter_2 = 0; counter_2 < tris[counter_1].size(); ++counter_2)
        {
            cv::Point points[1][3] = {};
            
            for (int counter_3 = 0; counter_3 < 3; ++counter_3)
            {
                P2 pt = tris[counter_1][counter_2].vertex( counter_3 );
                Point2d pt_cv = Point2d( to_double( pt.x() ), to_double( -pt.y() ) );
                points[0][counter_3] = cv::Point( scale_shift.first * pt_cv + scale_shift.second );
            }
                 
            const cv::Point* ppt[1] = { points[0] };
            int npt[] = { 3 };
             
            fillPoly( image, ppt, npt, 1, Colour_4( counter_1 ), LINE_AA );
        }
    }
    
    Point2d base_pt_cv = Point2d( to_double( base_pts[base_pt].x() ), to_double( -base_pts[base_pt].y() ) );
    Point2d lattice_pt_1 = Point2d( to_double( lattice_pts[0].x() ), to_double( -lattice_pts[0].y() ) );
    Point2d lattice_pt_2 = Point2d( to_double( lattice_pts[1].x() ), to_double( -lattice_pts[1].y() ) );
    
    line( image, cv::Point( scale_shift.first * base_pt_cv + scale_shift.second ), cv::Point( scale_shift.first * lattice_pt_1 + scale_shift.second ), CV_RGB( 0, 0, 0 ), 1, LINE_AA );
    line( image, cv::Point( scale_shift.first * base_pt_cv + scale_shift.second ), cv::Point( scale_shift.first * lattice_pt_2 + scale_shift.second ), CV_RGB( 0, 0, 0 ), 1, LINE_AA );
    
    circle( image, cv::Point( scale_shift.first * base_pt_cv + scale_shift.second ), 10, CV_RGB( 255, 0, 0 ), -1 );
    circle( image, cv::Point( scale_shift.first * base_pt_cv + scale_shift.second ), 10, CV_RGB( 0, 0, 0 ), 3 );
    
    for (auto iter = drawn_cloud.begin(); iter != drawn_cloud.end(); ++iter)
    {
        Point2d lpt = Point2d( to_double( iter->second.x() ), to_double( -iter->second.y() ) );
        
        circle( image, cv::Point( scale_shift.first * lpt + scale_shift.second ), 10, CV_RGB( 255, 0, 0 ), -1 );
        circle( image, cv::Point( scale_shift.first * lpt + scale_shift.second ), 10, CV_RGB( 0, 0, 0 ), 3 );
    }
    
    string image_file = f_p.output_dir + input.drawing_file + "_" + to_string( num_inputs ) + ".png";
    
    imwrite( image_file, image );
    
    cout << "Drawn Brillouin zones." << endl;
}
