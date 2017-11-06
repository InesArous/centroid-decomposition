#include <iostream>
#include "Testing.h"
#include "MatrixReadWrite.h"
#include "Performance/Benchmark.h"

#include "CommandLine.h"

using namespace Testing;
using namespace std;

int main(int argc, char *argv[])
{
    int test_type = -1;
    uint64_t n = 0, m = 0;
    bool matrix = true;
    string in = "./data", out = "./out";

    int result = CommandLine(argc, argv, n, m, test_type, matrix, in, out);

    if (result != 0)
    {
        return result;
    }
    else if (n == 0 || m == 0 || test_type == -1) // mandatory args not supplied or are garbage
    {
        return -1;
    }

    LinearAlgebra_Basic::Matrix *mx = nullptr;
    if (test_type != TEST_COMMON)
    {
        double *data = MathIO::getMatrixByName(in, n, m);
        mx = new LinearAlgebra_Basic::Matrix(n, m, data);
    }
    if (test_type == TEST_TIME)
    {
        int64_t time = Benchmark::benchmarkCDtime(mx);
        MathIO::writeTime(out, n, m, time);

        cout << "TIME: " << time << endl;
    }
    else if (test_type == TEST_PREC)
    {
        double prec = Benchmark::benchmarkCDprecision(mx);
        MathIO::writePrecision(out, n, m, prec);
    }
    else if (test_type == TEST_COMMON)
    {
        TestMult();

        TestCD();
    }
    else //if (test_type == TEST_OUT)
    {
        auto matrices = Benchmark::benchmarkCDoutput(mx);

        MathIO::writeMatrix(out, "L", std::get<0>(*matrices));

        MathIO::writeMatrix(out, "R", std::get<1>(*matrices));
    }

    return 0;
}
