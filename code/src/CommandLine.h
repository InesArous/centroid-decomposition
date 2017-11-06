//
// 
//

#include <cstdint>
#include <string>
#include <iostream>

#define TEST_PREC 0
#define TEST_TIME 1
#define TEST_OUT 2
#define TEST_COMMON 3

using namespace std;

void printUsage()
{
    cout << "Usage: centroiddecomposition [args]" << endl
         << "-test p : precision test" << endl
         << "-test t : time test" << endl
         << "-test o : output L, R" << endl
         << "-test c : test math library (other parameters are not required)" << endl
         << "-n #    : # of rows value" << endl
         << "-m #    : # of column value" << endl
         << "-data M : data is a matrix (-in specifies a file)" << endl
         << "-in F   : [default=./data] read from file/folder F" << endl
         << "-out F  : [default=./out] write to file F" << endl;
}

int CommandLine(int argc, char *argv[],
                 uint64_t &n, uint64_t &m,
                 int &test_type, bool &matrix,
                 string &in, string &out)
{
    string temp;
    for (int i = 1; i < argc; ++i)
    {
        temp = argv[i];

        if (!temp.compare("-test"))
        {
            ++i;
            temp = argv[i];

            if (!temp.compare("t"))
            {
                test_type = TEST_TIME;
            }
            else if (!temp.compare("m"))
            {
                test_type = TEST_PREC;
            }
            else if (!temp.compare("o"))
            {
                test_type = TEST_OUT;
            }
            else if (!temp.compare("c"))
            {
                test_type = TEST_COMMON;
                n = m = 1;
                return 0;
            }
            else
            {
                cout << "Invalid -test argument, testing type not recognized" << endl;
                printUsage();
                return -1;
            }
        }
        else if (!temp.compare("-n"))
        {
            ++i;
            temp = argv[i];
            n = static_cast<uint64_t>(stoll(temp));
        }
        else if (!temp.compare("-m"))
        {
            ++i;
            temp = argv[i];
            m = static_cast<uint64_t>(stoll(temp));
        }
        else if (!temp.compare("-data"))
        {
            ++i;
            temp = argv[i];

            if (!temp.compare("M"))
            {
                matrix = true;
            }
            else
            {
                cout << "Invalid -data argument, data source not recognized" << endl;
                printUsage();
                return -1;
            }
        }
        else if (!temp.compare("-in"))
        {
            ++i;
            in = argv[i];
        }
        else if (!temp.compare("-out"))
        {
            ++i;
            out = argv[i];
        }
        else
        {
            cout << "Unrecognized CLI argument" << endl;
            printUsage();
            return -1;
        }
    }

    return 0;
}
