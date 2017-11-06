//
// 
//

#include <iostream>
#include <fstream>
#include <dirent.h>
#include "MatrixReadWrite.h"

using namespace std;

namespace MathIO {

//
// Reading
//
double *getMatrixByName(string name, uint64_t n, uint64_t m)
{
    ifstream file ( name );
    string buffer;

    if (!file.is_open())
    {
        std::cout << "Can't open file " << name << std::endl;
        return nullptr;
    }

    double *data = static_cast<double *>(malloc(n * m * sizeof(*data)));

    uint64_t i = 0;

    while (!file.eof() && i < n)
    {
        getline(file, buffer);

        size_t pos = 0;

        string temp;
        for (uint64_t j = 0; j < m; ++j)
        {
            // TBA
            size_t newpos;
            newpos = buffer.find(' ', pos + 1);

            newpos = newpos == string::npos ? buffer.length() : newpos;

            temp = buffer.substr(pos, newpos - pos - 1);

            *(data + i * m + j) = stod(temp);

            pos = newpos + 1;
        }

        ++i;
    }

    file.close();

    return data;
}

void writeTime(std::string out, uint64_t n, uint64_t m, int64_t time)
{
    ofstream out_file;
    out_file.open (out, ios::out | ios::app);

    out_file << n << "\t" << m << "\t" << time << endl;

    out_file.close();
}

void writePrecision(std::string out, uint64_t n, uint64_t m, double precision)
{
    ofstream out_file;
    out_file.open (out, ios::out | ios::app);

    out_file << "PREC: " << n << "\t" << m << "\t" << precision << endl;

    out_file.close();
}

void writeMatrix(std::string out, std::string matrix, std::string &matrixContent)
{
    out.append(".");
    out.append(matrix);
    ofstream out_file;
    out_file.open (out, ios::out | ios::app);

    out_file << "MATRIX " << matrix <<": " << endl << matrixContent << endl;

    out_file.close();
}

} // namespace MathIO
