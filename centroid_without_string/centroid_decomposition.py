import numpy as np
from numpy import linalg as LA

#Calculate maximizing sign vector z
def SSV(x,n,m):
	pos = -1
	while True:
		#Change sign
		if pos==-1:
			z = np.matrix(np.ones((n,1),dtype=np.float))
		else:
			z[pos] = z[pos]*-1		
		#Determine s and v
		x_t = np.transpose(x)
		v = np.empty([n, 1])
		for i in range (0, n):
			v[i] = float(x[i]*x_t*z - (z[i]* x[i]*x_t[:,i]))
		#Search next element
		val=0
		pos=-1
		for i in range (0, n):
			if z[i]*v[i]<0:
				if abs(v[i]) > abs(val):
					val = v[i]
					pos = i					
		if pos == -1:
			break		
	return z
	
#Calculate centroid decomposition 
def CD(x):
	n = x.shape[0]
	m = x.shape[1]
	L = R = []	
	for i in range (0, m):
		z = SSV(x,n,m)
		r = (np.transpose(x)*z)/LA.norm(np.transpose(x)*z)
		l = x*r
		if i==0:
			R=r
			L=l
		else:
			R=np.c_[R,r]
			L=np.c_[L,l]		
		x = x - l*np.transpose(r)		
	return L,R
	
	
# input_matrix = []
# with open("./sample.txt") as f:
# 	for line in f:
# 		current_row=[float(x) for x in line.strip().split(' ')]
# 		input_matrix.append(current_row)
		
# input_matrix = np.matrix(input_matrix)

       
# L,R = centroid_decomposition(input_matrix)

# print("L= " + str(L))
# print("R=" + str(R))
