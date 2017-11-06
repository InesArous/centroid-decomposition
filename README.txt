
- Clone this repo
     git clone git@github.com:eXascaleInfolab/InCD_bench.git
- Navigate to your freshly cloned local git repo
     cd InCD_bench
    
#====#
 bin/
#====#

contains different versions of the programs for test runs
has to be compiled beforehand using provided Makefile; including for scripted scenarios

### see available programs

> cd bin/
> ls

### requirements

gnu/linux kernel system (or cygwin), no root priviliges required
gcc supporting C++14, recommended version: 5.0+

### building the program

> cd bin/batchCD/
> make


Results of the Centroid Decomposition are in Results/batch/

#=====#
 Data/
#=====#

contains data sets for test runs
sample.txt

#=======#
 script/
#=======#

contains a test script that use programs from bin/ and outputs results to Results/
scripts are meant to be launched from this folder (centroid-decomposition/), not from script/
language: python

### see available programs

> cd script/
> ls

### scenario usage

python ./script/batch_cd.py


#========#
 Results/
#========#

contains the output of test scripts

### output interpretation

#cd_runtime.txt
column 1 - number of rows
column 2 - number of columns
column 3 - execution time (milliseconds)

#output.txt
output.txt contain the decomposition output L (Load= ) and R (REL= )

#################
 Running example
#################

First, build the code:

>cd bin/batchCD/
>make

Second, run the script with python from the centroid-decomposition folder 

> python ./script/batch_cd.py 

The input matrix inside the folder Data/sample.txt is the following:

X=  7.0 -5.0 10.0
    9.0 1.0 0.0
    -8.0 10.0 6.0
    9.0 10.0 -8.0
    3.0 -7.0 -2.0
    -8.0 10.0 9.0
    
The output results are inside the folder Results/output.txt:

LOAD =
-5.16; 	-4.28; 	11.36; 	
-7.35; 	4.12; 	3.32; 	
12.78; 	4.87; 	3.59; 	
-6.00; 	14.07; 	-3.32; 	
-6.06; 	-4.83; 	-1.40; 	
13.66; 	4.20; 	6.37; 	

REL =
-0.86; 	0.36; 	0.36; 	
0.41; 	0.91; 	0.09; 	
0.29; 	-0.22; 	0.93; 

The runtime needed to run the centroid decomposition is in Results/cd_runtime.txt in the following format:

#cd_runtime.txt
column 1 - number of rows =6
column 2 - number of columns =3
column 3 - execution time (milliseconds)





