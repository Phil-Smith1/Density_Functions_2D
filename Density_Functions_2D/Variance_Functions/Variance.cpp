#include <vector>

using namespace std;

#ifndef Pi
#define Pi
const double PI = 3.14159265359;
#endif

double Variance ( vector<double> results )
{
    double s = results[0];
    double num_functions = (int)results.size() - 1;
    
    double first_sum = 0;
    double second_sum = 0;
    
    for (int counter = 0; counter < num_functions; ++counter)
    {
        first_sum += (counter + 1) * (counter + 1) * results[counter + 1];
        
        second_sum += (counter + 1) * results[counter + 1];
    }
    
    double variance = first_sum - second_sum * second_sum;
    
    variance = variance / (double)((4 / (double)3) * PI * s * s * s);
    
    return variance;
}
