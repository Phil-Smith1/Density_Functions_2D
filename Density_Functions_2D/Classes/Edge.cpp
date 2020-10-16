#include "Edge.h"

Edge::Edge ( L2 const& l, P2 const& s, P2 const& e )
{
    line = l;
    startpt = s;
    endpt = e;
}

Edge::Edge(){}
Edge::~Edge(){}
