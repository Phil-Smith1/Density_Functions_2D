#include "Framework_Parameters.h"
#include "Input.h"

#include <fstream>

bool Read_Input ( Framework_Parameters const& f_p, string const& input_file, Input& input )
{
    ifstream ifs_1( f_p.input_dir + input_file );
    
    if (!ifs_1.is_open())
    {
        cout << "Global file not found!" << endl;
        return false;
    }
    
    string line_data, val;
    
    getline( ifs_1, line_data );
    
    stringstream stream;
    
    stream << line_data;
    
    getline( stream, val, ',' );
    
    ifstream ifs_2( f_p.input_dir + val );
    
    if (!ifs_2.is_open())
    {
        cout << "Cell file not found!" << endl;
        return false;
    }
    
    getline( ifs_2, line_data );
    
    stream.clear();
    stream << line_data;
    
    getline( stream, val, ',' );
    
    input.cell_param_a = stod( val );
    
    getline( stream, val, ',' );
    
    input.cell_param_b = stod( val );
    
    getline( stream, val, ',' );
    
    input.cell_param_gamma = stod( val );
    
    ifs_2.close();
    
    getline( ifs_1, line_data );
    
    stream.clear();
    stream << line_data;
    
    getline( stream, val, ',' );
    
    ifstream ifs_3( f_p.input_dir + val );
    
    if (!ifs_3.is_open())
    {
        cout << "Frac_Coords file not found!" << endl;
        return false;
    }
    
    while (getline( ifs_3, line_data ))
    {
        stream.clear();
        stream << line_data;
        
        getline( stream, val, ',' );
        
        double x = stod( val );
        
        getline( stream, val, ',' );
        
        double y = stod( val );
        
        input.frac_base_pts.push_back( P2( x, y ) );
    }
    
    ifs_3.close();
    
    getline( ifs_1, line_data );
    
    ifs_1.close();
    
    stream.clear();
    stream << line_data;
    
    getline( stream, val, ',' );
    
    ifstream ifs_4( f_p.input_dir + val );
    
    if (!ifs_4.is_open())
    {
        cout << "File_Names file not found!" << endl;
        return false;
    }
    
    getline( ifs_4, line_data );
    
    input.data_file = line_data;
    
    getline( ifs_4, line_data );
    
    input.graph_file = line_data;
    
    getline( ifs_4, line_data );
    
    input.drawing_file = line_data;
    
    ifs_4.close();
    
    return true;
}
