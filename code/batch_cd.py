#! /usr/bin/python
import subprocess
import numpy as np

# WORKING_DIRECTORY = '/Users/rkoopmanschap/projects/centroid-decomposition/'
# FILE_LOCATION = WORKING_DIRECTORY + 'files/'
# CDEXEC = WORKING_DIRECTORY + 'code/src/CentroidDecomposition'

WORKING_DIRECTORY = None
FILE_LOCATION = None
CDEXEC = None

# technical
def my_range(start, end, step):
    while start <= end:
        yield start
        start += step

def launchCD(n, m, mx_val, out_val):
    procCD = subprocess.Popen(CDEXEC + \
        ' -test o -n '+ str(n) + ' -m ' + str(m) + \
        ' -data M -in ' + FILE_LOCATION + mx_val + '.txt -out ' + FILE_LOCATION + out_val + '.txt', \
        shell=True)
    retval = procCD.wait()

def convert_blobs_to_floats(blob_array):
	result = []

	for blob in blob_array:
		row = []
		for field in blob.split(' '):
			row.append(float(field))
		result.append(row)

	return np.matrix(result)

def write_matrix_to_file(input_matrix, filename):
	f = open(FILE_LOCATION + filename, 'r+')

	for index, row in enumerate(input_matrix.A):
		if(index != 0): 
			f.write('\n')
		for field in row:
			f.write(str(field) + ' ')

	f.close()

# ---------------

def read_matrix(matrix_lines, matrix_name):
	result = []

	index = matrix_lines.index(matrix_name) + 1

	for line in matrix_lines[index:]:
		if(line == ''):
			break # stop reading at the first empty line
		result_line = []
		for field in line.strip().split(';'):
			if(field != ''): result_line.append(float(field))
		result.append(result_line)

	return result

def read_matrices_from_file(filename):
	result = []

	f = open(FILE_LOCATION + filename, 'r+')
	matrix_text = f.read()
	f.close()

	matrix_lines = matrix_text.split('\n')

	# TODO: always a matrix L and a matrix R?
	matrix_l = read_matrix(matrix_lines, 'MATRIX L: ')
	matrix_r = read_matrix(matrix_lines, 'MATRIX R: ')

	return np.matrix(matrix_l), np.matrix(matrix_r)

# ---------------

def clear_file(filename):
	f = open(FILE_LOCATION + filename, 'r+')
	f.truncate(0)
	f.close()

### scenario
def centroid_decomposition_wrapper(blob_array, working_directory):
	global WORKING_DIRECTORY
	global FILE_LOCATION
	global CDEXEC

	INPUT_FILENAME = 'sample'
	OUTPUT_FILENAME = 'cd_output'
	WORKING_DIRECTORY = working_directory
	FILE_LOCATION = WORKING_DIRECTORY + 'files/'
	CDEXEC = WORKING_DIRECTORY + 'code/src/CentroidDecomposition'

	clear_file(OUTPUT_FILENAME + '.txt')

	input_matrix = convert_blobs_to_floats(blob_array)
	write_matrix_to_file(input_matrix, INPUT_FILENAME + '.txt')
	launchCD(6, 3, INPUT_FILENAME, OUTPUT_FILENAME)
	matrix_l, matrix_r = read_matrices_from_file(OUTPUT_FILENAME + '.txt')
	
	return matrix_l, matrix_r

# launchCD(6, 3, 'sample', 'cd_output')
