
DROP FUNCTION centroid_decomposition;
CREATE FUNCTION centroid_decomposition(x1 float, x2 float, x3 float, x4 float) RETURNS STRING LANGUAGE PYTHON {
    import sys
    import numpy as np
    import importlib
    
    
    working_directory = '/Volumes/GoogleDrive/My Drive/Ines/research/code/cd_recov'
    sys.path.append(working_directory)
    import recovery
    matrix = []

    matrix = np.array([x1,x2,x3,x4]).T
    n =matrix.shape[0]
    m =matrix.shape[1]
    k=3


    rec_time,iter,rec_mat = recovery.recovery(matrix,n,m,k)
    return str(rec_mat)
};




DROP TABLE time_series;
CREATE TABLE time_series(x1 float, x2 float, x3 float, x4 float);
COPY 20 RECORDS INTO time_series FROM '/Volumes/GoogleDrive/My Drive/Ines/research/code/cd_recov/sample.txt' USING DELIMITERS ',','\n';
SELECT centroid_decomposition(x1, x2, x3, x4) AS result FROM time_series;
