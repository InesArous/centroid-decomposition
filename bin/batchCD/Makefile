all:
	$(CC) -x c++ -O3 -o CentroidDecomposition -Wall -Wextra -Werror -pedantic -std=c++14  main.cpp LinearAlgebra/Vector.cpp LinearAlgebra/Vector.h LinearAlgebra/Matrix.cpp LinearAlgebra/Matrix.h Testing.cpp Testing.h LinearAlgebra/CentroidDecomposition.cpp LinearAlgebra/CentroidDecomposition.h MatrixReadWrite.cpp MatrixReadWrite.h Performance/Benchmark.cpp Performance/Benchmark.h -lstdc++ -lpthread 

clean:
	rm CentroidDecomposition