//
// 
//

#include <string>
#include <iostream>
#include "Testing.h"
#include "LinearAlgebra/Basic"
#include "LinearAlgebra/CentroidDecomposition.h"

using namespace LinearAlgebra_Basic;
using namespace LinearAlgebra_Algorithms;

namespace Testing {

//
// Data sets
//

std::vector<std::vector<double>> data1 = {
        { -5.63, -1.58, -6.57 },
        { -3.37, -0.20, -3.92 },
        { -0.82,  4.07,  1.45 }

};

std::vector<std::vector<double>> data2 = {
        { 6, 1.5, -1 },
        { 2.3, 1, 0 }
};

std::vector<double> vector1 =
        { 1.4, -2.0, 0.0 };

//
// Test scenarios
//

void TestCD()
{
    Matrix *mx = new Matrix(Testing::data1);
    Matrix *mx2 = mx->copy();

    std::cout << "X =" << std::endl << mx->toString() << std::endl;

    CentroidDecomposition cd = CentroidDecomposition(mx2);

    cd.performDecomposition(false);

    Matrix &L = *cd.getLoad();
    Matrix &R = *cd.getRel();

    std::cout << "LOAD =" << std::endl << L.toString() << std::endl;

    std::cout << "REL =" << std::endl << R.toString() << std::endl;

    Matrix *reconstructedX = matrix_mult_A_BT(L, R);

    std::cout << "L * R^T: " << std::endl << reconstructedX->toString() << std::endl;

    *reconstructedX -= *mx;

    std::cout << "||X - (L * R^T)||_F = " << reconstructedX->normF() << std::endl;

    delete reconstructedX;
    delete mx;
    delete mx2;
}

void TestMult()
{
    Matrix *m1 = new Matrix(Testing::data1);
    Matrix *m2 = new Matrix(Testing::data2);
    Vector *v1 = new Vector(Testing::vector1);

    Matrix *resm;
    Vector *resv;

    Matrix *m_id = Matrix::identity(m2->dimensionM());

    // Test 1 - M2 * M1
    std::cout << "M1:" << std::endl << m1->toString() << std::endl;
    std::cout << "M2:" << std::endl << m2->toString() << std::endl;

    resm = (*m2) * (*m1);

    std::cout << "M2 * M1: " << std::endl << resm->toString() << std::endl;

    delete resm;

    // Test 2 - M2 * ID

    std::cout << "ID: " << std::endl << m_id->toString() << std::endl;

    resm = (*m2) * (*m_id);

    std::cout << "M2 * ID: " << std::endl << resm->toString() << std::endl;

    delete resm;

    // Test 3 - M1 * V1

    std::cout << "V1: " << std::endl << v1->toString() << std::endl;

    resv = (*m1) * (*v1);

    std::cout << "M1 * V1: " << std::endl << resv->toString() << std::endl;

    delete resv;

    // Test 3 - M2 * V1

    resv = (*m2) * (*v1);

    std::cout << "M2 * V1: " << std::endl << resv->toString() << std::endl;

    delete resv;

    // Test 4 - scalar & norm of v1

    std::cout << "<V1,V1> & ||V1||_2: " << std::endl << vector_dot(*v1, *v1)
            << " \t" << v1->norm2() << std::endl << std::endl;

    // Test 5.1 - normalize and print <,> & norm

    (void)v1->normalize();

    std::cout << "V1 [normalized]: " << std::endl << v1->toString() << std::endl;

    std::cout << "<V1,V1> & ||V1||_2: " << std::endl << vector_dot(*v1, *v1)
              << " \t" << v1->norm2() << std::endl << std::endl;

    // cleanup

    delete m1;
    delete m2;
    delete v1;
    delete m_id;
}

} //namespace Testing
