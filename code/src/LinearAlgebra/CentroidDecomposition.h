//
// 
//

#include "Basic"

#ifndef CENTROIDDECOMPOSITION_CENTROIDDECOMPOSITION_H
#define CENTROIDDECOMPOSITION_CENTROIDDECOMPOSITION_H

namespace LinearAlgebra_Algorithms {

class CentroidDecomposition {
    //
    // Data
    //
  private:
    LinearAlgebra_Basic::Matrix *Src;
    LinearAlgebra_Basic::Matrix *Load = nullptr;
    LinearAlgebra_Basic::Matrix *Rel = nullptr;

    //
    // Constructors & desctructors
    //
  public:
    CentroidDecomposition(LinearAlgebra_Basic::Matrix *mx);
    ~CentroidDecomposition();

    //
    // API
    //
  public:
    LinearAlgebra_Basic::Matrix *getLoad();
    LinearAlgebra_Basic::Matrix *getRel();

    void performDecomposition(bool incremental);

    //
    // Algorithm
    //
  private:
    LinearAlgebra_Basic::Vector *findSSV(LinearAlgebra_Basic::Matrix *mx);
    LinearAlgebra_Basic::Vector *findIncrementalSSV(LinearAlgebra_Basic::Matrix *mx);
    LinearAlgebra_Basic::Vector *createBaseSignVector();
};

} // namespace LinearAlgebra_Algorithms

#endif //CENTROIDDECOMPOSITION_CENTROIDDECOMPOSITION_H
