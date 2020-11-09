#include "Framework_Parameters.h"
#include "Experiment_Data.h"

#include <fstream>

void Write_Experiment_Data ( Framework_Parameters const& f_p, Experiment_Data const& experiment_data )
{
    if (f_p.time_vary_k)
    {
        ofstream ofs( f_p.output_dir + "Experiments/Data/Runtime.txt" );
        
        ofs << setprecision( 10 ) << experiment_data.m_time[0].second[0].first << " " << experiment_data.m_time[0].second[0].second;
        
        for (int counter = 1; counter < experiment_data.m_time[0].second.size(); ++counter)
        {
            ofs << endl;
            ofs << setprecision( 10 ) << experiment_data.m_time[0].second[counter].first << " " << experiment_data.m_time[0].second[counter].second;
        }
        
        ofs.close();
    }
    
    if (f_p.time_vary_m)
    {
        ofstream ofs( f_p.output_dir + "Experiments/Data/Runtime.txt" );
        
        ofs << setprecision( 10 ) << experiment_data.m_time[0].first << " " << experiment_data.m_time[0].second[0].second;
        
        for (int counter = 1; counter < experiment_data.m_time.size(); ++counter)
        {
            ofs << endl;
            ofs << setprecision( 10 ) << experiment_data.m_time[counter].first << " " << experiment_data.m_time[counter].second[0].second;
        }
        
        ofs.close();
    }
        
    if (f_p.vary_k)
    {
        ofstream ofs_1( f_p.output_dir + "Experiments/Data/Vertices.txt" );
        
        ofs_1 << setprecision( 10 ) << 1 << " " << experiment_data.m_vertices[0].second[0];
        
        for (int counter = 1; counter < experiment_data.m_vertices[0].second.size(); ++counter)
        {
            ofs_1 << endl;
            ofs_1 << setprecision( 10 ) << counter + 1 << " " << experiment_data.m_vertices[0].second[counter];
        }
        
        ofs_1.close();
        
        ofstream ofs_2( f_p.output_dir + "Experiments/Data/Edges.txt" );
        
        ofs_2 << setprecision( 10 ) << 1 << " " << experiment_data.m_edges[0].second[0];
        
        for (int counter = 1; counter < experiment_data.m_edges[0].second.size(); ++counter)
        {
            ofs_2 << endl;
            ofs_2 << setprecision( 10 ) << counter + 1 << " " << experiment_data.m_edges[0].second[counter];
        }
        
        ofs_2.close();
        
        ofstream ofs_3( f_p.output_dir + "Experiments/Data/Polys.txt" );
        
        ofs_3 << setprecision( 10 ) << 1 << " " << experiment_data.m_polys[0].second[0];
        
        for (int counter = 1; counter < experiment_data.m_polys[0].second.size(); ++counter)
        {
            ofs_3 << endl;
            ofs_3 << setprecision( 10 ) << counter + 1 << " " << experiment_data.m_polys[0].second[counter];
        }
        
        ofs_3.close();
        
        ofstream ofs_4( f_p.output_dir + "Experiments/Data/Perim.txt" );
        
        ofs_4 << setprecision( 10 ) << 1 << " " << experiment_data.m_perim[0].second[0];
        
        for (int counter = 1; counter < experiment_data.m_perim[0].second.size(); ++counter)
        {
            ofs_4 << endl;
            ofs_4 << setprecision( 10 ) << counter + 1 << " " << experiment_data.m_perim[0].second[counter];
        }
        
        ofs_4.close();
    }
    
    if (f_p.vary_m)
    {
        vector<double> total_vertices( experiment_data.m_vertices.size(), 0 );
        vector<double> total_edges( experiment_data.m_vertices.size(), 0 );
        vector<double> total_polys( experiment_data.m_vertices.size(), 0 );
        vector<double> total_length( experiment_data.m_vertices.size(), 0 );
        
        for (int counter_1 = 0; counter_1 < experiment_data.m_vertices.size(); ++counter_1)
        {
            for (int counter_2 = 0; counter_2 < experiment_data.m_vertices[counter_1].second.size(); ++counter_2)
            {
                total_vertices[counter_1] += experiment_data.m_vertices[counter_1].second[counter_2];
                total_edges[counter_1] += experiment_data.m_edges[counter_1].second[counter_2];
                total_polys[counter_1] += experiment_data.m_polys[counter_1].second[counter_2];
                total_length[counter_1] += experiment_data.m_perim[counter_1].second[counter_2];
            }
        }
        
        ofstream ofs_1( f_p.output_dir + "Experiments/Data/Vertices.txt" );
        
        ofs_1 << setprecision( 10 ) << experiment_data.m_vertices[0].first << " " << total_vertices[0];
        
        for (int counter = 1; counter < experiment_data.m_vertices.size(); ++counter)
        {
            ofs_1 << endl;
            ofs_1 << setprecision( 10 ) << experiment_data.m_vertices[counter].first << " " << total_vertices[counter];
        }
        
        ofs_1.close();
        
        ofstream ofs_2( f_p.output_dir + "Experiments/Data/Edges.txt" );
        
        ofs_2 << setprecision( 10 ) << experiment_data.m_edges[0].first << " " << total_edges[0];
        
        for (int counter = 1; counter < experiment_data.m_edges.size(); ++counter)
        {
            ofs_2 << endl;
            ofs_2 << setprecision( 10 ) << experiment_data.m_edges[counter].first << " " << total_edges[counter];
        }
        
        ofs_2.close();
        
        ofstream ofs_3( f_p.output_dir + "Experiments/Data/Polys.txt" );
        
        ofs_3 << setprecision( 10 ) << experiment_data.m_polys[0].first << " " << total_polys[0];
        
        for (int counter = 1; counter < experiment_data.m_polys.size(); ++counter)
        {
            ofs_3 << endl;
            ofs_3 << setprecision( 10 ) << experiment_data.m_polys[counter].first << " " << total_polys[counter];
        }
        
        ofs_3.close();
        
        ofstream ofs_4( f_p.output_dir + "Experiments/Data/Perim.txt" );
        
        ofs_4 << setprecision( 10 ) << experiment_data.m_perim[0].first << " " << total_length[0];
        
        for (int counter = 1; counter < experiment_data.m_perim.size(); ++counter)
        {
            ofs_4 << endl;
            ofs_4 << setprecision( 10 ) << experiment_data.m_perim[counter].first << " " << total_length[counter];
        }
        
        ofs_4.close();
    }
}
