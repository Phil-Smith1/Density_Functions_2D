#include "Framework_Parameters.h"

void Data_File_Name ( Framework_Parameters const& f_p, string& data_file )
{
    /*if (input.superhomo)
    {
        if (input.set_type == "a") data_file = input.output_dir + "Data/A.txt";
        
        else if (input.set_type == "b") data_file = input.output_dir + "Data/B.txt";
    }*/
        
    data_file = f_p.output_dir + "Data/Custom.txt";
}
