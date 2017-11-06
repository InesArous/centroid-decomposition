
- Clone this repo
     git clone git@github.com:InesArous/centroid-decomposition.git
- Navigate to your freshly cloned local git repo
     cd centroid-decomposition
     
### requirements

gnu/linux kernel system (or cygwin), no root priviliges required
gcc supporting C++14, recommended version: 5.0+ 


#====#
 code/
#====#

contains src and batch_cd.py

src contains the c++ implementation of the centroid decomposition.
batch_cd.py the script to run the c++ code

#=====#
 files/
#=====#

contains a sample dataset (sample.txt)  and the decomposition result (cd_output.txt)


#################
 Running example
#################

First, build the program:

>cd code/src/
>make

Second, run the script with python from the "code" folder 

> python batch_cd.py 

The input matrix from files/sample.txt is the following:

X=  7.0 -5.0 10.0
    9.0 1.0 0.0
    -8.0 10.0 6.0
    9.0 10.0 -8.0
    3.0 -7.0 -2.0
    -8.0 10.0 9.0
    
The output results from files/cd_output.txt:

Matrix L =
-5.16; 	-4.28; 	11.36; 	
-7.35; 	4.12; 	3.32; 	
12.78; 	4.87; 	3.59; 	
-6.00; 	14.07; 	-3.32; 	
-6.06; 	-4.83; 	-1.40; 	
13.66; 	4.20; 	6.37; 	

Matrix R=
-0.86; 	0.36; 	0.36; 	
0.41; 	0.91; 	0.09; 	
0.29; 	-0.22; 	0.93; 






