#include "Plot_Perim.h"

void Plot_Experiment ( Framework_Parameters const& f_p, string const& file_name, string const& y_label )
{
    double terminal_size_x = 8;
    double terminal_size_y = 3.5;
    
    double border = 3;
    double bmargin = 4;
    double lmargin = 11;
    double tmargin = 2;
    double rmargin = 2;
    
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
    
    gp << "set ylabel '" + y_label + "' font ', 24' offset -2, 0\n";
        
    gp << "set xlabel 'Index k of Brillouin Zone' font ', 20' offset 0, -0.5\n";
        
    gp << "set xrange [1:30]\n";
    gp << "set xtics font ', 18'\n";
    gp << "set ytics font ', 18'\n";
    
    gp << "set style line 1 lc rgb '#006400' lw 3\n";
    
    // Poly Blue 0d61ec
    // Time Dark green 006400
    // Vertices Red ff0000
    // Edges Orange ffa500
    // Perim Purple 800080
    
    gp << "set output \"" + graph_file + "\"\n";
    
    gp << "set samples 1000\n";
    
    string plot;
        
    plot += "plot '" + data_file + "' with linespoints ls 1 notitle";
        
    plot += "\n";
    
    gp << plot;
}

void Plot_Experiment_2 ( Framework_Parameters const& f_p, string const& file_name, string const& y_label )
{
    double terminal_size_x = 8;
    double terminal_size_y = 3.5;
    
    double border = 3;
    double bmargin = 4;
    double lmargin = 11;
    double tmargin = 2;
    double rmargin = 2;
    
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
    
    gp << "set ylabel '" + y_label + "' font ', 24' offset -2, 0\n";
        
    gp << "set xlabel 'Number m of Motif Points' font ', 20' offset 0, -0.5\n";
        
    gp << "set xrange [1:50]\n";
    gp << "set xtics font ', 18'\n";
    gp << "set ytics font ', 18'\n";
    
    gp << "set style line 1 lc rgb '#800080' lw 3\n";
    
    // Poly Blue 0d61ec
    // Time Dark green 006400
    // Vertices Red ff0000
    // Edges Orange ffa500
    // Perim Purple 800080
    
    gp << "set output \"" + graph_file + "\"\n";
    
    gp << "set samples 1000\n";
    
    string plot;
        
    plot += "plot '" + data_file + "' with linespoints ls 1 notitle";
        
    plot += "\n";
    
    gp << plot;
}

void Plot_Experiments ( Framework_Parameters const& f_p, int zone_limit )
{
    if (f_p.time_vary_k) Plot_Experiment( f_p, "Runtime", "Runtime (ms)" );
    
    if (f_p.time_vary_m) Plot_Experiment_2( f_p, "Runtime", "Runtime (ms)" );
    
    if (f_p.vary_k)
    {
        Plot_Experiment( f_p, "Vertices", "Number of Vertices" );
        Plot_Experiment( f_p, "Edges", "Number of Edges" );
        Plot_Experiment( f_p, "Polys", "Number of Polygons" );
        Plot_Experiment( f_p, "Perim", "Perimeter Length" );
    }
    
    if (f_p.vary_m)
    {
        Plot_Experiment_2( f_p, "Vertices", "Number of Vertices" );
        Plot_Experiment_2( f_p, "Edges", "Number of Edges" );
        Plot_Experiment_2( f_p, "Polys", "Number of Polygons" );
        Plot_Experiment_2( f_p, "Perim", "Perimeter Length" );
    }
    
    //Plot_Perim( f_p, zone_limit );
}
