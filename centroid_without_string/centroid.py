import numpy as np
import centroid_decomposition
import time



matrix = []

for i in range(1000):
	x = np.array([float(element) for element in input().split(",")])

	matrix.append(x)

matrix = np.matrix(matrix)



ts1 = time.time()
matrix_l, matrix_r = centroid_decomposition.CD(matrix)
ts2 = time.time()
print(ts2 - ts1)

print(matrix_r)
