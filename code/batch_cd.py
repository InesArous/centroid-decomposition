#! /usr/bin/python
import subprocess

# technical
def my_range(start, end, step):
    while start <= end:
        yield start
        start += step

CDexec = './src/CentroidDecomposition'

def launchCD(n, m, mx_val, out_val):
    procCD = subprocess.Popen(CDexec + \
        ' -test o -n '+ str(n) + ' -m ' + str(m) + \
        ' -data M -in ../files/' + mx_val + '.txt -out ../files/' + out_val + '.txt', \
        shell=True)
    retval = procCD.wait()

### scenario
launchCD(6, 3, 'sample', 'cd_output')


