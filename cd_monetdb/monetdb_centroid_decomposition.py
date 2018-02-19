import numpy as np
import cd_ssv

# parameters = {
# 	'x1': [1,2,3],
# 	'x2': [3,4,5]
# }

matrix = np.array(list(parameters.values())).T
n = matrix.shape[0]
m = matrix.shape[1]
matrix_l, matrix_r = cd_ssv.CD(matrix, n, m)

return str(matrix_r)
# print(str(matrix_r))
