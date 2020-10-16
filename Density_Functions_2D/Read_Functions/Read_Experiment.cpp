#include "Framework_Parameters.h"
#include "Experiment.h"

#include <fstream>
#include <sstream>
#include <iostream>

bool Read_Experiment ( Framework_Parameters const& f_p, Experiment& e )
{
    ifstream ifs( f_p.input_dir + f_p.experiment_file );
    
    if (!ifs.is_open())
    {
        cout << "Experiment file not found!" << endl;
        return false;
    }
    
    string line_data, val;
    
    getline( ifs, line_data );
    
    stringstream stream;
    
    stream << line_data;
    
    while (getline( stream, val, ',' ))
    {
        e.motif_sizes.push_back( stoi( val ) );
    }
    
    getline( ifs, line_data );
    
    stream.clear();
    stream << line_data;
    
    while (getline( stream, val, ',' ))
    {
        e.k.push_back( stoi( val ) );
    }
    
    getline( ifs, line_data );
    
    e.repetitions = stoi( line_data );
    
    ifs.close();
    
    return true;
}

