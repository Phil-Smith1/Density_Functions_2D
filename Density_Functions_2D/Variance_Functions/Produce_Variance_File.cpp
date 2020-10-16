#include "Variance.h"

#include <fstream>
#include <sstream>
#include <vector>

void Produce_Variance_File ( string const& data_file )
{
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
