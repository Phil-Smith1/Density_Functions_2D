#include "Framework_Parameters.h"
#include "Input.h"
#include "Scale_Drawing.h"
#include "Colour.h"

#include <opencv2/imgcodecs.hpp>

void Draw_Brillouin_Zones ( Framework_Parameters const& f_p, Input const& input, int base_pt, multimap<double, P2>const& cloud, vector<vector<Tri>>const& tris )
{
    cv::Point image_sizes( 800, 800 );
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
             
            fillPoly( image, ppt, npt, 1, Colour( counter_1 ), LINE_AA );
        }
    }
    
    Point2d base_pt_cv = Point2d( to_double( input.base_pts[base_pt].x() ), to_double( -input.base_pts[base_pt].y() ) );
    Point2d lattice_pt_1 = Point2d( to_double( input.lattice_vectors[0].x() ), to_double( -input.lattice_vectors[0].y() ) );
    Point2d lattice_pt_2 = Point2d( to_double( input.lattice_vectors[1].x() ), to_double( -input.lattice_vectors[1].y() ) );
    
    line( image, cv::Point( scale_shift.first * base_pt_cv + scale_shift.second ), cv::Point( scale_shift.first * lattice_pt_1 + scale_shift.second ), CV_RGB( 0, 0, 0 ), 1, LINE_AA );
    line( image, cv::Point( scale_shift.first * base_pt_cv + scale_shift.second ), cv::Point( scale_shift.first * lattice_pt_2 + scale_shift.second ), CV_RGB( 0, 0, 0 ), 1, LINE_AA );
    
    circle( image, cv::Point( scale_shift.first * base_pt_cv + scale_shift.second ), 5, CV_RGB( 255, 0, 0 ), -1 );
    circle( image, cv::Point( scale_shift.first * base_pt_cv + scale_shift.second ), 5, CV_RGB( 0, 0, 0 ), 2 );
    
    for (auto iter = cloud.begin(); iter != cloud.end(); ++iter)
    {
        Point2d pt_cv = Point2d( to_double( iter->second.x() ), to_double( -iter->second.y() ) );
        
        circle( image, cv::Point( scale_shift.first * pt_cv + scale_shift.second ), 5, CV_RGB( 255, 0, 0 ), -1 );
        circle( image, cv::Point( scale_shift.first * pt_cv + scale_shift.second ), 5, CV_RGB( 0, 0, 0 ), 2 );
    }
    
    /*cv::Point image_sizes_2( 2100, 2970 );
    Mat image_2( image_sizes_2, CV_8UC3, CV_RGB( 255, 255, 255 ) );
    image( Rect( (image_sizes.x - image_sizes_2.x) / 2, (image_sizes.y - image_sizes_2.y) / 2, image_2.cols, image_2.rows ) ).copyTo( image_2 );*/
    
    string image_file = f_p.output_dir + input.drawing_file + "_" + to_string( input.num_input ) + ".png";
    
    imwrite( image_file, image );
    
    cout << "Drawn Brillouin zones." << endl;
}
