import numpy as np
import importlib
import recovery

def process_data(data):
    matrix = []

    matrix = np.array(list(data.values())).T
    n =matrix.shape[0]
    m =matrix.shape[1]
    k=3

    rec_time,iter,rec_mat = recovery.recovery(matrix,n,m,k)
    return rec_mat
