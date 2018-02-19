DROP FUNCTION set_working_directory;
CREATE FUNCTION set_working_directory(working_directory STRING) RETURNS BOOLEAN LANGUAGE PYTHON {
    import os

    return os.chdir(working_directory)

    return True
};

DROP FUNCTION get_working_directory;
CREATE FUNCTION get_working_directory() RETURNS STRING LANGUAGE PYTHON {
    import os

    return os.getcwd()
};

# Example queries
SELECT set_working_directory('/Users/rkoopmanschap/projects/centroid-decomposition/cd_monetdb');
SELECT get_working_directory();
