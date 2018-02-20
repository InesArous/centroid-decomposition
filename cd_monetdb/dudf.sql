CREATE OR REPLACE FUNCTION set_working_directory(working_directory STRING) RETURNS BOOLEAN LANGUAGE PYTHON {
    import os

    os.chdir(working_directory)

    return True
};

CREATE OR REPLACE FUNCTION dudf(file STRING, table_name STRING, columns STRING) RETURNS STRING LANGUAGE PYTHON {
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
    default_function_code_before = """
from collections import OrderedDict
import sys
import os

data = OrderedDict()
original_column_names = original_column_names.split(',')
for i in range(number_of_columns):
    exec('data[original_column_names[i]] = c' + str(i)) in locals()

working_directory = os.getcwd()
sys.path.append(working_directory)

"""

    default_function_code_after = """
return str(process_data(data))

"""

    with open(file, "r") as myfile:
        data = myfile.read()
    function_code = data

    # create the new UDF
    create_query = 'CREATE FUNCTION auto_generated_udf(number_of_columns INTEGER, original_column_names STRING, ' + column_parameters + ') RETURNS STRING LANGUAGE PYTHON {\n' + default_function_code_before + function_code + '\n' + default_function_code_after + '\n};'
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

    # execute the query
    result = _conn.execute(query)['result']
    
    # return the results
    return result
};
