import numpy as np
import cd_ssv

def process_data(data):
	matrix = np.array(list(data.values())).T
	n = matrix.shape[0]
	m = matrix.shape[1]
	matrix_l, matrix_r = cd_ssv.CD(matrix, n, m)

	return matrix_r
