DROP FUNCTION centroid_decomposition;
CREATE FUNCTION centroid_decomposition(array STRING) RETURNS STRING LANGUAGE PYTHON {
    import sys
    import numpy as np
    import importlib

    working_directory = '/Users/rkoopmanschap/projects/centroid-decomposition/'
    sys.path.append(working_directory + "code")

    matrix_l, matrix_r = batch_cd.centroid_decomposition_wrapper(array, working_directory)
    return str(matrix_l) + str(matrix_r)
};


DROP TABLE time_series;
CREATE TABLE time_series(array STRING);
INSERT INTO time_series VALUES ('7.0 -5.0 10.0'), ('9.0 1.0 0.0'), ('-8.0 10.0 6.0'), ('9.0 10.0 -8.0'), ('3.0 -7.0 -2.0'), ('-8.0 10.0 9.0');
SELECT centroid_decomposition(array) AS result FROM time_series;
