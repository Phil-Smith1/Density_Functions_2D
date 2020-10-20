#include "Framework_Parameters.h"
#include "Input.h"
#include "Variance.h"

#include <fstream>
#include <sstream>

void Produce_Variance_File ( Framework_Parameters const& f_p, Input const& input )
{
    string data_file;
    
    if (f_p.uplusv) data_file = f_p.output_dir + input.data_file + to_string( input.num_v ) + "_" + to_string( input. rep_iter ) + ".txt";
    else data_file = f_p.output_dir + input.data_file + ".txt";
    
    ifstream ifs( data_file );
    ofstream ofs( "/Users/philsmith/Documents/Work/Xcode Projects/Density_Functions_2D/Output/Data/Variance.txt" );
    
    string line_data;
    
    while (getline( ifs, line_data ))
    {
        stringstream stream;
        
        stream << line_data;
        
        vector<double> results;
        
        for (int counter = 0; counter < 19; ++counter)
        {
            double val;
            
            stream >> val;
            
            results.push_back( val );
        }
        
        double variance = Variance( results );
        
        ofs << results[0];
        
        for (int counter = 1; counter < 19; ++counter)
        {
            ofs << " " << results[counter];
        }
        
        ofs << " " << variance << endl;
    }
}
