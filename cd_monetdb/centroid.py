import numpy as np
import cd_ssv
import time



input_matrix=np.loadtxt('./climate1.csv',delimiter=',')
n =input_matrix.shape[0]
m =input_matrix.shape[1]


ts1 = time.time()
matrix_l, matrix_r = cd_ssv.CD(input_matrix,n,m)
ts2 = time.time()
print(ts2 - ts1)

print(matrix_r)
