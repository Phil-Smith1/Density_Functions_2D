#include <iostream>

using namespace std;

void Print_Info ( clock_t const& start_code_runtime, chrono::time_point<chrono::steady_clock>const& start_absolute_time )
{
    clock_t end_code_runtime = clock();
    
    double runtime = (end_code_runtime - start_code_runtime) / (double)CLOCKS_PER_SEC;
    auto absolute_time = chrono::duration_cast<chrono::milliseconds>( chrono::steady_clock::now() - start_absolute_time );
    
    cout << endl;
    cout << "Code runtime: " << runtime << "s." << endl;
    cout << "Elapsed time: " << absolute_time.count() / (double)1000 << "s." << endl << endl;
}
