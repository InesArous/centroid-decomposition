#! /usr/bin/python
import subprocess

# technical
def my_range(start, end, step):
    while start <= end:
        yield start
        start += step

CDexec = './bin/batchCD/CentroidDecomposition'

def launchCD(n, m, mx_val, out_val):
    procCD = subprocess.Popen(CDexec + \
        ' -test t -n '+ str(n) + ' -m ' + str(m) + \
        ' -data M -in ./Data/' + mx_val + '.txt -out ./Results/batch/' + out_val + '.txt', \
        shell=True)
    retval = procCD.wait()

### scenario
launchCD(6, 3, 'sample', 'cd_runtime')


