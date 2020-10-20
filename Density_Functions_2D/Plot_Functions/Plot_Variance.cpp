#include "gnuplot-iostream.h"

#include "Replot_Max_Radius.h"

void Plot_Variance ( Framework_Parameters const& f_p, Input& input )
{
    double terminal_size_x = 8;
    double terminal_size_y = 3.5;
    
    double border = 3;
    double bmargin = 4.5;
    double lmargin = 9;
    double tmargin = 1;
    double rmargin = 2;
    
    double yrange = 38;
    
    string data_file_1 = "Data/Variance.txt";
    string data_file_2;
    string graph_file = "Graphs/Variance.txt";
    
    if (f_p.replot) Replot_Max_Radius( f_p, input, data_file_1, data_file_2 );
    
    Gnuplot gp;
    
    gp << "cd \"" << f_p.output_dir << "\"\n";
    
    gp << "set terminal pdfcairo size " + to_string( terminal_size_x ) + ", " + to_string( terminal_size_y ) + "\n";
    
    gp << "set border " + to_string( border ) + "\n";
    gp << "set grid\n";
    gp << "set bmargin " + to_string( bmargin ) + "\n";
    gp << "set lmargin " + to_string( lmargin ) + "\n";
    gp << "set rmargin " + to_string( rmargin ) + "\n";
    
    if (f_p.title)
    {
        gp << "set tmargin " + to_string( tmargin + 2 ) + "\n";
        gp << "set title '" << f_p.title_str << "' font ', 20' offset 0, 2\n";
    }
    
    else gp << "set tmargin " + to_string( tmargin ) + "\n";
    
    gp << "set ylabel 'Variance' font ', 20' offset -0.5, 0\n";
    
    gp << "set xlabel 'Radius of Balls' font ', 20' offset 0, -0.3\n";
    
    gp << "set xrange [0: " << input.max_radius << "]\n";
    gp << "set yrange [0: " << to_string( yrange ) << "]\n";
    gp << "set xtics font ', 18'\n";
    gp << "set ytics font ', 18'\n";
    
    gp << "set style line 1 lc rgb '#0d61ec' lw 3\n";
    
    gp << "set output \"" + graph_file + "\"\n";
    
    gp << "set samples 1000\n";
    
    string plot;
    
    plot += "plot '" + data_file_1 + "' using 1:" + to_string( input.zone_limit + 1 ) + "smooth csplines ls 1 notitle";
    
    plot += "\n";
    
    gp << plot;
}
