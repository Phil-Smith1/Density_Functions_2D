#include "gnuplot-iostream.h"

#include "Plot_Graph_File_Names.h"
#include "Replot_Max_Radius.h"

void Plot_Densigram ( Framework_Parameters const& f_p, Input& input )
{
    double terminal_size_x = 8;
    double terminal_size_y = 3.5;
    
    double border = 3;
    double bmargin = 4.5;
    double lmargin = 12;
    double tmargin = 9;
    double rmargin = 2;
    
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
    
    if (!f_p.superimposed ) gp << "set ylabel '{/Symbol S}@_1^n{/Symbol y}@_k^A(t)' font ', 24' offset -1.5, 0\n";
    else gp << "set ylabel '{/Symbol S}@_1^n{/Symbol y}_k(t)' font ', 20' offset -0.5, 0\n";
    
    gp << "set xlabel 'Radius of Balls' font ', 20' offset 0, -0.3\n";
    
    gp << "set xrange [0: " << input.max_radius << "]\n";
    gp << "set yrange [0: " << to_string( yrange ) << "]\n";
    gp << "set xtics font ', 18'\n";
    gp << "set ytics font ', 18'\n";
    
    if (!f_p.superimposed) gp << "set key horizontal at graph 0.5, graph 1.03 center bottom font ', 22' spacing 1.5 samplen 1.5\n";
    else gp << "set key horizontal at graph 0.5, graph 1.04 center bottom font ', 16'\n";
    
    gp << "set style line 1 lc rgb '#BDDAFF' lw 3\n";
    gp << "set style line 2 lc rgb '#A0C7FA' lw 3\n";
    gp << "set style line 3 lc rgb '#75AAEF' lw 3\n";
    gp << "set style line 4 lc rgb '#548FDA' lw 3\n";
    gp << "set style line 5 lc rgb '#3174CA' lw 3\n";
    gp << "set style line 6 lc rgb '#1760BB' lw 3\n";
    gp << "set style line 7 lc rgb '#064AA0' lw 3\n";
    gp << "set style line 8 lc rgb '#003983' lw 3\n";
    gp << "set style line 9 lc rgb '#000000' lw 3\n";
    
    gp << "set output \"" + graph_file + "\"\n";
    
    gp << "set samples 1000\n";
    
    string key_title = "n = 1";
    
    string plot;
    
    plot += "plot '" + data_file_1 + "' using 1:2 smooth csplines with filledcurves above y1 = 0 ls 1 title '" + key_title + "'";
    
    for (int counter = 1; counter < input.zone_limit - 1; ++counter)
    {
        key_title = "n = " + to_string( counter + 1 );
        
        plot += ", '" + data_file_1 + "' using 1:" + to_string( counter + 2 ) + " smooth csplines with filledcurves above y1 = 0 ls " + to_string( counter + 1 ) + " title '" + key_title + "'";
    }
    
    gp << "f(x) = 1\n";
    gp << "g(x) = 0\n";
    plot += ", '+' using 1:(f($1)):(g($1)) lc '#F3F9FE' with filledcurves closed notitle";
    
    gp << "h(x) = 10 - 10 * x\n";
    plot += ", '+' using 1:(f($1)):(h($1)) lc '#8C9196' with filledcurves closed notitle";
    
    for (int counter = input.zone_limit - 2; counter >= 0; --counter)
    {
        plot += ", '" + data_file_1 + "' using 1:" + to_string( counter + 2 ) + " smooth csplines with filledcurves above y1 = 0 ls " + to_string( counter + 1 ) + " notitle";
    }
    
    for (int counter = 0; counter < input.zone_limit - 1; ++counter)
    {
        plot += ", '" + data_file_1 + "' using 1:" + to_string( counter + 2 ) + " smooth csplines ls " + to_string( 9 ) + " notitle";
    }
    
    if (f_p.superimposed)
    {
        gp << "set style line 10 dt 2 lc rgb '#8AFF05' lw 3\n";
        
        for (int counter = 0; counter < input.zone_limit - 1; ++counter)
        {
            plot += ", '" + data_file_2 + "' using 1:" + to_string( counter + 2 ) + " smooth csplines ls " + to_string( 10 ) + " notitle";
        }
    }
    
    plot += "\n";
    
    gp << plot;
}

