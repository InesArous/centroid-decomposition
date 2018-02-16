#DROP FUNCTION centroid_decomposition;
#CREATE FUNCTION centroid_decomposition(array STRING) RETURNS STRING LANGUAGE PYTHON {
#    import sys
#    import numpy as np
#    import importlib
    
    
#    working_directory = '/Users/rkoopmanschap/projects/centroid-decomposition2'
#    sys.path.append(working_directory)
#    import centroid_decomposition
#    matrix = []
#    for row in array:
#        matrix.append([float(element) for element in row.split(',')])

#    matrix = np.matrix(matrix)

#    matrix_l, matrix_r = centroid_decomposition.CD(matrix)
#    return str(matrix_r)
#};

#DROP TABLE time_series;
#CREATE TABLE time_series(array BLOB);
#INSERT INTO time_series VALUES ('7.0 -5.0 10.0'), ('9.0 1.0 0.0'), ('-8.0 10.0 6.0'), ('9.0 10.0 -8.0'), ('3.0 -7.0 -2.0'), ('-8.0 10.0 9.0');
#COPY 1000 RECORDS INTO time_series FROM '/Users/rkoopmanschap/projects/centroid-decomposition2/climate.csv' USING DELIMITERS '|','\n';
#SELECT centroid_decomposition(array) AS result FROM time_series;










DROP FUNCTION centroid_decomposition;
CREATE FUNCTION centroid_decomposition(x1 float, x2 float, x3 float, x4 float) RETURNS STRING LANGUAGE PYTHON {
    import sys
    import numpy as np
    import importlib
    
    
    working_directory = '/Users/rkoopmanschap/projects/centroid-decomposition2'
    sys.path.append(working_directory)
    import centroid_decomposition
    matrix = []

    matrix = np.matrix([x1,x2,x3,x4]).T

    matrix_l, matrix_r = centroid_decomposition.CD(matrix)
    return str(matrix_r)
};




DROP TABLE time_series;
CREATE TABLE time_series(x1 float, x2 float, x3 float, x4 float);
#INSERT INTO time_series VALUES ('7.0 -5.0 10.0'), ('9.0 1.0 0.0'), ('-8.0 10.0 6.0'), ('9.0 10.0 -8.0'), ('3.0 -7.0 -2.0'), ('-8.0 10.0 9.0');
COPY 1000 RECORDS INTO time_series FROM '/Users/rkoopmanschap/projects/centroid-decomposition2/climate.csv' USING DELIMITERS ',','\n';
SELECT centroid_decomposition(x1, x2, x3, x4) AS result FROM time_series;
