#include <CGAL/Triangle_2.h>
#include <CGAL/Triangulation_2.h>

#include "B_Poly.h"

using namespace std;

typedef K::Point_2 P2;
typedef Triangle_2<K> Tri;
typedef Triangulation_2<K> Triangulation;
typedef Poly::Vertex_iterator vertex_iterator;
typedef Triangulation::Finite_faces_iterator faces_iterator;

void Triangulate_Zones ( vector<B_Poly>& polys, int zone_limit, vector<vector<Tri>>& tris, vector<double>& cell_volume )
{
    tris.resize( zone_limit );
    
    for (int counter = 0; counter < polys.size(); ++counter)
    {
        vector<P2> vertices;
        
        for (vertex_iterator v = polys[counter].poly.vertices_begin(); v != polys[counter].poly.vertices_end(); ++v)
        {
            P2 p = P2( v->x(), v->y() );
            
            vertices.push_back( p );
        }
        
        Triangulation T( vertices.begin(), vertices.end() );
        
        for (faces_iterator c = T.Triangulation::finite_faces_begin(); c != T.Triangulation::finite_faces_end(); ++c)
        {
            Tri tri = T.triangle( c );
            
            tris[polys[counter].zone - 1].push_back( tri );
            
            cell_volume[polys[counter].zone - 1] += tri.area();
        }
    }
}
