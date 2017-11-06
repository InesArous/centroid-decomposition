//
// 
//

#ifndef CENTROIDDECOMPOSITION_BENCHMARK_H
#define CENTROIDDECOMPOSITION_BENCHMARK_H

#include <cstdint>
#include <tuple>
#include "../LinearAlgebra/Basic"

namespace Benchmark {

int64_t benchmarkCDtime(LinearAlgebra_Basic::Matrix *mx);

double benchmarkCDprecision(LinearAlgebra_Basic::Matrix *mx);

std::tuple<std::string, std::string> *benchmarkCDoutput(LinearAlgebra_Basic::Matrix *mx);

} // namespace Benchmark

#endif //CENTROIDDECOMPOSITION_BENCHMARK_H
