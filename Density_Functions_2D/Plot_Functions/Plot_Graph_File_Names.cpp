#include "Framework_Parameters.h"
#include "Input.h"

void Plot_Graph_File_Names ( Framework_Parameters const& f_p, Input const& input, string& data_file_1, string& data_file_2, string& graph_file, int num_v, int iter )
{
    /*if (input.hyperuniformity)
    {
        data_file_1 = "Data/Poi/0_Variance.txt";
        graph_file = "Graphs/Poi/0_Variance.pdf";
    }
    
    else if (input.superimposed)
    {
        data_file_1 = "Data/Square.txt";
        data_file_2 = "Data/Hexagonal.txt";
        graph_file = "Graphs/Superimposed.pdf";
    }
    
    else
    {
        if (input.superhomo)
        {
            if (input.set_type == "a")
            {
                data_file_1 = "Data/A.txt";
                graph_file = "Graphs/A.pdf";
            }
            
            else if (input.set_type == "b")
            {
                data_file_1 = "Data/B.txt";
                graph_file = "Graphs/B.pdf";
            }
        }
        
        else
        {
            data_file_1 = "Data/Custom.txt";
            graph_file = "Graphs/Custom.pdf";
        }
    }*/
    
    if (f_p.uplusv) data_file_1 = input.data_file + to_string( num_v ) + "_" + to_string( iter ) + ".txt";
    else data_file_1 = input.data_file + ".txt";
    
    if (f_p.uplusv) graph_file = input.graph_file + to_string( num_v ) + "_" + to_string( iter ) + ".pdf";
    else graph_file = input.graph_file + ".pdf";
}
