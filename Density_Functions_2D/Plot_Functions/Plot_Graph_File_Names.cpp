#include "Framework_Parameters.h"
#include "Input.h"

void Plot_Graph_File_Names ( Framework_Parameters const& f_p, Input const& input, string& data_file_1, string& data_file_2, string& graph_file )
{
    if (f_p.uplusv) data_file_1 = input.data_file + to_string( input.num_v ) + "_" + to_string( input.rep_iter ) + ".txt";
    else data_file_1 = input.data_file + ".txt";
    
    if (f_p.uplusv) graph_file = input.graph_file + to_string( input.num_v ) + "_" + to_string( input.rep_iter ) + ".pdf";
    else graph_file = input.graph_file + ".pdf";
    
    if (f_p.superimposed)
    {
        data_file_1 = "Data/Custom_1.txt";
        data_file_2 = "Data/Custom_2.txt";
    }
}
