//
// 
//

#ifndef CENTROIDDECOMPOSITION_MATRIXREADWRITE_H
#define CENTROIDDECOMPOSITION_MATRIXREADWRITE_H

#include <string>
#include "LinearAlgebra/Basic"

namespace MathIO {

double *getMatrixByName(std::string name, uint64_t n, uint64_t m);

void writeTime(std::string out, uint64_t n, uint64_t m, int64_t time);
void writePrecision(std::string out, uint64_t n, uint64_t m, double precision);
void writeMatrix(std::string out, std::string matrix, std::string &matrixContent);

} //namespace MathIO

#endif //CENTROIDDECOMPOSITION_MATRIXREADWRITE_H
