#include "Framework_Parameters.h"
#include "Input.h"

#include <fstream>

#ifndef Pi
#define Pi
const double PI = 3.14159265359;
#endif

bool Read_V ( Framework_Parameters const& f_p, string& line_data, Input& input )
{
    ifstream ifs( f_p.input_dir + line_data );
    
    if (!ifs.is_open())
    {
        cout << "V not found!" << endl;
        return false;
    }
    
    input.frac_V.clear();
    
    while (getline( ifs, line_data ))
    {
        string val;
        stringstream stream;
        
        stream << line_data;
        
        getline( stream, val, ',' );
        
        double x = stod( val );
        
        getline( stream, val, ',' );
        
        double y = stod( val );
        
        input.frac_V.push_back( P2( x, y ) );
    }
    
    ifs.close();
    
    /*input.frac_V.clear();
    
    int n = 3;
    double scale = 0.06;
    
    for (int counter = 0; counter < n; ++counter)
    {
        input.frac_V.push_back( P2( scale * cos( counter * 2 * PI / (double)n ) / (double)input.cell_param_a, scale * sin( counter * 2 * PI / (double)n ) / (double)input.cell_param_b ) );
    }*/
    
    return true;
}
