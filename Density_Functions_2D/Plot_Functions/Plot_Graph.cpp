#include "Plot_Variance.h"
#include "Plot_Densigram.h"
#include "Plot_Graph_Standard.h"

void Plot_Graph ( Framework_Parameters const& f_p, Input& input )
{
    if (f_p.variance) Plot_Variance( f_p, input );
    
    if (f_p.densigram) Plot_Densigram( f_p, input );
    
    else Plot_Graph_Standard( f_p, input );
}
