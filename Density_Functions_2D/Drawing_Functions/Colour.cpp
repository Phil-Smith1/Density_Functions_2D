#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

Scalar Colour_4( int n )
{
    if (n % 4 == 0) return CV_RGB( 255, 255, 0 );
    if (n % 4 == 1) return CV_RGB( 0, 255, 0 );
    if (n % 4 == 2) return CV_RGB( 0, 255, 255 );
    else return CV_RGB( 255, 128, 0 );
}

Scalar Grey_Colour( int k, int n )
{
    double colour;
    
    if (n == 1) colour = 0;
    else colour = 0 + 255 * (k - 1) / (double)(n);
    
    return CV_RGB( colour, colour, colour );
}

Scalar Colour ( int n )
{
    if (n == 0) return CV_RGB( 255, 255, 0 );
    else if (n == 1) return CV_RGB( 0, 255, 0 );
    else if (n == 2) return CV_RGB( 0, 255, 255 );
    else if (n == 3) return CV_RGB( 255, 128, 0 );
    else if (n == 4) return CV_RGB( 128, 128, 255 );
    else if (n == 5) return CV_RGB( 255, 128, 255 );
    else if (n == 6) return CV_RGB( 128, 0, 255 );
    else if (n == 7) return CV_RGB( 0, 255, 128 );
    else if (n == 8) return CV_RGB( 0, 0, 255 );
    else if (n == 9) return CV_RGB( 128, 0, 224 );
    else if (n == 10) return CV_RGB( 128, 255, 0 );
    else if (n == 11) return CV_RGB( 255, 0, 255 );
    else if (n == 12) return CV_RGB( 0, 128, 255 );
    else if (n == 13) return CV_RGB( 128, 255, 128 );
    else if (n == 14) return CV_RGB( 255, 128, 128 );
    else if (n == 15) return CV_RGB( 255, 255, 128 );
    else if (n == 16) return CV_RGB( 128, 255, 255 );
    else if (n == 17) return CV_RGB( 128, 128, 128 );
    else if (n == 18) return CV_RGB( 224, 128, 32 );
    else if (n == 19) return CV_RGB( 32, 224, 128 );
    else if (n == 20) return CV_RGB( 128, 32, 224 );
    else if (n == 21) return CV_RGB( 224, 32, 128 );
    else if (n == 22) return CV_RGB( 128, 224, 32 );
    else if (n == 23) return CV_RGB( 32, 128, 224 );
    else if (n == 24) return CV_RGB( 224, 224, 32 );
    else if (n == 25) return CV_RGB( 224, 32, 224 );
    else if (n == 26) return CV_RGB( 32, 224, 224 );
    else if (n == 27) return CV_RGB( 32, 224, 32 );
    else if (n == 28) return CV_RGB( 128, 224, 224 );
    else if (n == 29) return CV_RGB( 32, 32, 224 );
    else return CV_RGB( 0, 0, 0 );
}
