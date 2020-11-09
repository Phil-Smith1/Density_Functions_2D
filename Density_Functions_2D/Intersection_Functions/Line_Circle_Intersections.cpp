#include "Circle.h"
#include "Edge.h"

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

int Line_Circle_Intersections ( Circle const& circle, Edge& e )
{
    long double a = e.line.a(), b = e.line.b(), c = e.line.c();
    
    if (abs( a / (long double)b ) < 1e-8) a = 0;
    if (abs( b / (long double)a ) < 1e-8) b = 0;
    
    if (abs( a ) > tiny_num && abs( b ) > tiny_num)
    {
        long double discriminant = circle.r * circle.r * (1 + pow( a / (long double)b, 2 )) - pow( circle.c.y() + circle.c.x() * a / (long double)b + c / (long double)b, 2 );
        
        if (discriminant < 0) return 0;
        
        long double x_1 = (circle.c.x() - circle.c.y() * a / (long double)b - a * c / (long double)(b * b) + sqrtl( discriminant )) / (long double)(1 + a * a / (long double)(b * b));
        long double x_2 = (circle.c.x() - circle.c.y() * a / (long double)b - a * c / (long double)(b * b) - sqrtl( discriminant )) / (long double)(1 + a * a / (long double)(b * b));
        long double y_1 = (- a * x_1 - c) / (long double)b;
        long double y_2 = (- a * x_2 - c) / (long double)b;
        
        e.i1 = P2( x_1, y_1 );
        e.i2 = P2( x_2, y_2 );
        
        if (discriminant < tiny_num) return 1;
        
        else return 2;
    }
    
    else if (abs( b ) > tiny_num)
    {
        long double discriminant = circle.r * circle.r - pow( c / (long double)b + circle.c.y(), 2 );
        
        if (discriminant < 0) return 0;
        
        long double x_1 = circle.c.x() + sqrtl( discriminant );
        long double x_2 = circle.c.x() - sqrtl( discriminant );
        long double y_1 = - c / (long double)b;
        long double y_2 = - c / (long double)b;
        
        e.i1 = P2( x_1, y_1 );
        e.i2 = P2( x_2, y_2 );
        
        if (discriminant < tiny_num) return 1;
        
        else return 2;
    }
    
    else
    {
        long double discriminant = circle.r * circle.r - pow( c / (long double)a + circle.c.x(), 2 );
        
        if (discriminant < 0) return 0;
        
        long double y_1 = circle.c.y() + sqrt( discriminant );
        long double y_2 = circle.c.y() - sqrt( discriminant );
        long double x_1 = - c / (long double)a;
        long double x_2 = - c / (long double)a;
        
        e.i1 = P2( x_1, y_1 );
        e.i2 = P2( x_2, y_2 );
        
        if (discriminant < tiny_num) return 1;
        
        else return 2;
    }
}
