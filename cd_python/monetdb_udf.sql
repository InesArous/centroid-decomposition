DROP FUNCTION centroid_decomposition;
CREATE FUNCTION centroid_decomposition(array STRING) RETURNS STRING LANGUAGE PYTHON {
    import sys
    import numpy as np
    import centroid_decomposition

    sys.path.append('/Users/rkoopmanschap/projects/cd_python/')

    matrix = []
    for row in array:
        matrix.append([float(element) for element in row.split(' ')])

    matrix = np.matrix(matrix)

    matrix_l, matrix_r = centroid_decomposition.centroid_decomposition(matrix)
    return str(matrix_l) + str(matrix_r)
};

DROP TABLE time_series;
CREATE TABLE time_series(array STRING);
INSERT INTO time_series VALUES ('7.0 -5.0 10.0'), ('9.0 1.0 0.0'), ('-8.0 10.0 6.0'), ('9.0 10.0 -8.0'), ('3.0 -7.0 -2.0'), ('-8.0 10.0 9.0');
SELECT centroid_decomposition(array) AS result FROM time_series;
