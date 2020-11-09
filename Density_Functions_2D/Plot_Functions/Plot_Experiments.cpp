#include "Plot_Experiment_Zone.h"
#include "Plot_Experiment_Motif.h"

void Plot_Experiments ( Framework_Parameters const& f_p, int zone_limit )
{
    if (f_p.time_vary_k) Plot_Experiment_Zone( f_p, "Runtime", "Runtime (ms)", "006400" );
    
    if (f_p.time_vary_m) Plot_Experiment_Motif( f_p, "Runtime", "Runtime (ms)", "006400" );
    
    if (f_p.vary_k)
    {
        Plot_Experiment_Zone( f_p, "Vertices", "Number of Vertices", "ff0000" );
        Plot_Experiment_Zone( f_p, "Edges", "Number of Edges", "ffa500" );
        Plot_Experiment_Zone( f_p, "Polys", "Number of Polygons", "0d61ec" );
        Plot_Experiment_Zone( f_p, "Perim", "Perimeter Length", "800080" );
    }
    
    if (f_p.vary_m)
    {
        Plot_Experiment_Motif( f_p, "Vertices", "Number of Vertices", "ff0000" );
        Plot_Experiment_Motif( f_p, "Edges", "Number of Edges", "ffa500" );
        Plot_Experiment_Motif( f_p, "Polys", "Number of Polygons", "0d61ec" );
        Plot_Experiment_Motif( f_p, "Perim", "Perimeter Length", "800080" );
    }
    
    //Plot_Perim( f_p, zone_limit );
}
