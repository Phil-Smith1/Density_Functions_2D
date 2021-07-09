#include "Framework_Parameters.h"
#include "Input.h"

#include <fstream>

#ifndef tiny_number
#define tiny_number
const double tiny_num = 1e-10;
#endif

void Combine_And_Write_Extracted_Data ( Framework_Parameters const& f_p, Input const& input, vector<double>const& cell_volume, vector<vector<double>>& results )
{
    // Dividing by the cell volume.
    
    for (int counter_1 = 0; counter_1 < results.size(); ++counter_1)
    {
        for (int counter_2 = 0; counter_2 < input.zone_limit; ++counter_2)
        {
            results[counter_1][counter_2 + 1] = results[counter_1][counter_2 + 1] / (double)cell_volume[counter_2];
        }
    }
    
    // Calculating density functions: "at least" -> "exact".
    
    for (int counter_1 = 0; counter_1 < results.size(); ++counter_1)
    {
        vector<double> results_copy = results[counter_1];
        
        for (int counter_2 = 0; counter_2 < input.zone_limit - 1; ++counter_2)
        {
            results[counter_1][counter_2 + 1] = results_copy[counter_2 + 1] - results_copy[counter_2 + 2];
            
            if (abs( results[counter_1][counter_2 + 1] ) < tiny_num) results[counter_1][counter_2 + 1] = tiny_num;
            else if (results[counter_1][counter_2 + 1] < 0) results[counter_1][counter_2 + 1] = tiny_num;
        }
        
        if (f_p.densigram)
        {
            vector<double> vec( results[counter_1].size() );
            
            vec[0] = results[counter_1][0];
            
            for (int counter_2 = 1; counter_2 < results[counter_1].size(); ++counter_2)
            {
                for (int counter_3 = 1; counter_3 < counter_2 + 1; ++counter_3)
                {
                    vec[counter_2] += results[counter_1][counter_3];
                }
            }
            
            results[counter_1] = vec;
            
            for (int counter_2 = 0; counter_2 < input.zone_limit - 1; ++counter_2)
            {
                if (results[counter_1][counter_2 + 1] > 1 - tiny_num * 1e6) results[counter_1][counter_2 + 1] = 1 - tiny_num * 1e6;
                
                if (abs( results[counter_1][counter_2 + 1] ) < tiny_num * 1e6) results[counter_1][counter_2 + 1] = tiny_num * 1e6;
                else if (results[counter_1][counter_2 + 1] < 0) results[counter_1][counter_2 + 1] = tiny_num * 1e6;
            }
        }
    }
    
    // Adding 0th density function
    
    if (!f_p.densigram && f_p.zero_density)
    {
        bool df0_is_0 = false;
        
        for (int counter_1 = 0; counter_1 < results.size(); ++counter_1)
        {
            for (int counter_2 = input.zone_limit; counter_2 > 1; --counter_2)
            {
                results[counter_1][counter_2] = results[counter_1][counter_2 - 1];
            }
            
            if (df0_is_0) results[counter_1][1] = tiny_num;
            
            else
            {
                results[counter_1][1] = 1;
                
                for (int counter_2 = 2; counter_2 < input.zone_limit + 1; ++counter_2)
                {
                    results[counter_1][1] -= results[counter_1][counter_2];
                }
            }
            
            if (results[counter_1][1] < tiny_num * 1e4) df0_is_0 = true;
        }
    }
    
    string data_file;
    
    if (f_p.uplusv) data_file = f_p.output_dir + input.data_file + to_string( input.num_v ) + "_" + to_string( input. rep_iter ) + ".txt";
    else data_file = f_p.output_dir + input.data_file + ".txt";
    
    int z_l = input.zone_limit;
    
    if (!f_p.zero_density) --z_l;
    
    ofstream ofs( data_file );
    
    ofs << setprecision( 10 ) << results[0][0];
    
    for (int counter = 0; counter < z_l; ++counter)
    {
        ofs << " " << results[0][counter + 1];
    }
    
    for (int counter_1 = 1; counter_1 < results.size(); ++counter_1)
    {
        ofs << endl;
        
        ofs << setprecision( 10 ) << results[counter_1][0];
        
        for (int counter_2 = 0; counter_2 < z_l; ++counter_2)
        {
            ofs << " " << results[counter_1][counter_2 + 1];
        }
    }
    
    ofs.close();
    
    cout << "Data extracted." << endl;
}
