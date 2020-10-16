#include "Experiment_Data.h"

Experiment_Data::Experiment_Data ( Experiment const& e )
{
    m_vertices.resize( e.motif_sizes.size() );
    m_edges.resize( e.motif_sizes.size() );
    m_polys.resize( e.motif_sizes.size() );
    m_perim.resize( e.motif_sizes.size() );
    m_time.resize( e.motif_sizes.size() );
    num_runs.resize( e.motif_sizes.size() );
    
    vector<double> vec( e.k[0], 0 );
    
    vector<pair<int, double>> vec2( e.k.size() );
    for (int counter = 0; counter < vec2.size(); ++counter)
    {
        vec2[counter].first = e.k[counter];
        vec2[counter].second = 0;
    }
    
    vector<double> vec3( e.k.size(), 0 );
    
    for (int counter = 0; counter < e.motif_sizes.size(); ++counter)
    {
        m_vertices[counter].first = e.motif_sizes[counter];
        m_vertices[counter].second = vec;
        
        m_edges[counter].first = e.motif_sizes[counter];
        m_edges[counter].second = vec;
        
        m_polys[counter].first = e.motif_sizes[counter];
        m_polys[counter].second = vec;
        
        m_perim[counter].first = e.motif_sizes[counter];
        m_perim[counter].second = vec;
        
        m_time[counter].first = e.motif_sizes[counter];
        m_time[counter].second = vec2;
        
        num_runs[counter] = vec3;
    }
}

Experiment_Data::Experiment_Data(){}
Experiment_Data::~Experiment_Data(){}
