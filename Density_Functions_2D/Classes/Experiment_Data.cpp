#include "Experiment_Data.h"

Experiment_Data::Experiment_Data ( Experiment const& e )
{
    m_vertices.resize( e.motif_sizes.size() );
    m_edges.resize( e.motif_sizes.size() );
    m_polys.resize( e.motif_sizes.size() );
    m_perim.resize( e.motif_sizes.size() );
    m_time.resize( e.motif_sizes.size() );
    num_runs.resize( e.motif_sizes.size() );
    
    vector<double> vec_1( e.k[0], 0 );
    
    vector<pair<int, double>> vec_2( e.k.size() );
    
    for (int counter = 0; counter < vec_2.size(); ++counter)
    {
        vec_2[counter].first = e.k[counter];
        vec_2[counter].second = 0;
    }
    
    vector<double> vec_3( e.k.size(), 0 );
    
    for (int counter = 0; counter < e.motif_sizes.size(); ++counter)
    {
        m_vertices[counter].first = e.motif_sizes[counter];
        m_vertices[counter].second = vec_1;
        
        m_edges[counter].first = e.motif_sizes[counter];
        m_edges[counter].second = vec_1;
        
        m_polys[counter].first = e.motif_sizes[counter];
        m_polys[counter].second = vec_1;
        
        m_perim[counter].first = e.motif_sizes[counter];
        m_perim[counter].second = vec_1;
        
        m_time[counter].first = e.motif_sizes[counter];
        m_time[counter].second = vec_2;
        
        num_runs[counter] = vec_3;
    }
}

Experiment_Data::Experiment_Data(){}
Experiment_Data::~Experiment_Data(){}
