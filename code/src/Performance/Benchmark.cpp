//
// 
//

#include <chrono>
#include <sstream>
#include <fstream>
#include <iostream>
#include "Benchmark.h"
#include "../LinearAlgebra/CentroidDecomposition.h"

using namespace LinearAlgebra_Basic;
using namespace LinearAlgebra_Algorithms;

namespace Benchmark {

int64_t benchmarkCDtime(Matrix *mx)
{
    CentroidDecomposition cd = CentroidDecomposition(mx);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    cd.performDecomposition(true);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

}
    

double benchmarkCDprecision(Matrix *mx)
{
    Matrix *mx_c = mx->copy();
    CentroidDecomposition cd = CentroidDecomposition(mx);

    cd.performDecomposition(true);

    Matrix &L = *cd.getLoad();
    Matrix &R = *cd.getRel();

    Matrix *reconstructedX = matrix_mult_A_BT(L, R);

    *reconstructedX -= *mx_c;

    return reconstructedX->normF();
}

std::tuple<std::string, std::string> *benchmarkCDoutput(LinearAlgebra_Basic::Matrix *mx)
{
    CentroidDecomposition cd = CentroidDecomposition(mx);

    cd.performDecomposition(true);

    auto matrices = new std::tuple<std::string, std::string>(cd.getLoad()->toString(), cd.getRel()->toString());

    return matrices;
}

} // namespace Benchmark
