#include "Framework_Parameters.h"
#include "Input.h"

#include <fstream>

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
    
    return true;
}
