CREATE OR REPLACE FUNCTION set_working_directory(working_directory STRING) RETURNS BOOLEAN LANGUAGE PYTHON {
    import os

    os.chdir(working_directory)

    return True
};

CREATE OR REPLACE FUNCTION get_working_directory() RETURNS STRING LANGUAGE PYTHON {
    import os

    return os.getcwd()
};

CREATE OR REPLACE FUNCTION call_dynamic_udf(file STRING, table_name STRING, columns STRING) RETURNS STRING LANGUAGE PYTHON {
    import numpy as np

    # convert params to string    
    columns = str(columns)
    table_name = str(table_name)
    columns_array = columns.split(',')

    # add the types
    results = _conn.execute('SELECT c.name, c.type FROM sys.columns AS c JOIN sys.tables AS t ON t.id = c.table_id WHERE t.name = \'' + table_name + '\';')
    types = results['type'].tolist()
    names = results['name'].tolist()

    column_parameter_list = []
    for i, column in enumerate(columns_array):
        column_name = column.strip()
        column_index = names.index(column_name)
        column_type = types[column_index]
        column_parameter_list.append('c' + str(i) + ' ' + column_type)

    # create function creation parameters
    column_parameters = ','.join(column_parameter_list)
    number_of_columns = len(columns_array)

    # get function code
    default_function_code = """
from collections import OrderedDict
parameters = OrderedDict()
original_column_names = original_column_names.split(',')
for i in range(number_of_columns):
    exec('parameters[original_column_names[i]] = c' + str(i)) in locals()

"""
    with open(file, "r") as myfile:
        data = myfile.read()
    function_code = data

    # create the new UDF
    create_query = 'CREATE FUNCTION auto_generated_udf(number_of_columns INTEGER, original_column_names STRING, ' + column_parameters + ') RETURNS ' + 'STRING' + ' LANGUAGE PYTHON {\n' + default_function_code + function_code + '\nreturn result};'
    print("create_query = ", create_query)
    auto_generated_udf_already_exists = _conn.execute('SELECT COUNT(*) AS c1 FROM sys.functions WHERE name=\'auto_generated_udf\' LIMIT 1;')['c1'][0] == 1
    if(auto_generated_udf_already_exists):
        _conn.execute('DROP FUNCTION auto_generated_udf;')
    _conn.execute(create_query)

    # create the query for the UDF
    columns = columns.lower()
    columns = columns.replace("int", "").replace("double", "").replace("clob", "")
    columns = columns.split(',')
    original_column_names = []
    query_parameters = []
    for column in columns:
        column_name = column.strip()
        original_column_names.append(column_name)
        query_parameter = table_name + '.' + column_name
        query_parameters.append(query_parameter)
    query_parameters = ','.join(query_parameters)
    original_column_names = ','.join(original_column_names)
    query = 'SELECT auto_generated_udf(' + str(number_of_columns) + ', \'' + original_column_names + '\', ' + query_parameters + ') AS result FROM ' + table_name + ';'
    print("query = ", query)

    # execute the query
    result = _conn.execute(query)['result']
    
    # return the results
    return result
};


# run the set_working_directory script first
SELECT set_working_directory('/Users/rkoopmanschap/projects/centroid-decomposition/cd_monetdb');

# example 1: time_series centroid decomposition
DROP TABLE time_series;
CREATE TABLE time_series(x1 float, x2 float, x3 float, x4 float);
COPY INTO time_series FROM '/Users/rkoopmanschap/projects/centroid-decomposition/cd_monetdb/climate.csv' USING DELIMITERS ',','\n';
SELECT call_dynamic_udf('monetdb_centroid_decomposition.py', 'time_series', 'x1, x2, x3, x4');

# example 2: Using views
DROP VIEW time_series5;
DROP TABLE time_series3;
DROP TABLE time_series4;
CREATE TABLE time_series3 (id INTEGER, x1 FLOAT, x2 FLOAT);
CREATE TABLE time_series4 (id INTEGER, x3 FLOAT, x4 FLOAT);
INSERT INTO time_series3 VALUES (1, 0.2, 0.5), (2, 0.7, 0.1);
INSERT INTO time_series4 VALUES (1, 0.6, 0.2), (2, 0.1, 0.9);
CREATE VIEW time_series5 AS (SELECT ts3.x1, ts3.x2, ts4.x3, ts4.x4 FROM time_series3 AS ts3 JOIN time_series4 AS ts4 ON ts3.id = ts4.id);
SELECT call_dynamic_udf('monetdb_centroid_decomposition.py', 'time_series5', 'x1, x2, x3, x4');
