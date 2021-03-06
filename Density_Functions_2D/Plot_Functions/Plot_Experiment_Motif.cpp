#include "gnuplot-iostream.h"

#include "Framework_Parameters.h"

void Plot_Experiment_Motif ( Framework_Parameters const& f_p, string const& file_name, string const& y_label, string const& colour )
{
    double terminal_size_x = 8;
    double terminal_size_y = 3.5;
    
    double border = 3;
    double bmargin = 5;
    double lmargin = 13;
    double tmargin = 2;
    double rmargin = 3;
    
    string data_file = "Experiments/Data/" + file_name + ".txt";
    string graph_file = "Experiments/Graphs/" + file_name + ".pdf";
    
    Gnuplot gp;
    
    gp << "cd \"" << f_p.output_dir << "\"\n";
    
    gp << "set terminal pdfcairo size " + to_string( terminal_size_x ) + ", " + to_string( terminal_size_y ) + "\n";
    
    gp << "set border " + to_string( border ) + "\n";
    gp << "set grid\n";
    gp << "set bmargin " + to_string( bmargin ) + "\n";
    gp << "set lmargin " + to_string( lmargin ) + "\n";
    gp << "set rmargin " + to_string( rmargin ) + "\n";
    gp << "set tmargin " + to_string( tmargin ) + "\n";
    
    gp << "set ylabel '" + y_label + "' font ', 26' offset -4, 0\n";
        
    gp << "set xlabel 'Number m of Motif Points' font ', 26' offset 0, -1\n";
        
    gp << "set xrange [1:50]\n";
    gp << "set xtics font ', 24'\n";
    gp << "set ytics font ', 24'\n";
    
    gp << "set style line 1 lc rgb '#" + colour + "' lw 3\n";
    
    gp << "set output \"" + graph_file + "\"\n";
    
    gp << "set samples 1000\n";
    
    string plot;
        
    plot += "plot '" + data_file + "' with linespoints ls 1 notitle";
        
    plot += "\n";
    
    gp << plot;
}
