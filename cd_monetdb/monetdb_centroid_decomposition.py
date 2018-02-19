import numpy as np
import cd_ssv
from collections import OrderedDict

# initialize parameters
def init_params():
	return OrderedDict({
		'x1': [1,2,3],
		'x2': [3,4,5]
	})

if('parameters' not in locals()):
	parameters = init_params()

# code
matrix = np.array(list(parameters.values())).T
n = matrix.shape[0]
m = matrix.shape[1]
matrix_l, matrix_r = cd_ssv.CD(matrix, n, m)

# create results
result = str(matrix_r)
print(matrix_r)
