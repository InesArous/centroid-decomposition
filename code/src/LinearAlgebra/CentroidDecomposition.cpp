//
// 
//

#include <cmath>
#include "CentroidDecomposition.h"

using namespace LinearAlgebra_Basic;

namespace LinearAlgebra_Algorithms {
//
// CentroidDecomposition constructors & desctructors
//

CentroidDecomposition::CentroidDecomposition(LinearAlgebra_Basic::Matrix *mx)
{
    Load = new Matrix(mx->dimensionN(), mx->dimensionM(), false);
    Rel =  new Matrix(mx->dimensionM(), mx->dimensionM(), false);

    Src = mx;
}

CentroidDecomposition::~CentroidDecomposition()
{
    delete Load;
    delete Rel;
}

//
// CentroidDecomposition API
//

Matrix *CentroidDecomposition::getLoad()
{
    return Load;
}

Matrix *CentroidDecomposition::getRel()
{
    return Rel;
}

void CentroidDecomposition::performDecomposition(bool incremental)
{
    Matrix *Li_RiT; // container for L_i * R_i^T

    Matrix *X = Src;

    Vector *Z;
    Vector *Rel_i;
    Vector *Load_i;

    for (uint64_t i = 0; i < X->dimensionM(); i++)
    {
        if (incremental)
        {
            Z = findIncrementalSSV(X);
        }
        else
        {
            Z = findSSV(X);
        }

        // C_*i = X^T * Z
        Rel_i = (*X) ^ (*Z);

        // R_*i = C_*i / ||C_*i||
        (void)Rel_i->normalize();

        // R = Append(R, R_*i)
        (void)Rel->insertVectorAtColumn(i, Rel_i);

        // L_*i = X * R
        Load_i = (*X) * (*Rel_i);

        // L = Append(L, L_*i)
        (void)Load->insertVectorAtColumn(i, Load_i);

        // X := X - L_*i * R_*i^T
        Li_RiT = vector_outer(*Load_i, *Rel_i);
        *X -= *Li_RiT;

        delete Li_RiT;
        delete Z;

        delete Rel_i;
        delete Load_i;
    }

    if (incremental) { delete X; }
}

//
// Algorithm
//
Vector *CentroidDecomposition::findSSV(Matrix *mx)
{
    // Scalable Sign Vector
    int64_t pos = -1;
    double val = 0.0;

    Vector *Z_vec = createBaseSignVector();
    Vector &Z = *Z_vec;  // get a reference

    Vector *S = new Vector(Src->dimensionM(), false);
    Vector *V = new Vector(Src->dimensionN(), false);

    // pre-process rows of X
    std::vector<Vector *> x_ = std::vector<Vector *>();
    std::vector<double> XXT_ = std::vector<double>();

    for (uint64_t i = 0; i < mx->dimensionN(); ++i)
    {
        x_.push_back(mx->extractRowVector(i, false));
        XXT_.push_back(vector_dot(*x_[i], *x_[i]));
    }

    // main loop
    do
    {
        // change sign
        if (pos != -1) { Z[pos] = Z[pos] * (-1.0); }

        // Determine S, V

        // S = Sum(1:n) { z_i * (X_i* ^ T) }

        // i = 0
        {
            for (uint64_t j = 0; j < S->dimension(); ++j)
            {
                (*S)[j] = (*x_[0])[j] * Z[0];
            }
        }

        for (uint64_t i = 1; i < mx->dimensionN(); ++i)
        {
            for (uint64_t j = 0; j < S->dimension(); ++j)
            {
                (*S)[j] += (*x_[i])[j] * Z[i];
            }
        }



        // v_i = z_i * (z_i * X_i* * S - X_i* * (X_i*)^T)
        for (uint64_t i = 0; i < mx->dimensionN(); ++i)
        {
            (*V)[i] = Z[i] * (
                    Z[i] * vector_dot(*x_[i], *S) - XXT_[i]
            );
        }

        // Search next element
        val = 0.0; pos = -1;

        for (uint64_t i = 0; i < mx->dimensionN(); ++i)
        {
            if (Z[i] * (*V)[i] < 0)
            {
                if (fabs((*V)[i]) > val)
                {
                    val = fabs((*V)[i]);
                    pos = i;
                }
            }
        }

    } while (pos != -1);

    // both are reused inside the loop and never deconstructed in the process
    delete S;
    delete V;

    for (uint64_t i = 0; i < mx->dimensionN(); ++i)
    {
        delete x_.at(i);
    }

    return Z_vec;
}

LinearAlgebra_Basic::Vector *CentroidDecomposition::findIncrementalSSV(LinearAlgebra_Basic::Matrix *mx)
{
    // Scalable Sign Vector
    int64_t pos = -1;
    double val = 0.0;

    Vector *Z_vec = createBaseSignVector();
    Vector &Z = *Z_vec;  // get a reference

    Vector *S = new Vector(Src->dimensionM(), false);
    Vector *V = new Vector(Src->dimensionN(), false);

    // pre-process rows of X
    std::vector<Vector *> x_ = std::vector<Vector *>();
    std::vector<double> XXT_ = std::vector<double>();

    for (uint64_t i = 0; i < mx->dimensionN(); ++i)
    {
        x_.push_back(mx->extractRowVector(i, false));
        XXT_.push_back(vector_dot(*x_[i], *x_[i]));
    }


    // ITERATION #1

    // S = Sum(1:n) { z_i * (X_i* ^ T) }

    // i = 0
    {
        for (uint64_t j = 0; j < S->dimension(); ++j)
        {
            (*S)[j] = (*x_[0])[j] * Z[0];
        }
    }

    for (uint64_t i = 1; i < mx->dimensionN(); ++i)
    {
        for (uint64_t j = 0; j < S->dimension(); ++j)
        {
            (*S)[j] += (*x_[i])[j] * Z[i];
        }
    }



    // v_i = z_i * (z_i * X_i* * S - X_i* * (X_i*)^T)
    for (uint64_t i = 0; i < mx->dimensionN(); ++i)
    {
        (*V)[i] = Z[i] * (
                Z[i] * vector_dot(*x_[i], *S) - XXT_[i]
        );
    }

    // Search next element
    val = 0.0; pos = -1;

    for (uint64_t i = 0; i < mx->dimensionN(); ++i)
    {
        if (Z[i] * (*V)[i] < 0)
        {
            if (fabs((*V)[i]) > val)
            {
                val = fabs((*V)[i]);
                pos = i;
            }
        }
    }

    // ITERATIONS 2+

    // main loop
    while (pos != -1)
    {
        // change sign
        Z[pos] = Z[pos] * (-1.0);

        // Determine V_k+1 from V_k

        for (uint64_t i = 0; i < mx->dimensionN(); ++i)
        {
            (*V)[i] -= 2 * (i == static_cast<uint64_t>(pos) ? XXT_[i] : vector_dot(*x_[i], *x_[pos]) ); //save one dot product calc
        }

        // Search next element to flip
        val = 0.0; pos = -1;

        for (uint64_t i = 0; i < mx->dimensionN(); ++i)
        {
            if (Z[i] * (*V)[i] < 0)
            {
                if (fabs((*V)[i]) > val)
                {
                    val = fabs((*V)[i]);
                    pos = i;
                }
            }
        }

    }

    // both are reused inside the loop and never deconstructed in the process
    delete S;
    delete V;

    for (uint64_t i = 0; i < mx->dimensionN(); ++i)
    {
        delete x_.at(i);
    }


    return Z_vec;
}

LinearAlgebra_Basic::Vector *CentroidDecomposition::createBaseSignVector()
{
    Vector *signV = new Vector(Src->dimensionN(), false);
    for (uint64_t j = 0; j < signV->dimension(); j++)
    {
        (*signV)[j] = 1.0;
    }
    return signV;
}


} // namespace LinearAlgebra_Algorithms
