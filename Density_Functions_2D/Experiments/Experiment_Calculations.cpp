#include "Experiment.h"
#include "Experiment_Data.h"

void Experiment_Calculations ( bool time_vary_k, bool vary_k, Experiment const& e, Experiment_Data& e_d )
{
    if (time_vary_k)
    {
        for (int counter_1 = 1; counter_1 < e.motif_sizes.size(); ++counter_1)
        {
            for (int counter_2 = 0; counter_2 < e.k.size(); ++counter_2)
            {
                e_d.m_time[0].second[counter_2].second += e_d.m_time[counter_1].second[counter_2].second;
            }
            
            e_d.num_runs[0][0] += e_d.num_runs[counter_1][0];
        }
        
        for (int counter = 0; counter < e.k.size(); ++counter)
        {
            e_d.m_time[0].second[counter].second = 1000 * e_d.m_time[0].second[counter].second / (double)(e_d.num_runs[0][0] * CLOCKS_PER_SEC);
        }
    }
    
    else if (vary_k)
    {
        for (int counter_1 = 1; counter_1 < e.motif_sizes.size(); ++counter_1)
        {
            for (int counter_2 = 0; counter_2 < e.k[0]; ++counter_2)
            {
                e_d.m_vertices[0].second[counter_2] += e_d.m_vertices[counter_1].second[counter_2];
                e_d.m_edges[0].second[counter_2] += e_d.m_edges[counter_1].second[counter_2];
                e_d.m_polys[0].second[counter_2] += e_d.m_polys[counter_1].second[counter_2];
                e_d.m_perim[0].second[counter_2] += e_d.m_perim[counter_1].second[counter_2];
            }
            
            e_d.num_runs[0][0] += e_d.num_runs[counter_1][0];
        }
        
        for (int counter = 0; counter < e.k[0]; ++counter)
        {
            e_d.m_vertices[0].second[counter] = e_d.m_vertices[0].second[counter] / (double)e_d.num_runs[0][0];
            e_d.m_edges[0].second[counter] = e_d.m_edges[0].second[counter] / (double)e_d.num_runs[0][0];
            e_d.m_polys[0].second[counter] = e_d.m_polys[0].second[counter] / (double)e_d.num_runs[0][0];
            e_d.m_perim[0].second[counter] = e_d.m_perim[0].second[counter] / (double)e_d.num_runs[0][0];
        }
    }
    
    else
    {
        for (int counter_1 = 0; counter_1 < e.motif_sizes.size(); ++counter_1)
        {
            for (int counter_2 = 0; counter_2 < e.k.size(); ++counter_2)
            {
                e_d.m_time[counter_1].second[counter_2].second = 1000 * e_d.m_time[counter_1].second[counter_2].second / (double)(e_d.num_runs[counter_1][0] * CLOCKS_PER_SEC);
            }
            
            for (int counter_2 = 0; counter_2 < e.k[0]; ++counter_2)
            {
                e_d.m_vertices[counter_1].second[counter_2] = e_d.m_vertices[counter_1].second[counter_2] / (double)(e_d.num_runs[counter_1][0]);
                e_d.m_edges[counter_1].second[counter_2] = e_d.m_edges[counter_1].second[counter_2] / (double)(e_d.num_runs[counter_1][0]);
                e_d.m_polys[counter_1].second[counter_2] = e_d.m_polys[counter_1].second[counter_2] / (double)(e_d.num_runs[counter_1][0]);
                e_d.m_perim[counter_1].second[counter_2] = e_d.m_perim[counter_1].second[counter_2] / (double)(e_d.num_runs[counter_1][0]);
            }
        }
    }
}
