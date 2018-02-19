import numpy as np
import centroid_decomposition

matrix = []
matrix = np.matrix(list(parameters.values())).T
matrix_l, matrix_r = centroid_decomposition.CD(matrix)
return str(matrix_r)
