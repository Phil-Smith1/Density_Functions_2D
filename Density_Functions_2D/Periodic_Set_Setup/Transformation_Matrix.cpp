#include <string>
#include <vector>
#include <cmath>

using namespace std;

#ifndef Pi
#define Pi
const double PI = 3.14159265359;
#endif

void Transformation_Matrix ( vector<pair<string, double>>const& cell_shape, double ** matrix )
{
    matrix[0][0] = cell_shape[0].second;
    matrix[0][1] = cell_shape[1].second * cos( PI * cell_shape[2].second / (double)180 );
    matrix[1][0] = 0;
    matrix[1][1] = cell_shape[1].second * sin( PI * cell_shape[2].second / (double)180 );
}
