#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Wed Jan 31 21:40:15 2018

@author: inesarous
"""

#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Tue Dec 12 17:14:45 2017

@author: inesarous
"""

import numpy as np
import time
from numpy import linalg as LA

#Calculate maximizing sign vector z
def SSV(x,n,m):
	pos = -1
	z = np.ones((n,1))
	v = (np.dot(x,np.transpose(np.sum(x, axis=0)))- np.sum(x*x,axis=1)).reshape((n,1))
	#print v
	var_bool=True
	while var_bool or (pos!=-1):
		var_bool=False
		#Change sign
		if pos!=-1:
			z[pos] = z[pos]*-1		
#		#Determine v
		v=v+(2*z[pos]*(np.dot(x,x[pos]))).reshape(n,1)
		v[pos]=v[pos]-(2*z[pos]*(np.dot(x[pos],x[pos])))            
		#Search next element
		val=z*v
		if val[val<0].size!=0:
			pos=np.argmin(val)
		else:
			pos=-1
	return z
	
#Calculate centroid decomposition 
def CD(x,k,n,m):
	L =np.zeros((n,m))
	R =np.zeros((m,m))
	#print R[:,0]
	for i in range (0,k):
		z = SSV(x,n,m)    
		R[:,[i]]  = np.dot(np.transpose(x),z)/LA.norm(np.dot(np.transpose(x),z))
		L[:,i] = np.dot(x,R[:,i])
		x = x - np.dot(L[:,[i]],np.transpose(R[:,[i]]))
	return L,R

def nan_helper(y):
    """Helper to handle indices and logical indices of NaNs.

    Input:
        - y, 1d numpy array with possible NaNs
    Output:
        - nans, logical indices of NaNs
        - index, a function, with signature indices= index(logical_indices),
          to convert logical indices of NaNs to 'equivalent' indices
    Example:
        >>> # linear interpolation of NaNs
        >>> nans, x= nan_helper(y)
        >>> y[nans]= np.interp(x(nans), x(~nans), y[~nans])
    """

    return np.isnan(y), lambda z: z.nonzero()[0],lambda z1: z1.nonzero()[1]

def cd_recovery(X_tilde,n,m,trunc_col,epsilon,missing_rows,missing_cols):
    iteration=1
    X_init = np.zeros([n, m])
    while (LA.norm(X_init-X_tilde)>epsilon):
    	iteration+=1
    	X_init=X_tilde.copy()
    	L,R = CD(X_tilde,(X_tilde.shape[1]-trunc_col),n,m)
    	X_new=np.dot(L,np.transpose(R))
    	X_tilde[missing_rows,missing_cols]=X_new[missing_rows,missing_cols]                    
    return X_init,iteration




def recovery(input_matrix,n,m,trunc_col):
    #interpolation
   X_tilde=input_matrix.copy()
   nans, index0,index1= nan_helper(X_tilde)
   missing_rows=index0(nans)
   missing_cols=index1(nans)
   X_tilde[nans]= np.interp(missing_rows, index0(~nans), X_tilde[~nans])
   #recovery of missing values
   epsilon=1e-02
   ts1 = time.time()
   X_init,iteration = cd_recovery(X_tilde,n,m,trunc_col,epsilon,missing_rows,missing_cols)
   ts2 = time.time()
   return (ts2 - ts1),iteration,X_init


