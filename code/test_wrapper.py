import numpy as np
# from batch_cd import centroid_decomposition_wrapper
import batch_cd
import importlib
importlib.reload(batch_cd)

blob_array = np.array(["7.0 -5.0 10.0",
"9.0 1.0 0.0",
"-8.0 10.0 6.0",
"9.0 10.0 -8.0",
"3.0 -7.0 -2.0",
"-8.0 10.0 9.0"])

matrix_l, matrix_r = batch_cd.centroid_decomposition_wrapper(blob_array, '/Users/rkoopmanschap/projects/centroid-decomposition/')
print("matrix_l", matrix_l)
print("matrix_r", matrix_r)
