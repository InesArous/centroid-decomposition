import sys
import numpy as np
import importlib

working_directory = '/Users/rkoopmanschap/projects/centroid-decomposition2'
sys.path.append(working_directory)
import centroid_decomposition
matrix = []

matrix = np.matrix(list(parameters.values())).T

matrix_l, matrix_r = centroid_decomposition.CD(matrix)

return str(matrix_r)
