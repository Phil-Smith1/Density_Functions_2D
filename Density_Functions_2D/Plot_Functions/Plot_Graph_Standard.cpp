#include "gnuplot-iostream.h"

#include "Plot_Graph_File_Names.h"
#include "Replot_Max_Radius.h"

void Plot_Graph_Standard ( Framework_Parameters const& f_p, Input& input )
{
    double terminal_size_x = 5;
    double terminal_size_y = 3.5;
    
    double border = 3;
    double bmargin = 4.5;
    double lmargin = 11;
    double tmargin = 4;
    double rmargin = 3;
    
    if (f_p.superimposed) tmargin = 4;
    
    double yrange = 1.0001;
    
    string data_file_1;
    string data_file_2;
    string graph_file;
    
    Plot_Graph_File_Names( f_p, input, data_file_1, data_file_2, graph_file );
    
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
    
    if (!f_p.superimposed ) gp << "set ylabel '{/Symbol y}@_k^A(t)' font ', 24' offset -1.7, 0\n";
    else gp << "set ylabel '{/Symbol y}_k(t)' font ', 24' offset -1.6, 0\n";
    
    gp << "set xlabel 'Radius of Balls' font ', 24' offset 0, -0.7\n";
    
    gp << "set xrange [0: " << input.max_radius << "]\n";
    gp << "set yrange [0: " << to_string( yrange ) << "]\n";
    gp << "set xtics font ', 22'\n";
    gp << "set ytics font ', 22'\n";
    
    if (!f_p.superimposed) gp << "set key horizontal at graph 0.5, graph 1.03 center bottom font ', 22' spacing 1.5 samplen 1.5\n";
    else gp << "set key horizontal at graph 0.5, graph 1.04 center bottom font ', 18' samplen 2\n";
    
    gp << "set style line 1 lc rgb '#94E3FF' lw 3\n";
    gp << "set style line 2 lc rgb '#0d61ec' lw 3\n";
    gp << "set style line 3 lc rgb '#24ae1d' lw 3\n";
    gp << "set style line 4 lc rgb '#ffae00' lw 3\n";
    gp << "set style line 5 lc rgb '#e70000' lw 3\n";
    gp << "set style line 6 lc rgb '#db0dec' lw 3\n";
    gp << "set style line 7 lc rgb '#7B0985' lw 3\n";
    gp << "set style line 8 lc rgb '#87663E' lw 3\n";
    gp << "set style line 9 lc rgb '#000000' lw 3\n";
    
    gp << "set output \"" + graph_file + "\"\n";
    
    gp << "set samples 1000\n";
    
    string key_title = "{/Symbol y}@_0^A";
    
    if (f_p.superimposed) key_title = "k = 0";
    
    string plot;
    
    plot += "plot '" + data_file_1 + "' using 1:2 smooth csplines ls 1 title '" + key_title + "'";
    
    for (int counter = 1; counter < input.zone_limit; ++counter)
    {
        key_title = "  {/Symbol y}@_{" + to_string( counter ) + "}^A";
        
        if (f_p.superimposed) key_title = " k = " + to_string( counter );
        
        plot += ", '" + data_file_1 + "' using 1:" + to_string( counter + 2 ) + "smooth csplines ls " + to_string( counter + 1 ) + " title '" + key_title + "'";
    }
    
    if (f_p.superimposed)
    {
        gp << "set style line 11 dt 2 lc rgb '#94E3FF' lw 3\n";
        gp << "set style line 12 dt 2 lc rgb '#0d61ec' lw 3\n";
        gp << "set style line 13 dt 2 lc rgb '#24ae1d' lw 3\n";
        gp << "set style line 14 dt 2 lc rgb '#ffae00' lw 3\n";
        gp << "set style line 15 dt 2 lc rgb '#e70000' lw 3\n";
        gp << "set style line 16 dt 2 lc rgb '#db0dec' lw 3\n";
        gp << "set style line 17 dt 2 lc rgb '#7B0985' lw 3\n";
        gp << "set style line 18 dt 2 lc rgb '#87663E' lw 3\n";
        gp << "set style line 19 dt 2 lc rgb '#000000' lw 3\n";
        
        for (int counter = 0; counter < input.zone_limit; ++counter)
        {
            plot += ", '" + data_file_2 + "' using 1:" + to_string( counter + 2 ) + " smooth csplines ls " + to_string( counter + 11 ) + " notitle";
        }
    }
    
    plot += "\n";
    
    gp << plot;
}
