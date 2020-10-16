#include "gnuplot-iostream.h"

#include "Framework_Parameters.h"

void Plot_Perim ( Framework_Parameters const& f_p, int zone_limit )
{
    double terminal_size_x = 8;
    double terminal_size_y = 3.5;
    
    double border = 3;
    double bmargin = 4.5;
    double lmargin = 12;
    double tmargin = 4;
    double rmargin = 2;
    
    string data_file = "Experiments/Data/Perim.txt";
    string graph_file = "Experiments/Graphs/Perim.pdf";
    
    Gnuplot gp;
    
    gp << "cd \"" << f_p.output_dir << "\"\n";
    
    gp << "set terminal pdfcairo size " + to_string( terminal_size_x ) + ", " + to_string( terminal_size_y ) + "\n";
    
    gp << "set border " + to_string( border ) + "\n";
    gp << "set grid\n";
    gp << "set bmargin " + to_string( bmargin ) + "\n";
    gp << "set lmargin " + to_string( lmargin ) + "\n";
    gp << "set rmargin " + to_string( rmargin ) + "\n";
    gp << "set tmargin " + to_string( tmargin ) + "\n";
    
    gp << "set ylabel 'Perimeter Length' font ', 24' offset -1.5, 0\n";
        
    gp << "set xlabel 'Size of Motif' font ', 20' offset 0, -0.3\n";
        
    gp << "set xrange [1:20]\n";
    gp << "set xtics font ', 18'\n";
    gp << "set ytics font ', 18'\n";
    
    gp << "set style line 1 lc rgb '#0d61ec' lw 3\n";
    gp << "set style line 2 lc rgb '#24ae1d' lw 3\n";
    gp << "set style line 3 lc rgb '#ffae00' lw 3\n";
    gp << "set style line 4 lc rgb '#e70000' lw 3\n";
    gp << "set style line 5 lc rgb '#db0dec' lw 3\n";
    gp << "set style line 6 lc rgb '#7B0985' lw 3\n";
    gp << "set style line 7 lc rgb '#87663E' lw 3\n";
    gp << "set style line 8 lc rgb '#000000' lw 3\n";
    
    gp << "set output \"" + graph_file + "\"\n";
    
    gp << "set samples 1000\n";
    
    string plot;
        
    plot += "plot '" + data_file + "' using 1:2 with linespoints ls 1 title '1'";
    
    for (int counter = 1; counter < zone_limit; ++counter)
    {
        plot += ", '" + data_file + "' using 1:" + to_string( counter + 2 ) + "with linespoints ls " + to_string( counter + 1 ) + " title '" + to_string( counter + 1 ) + "'";
    }
        
    plot += "\n";
    
    gp << plot;
}
