import numpy as np
import time
from numpy import linalg as LA

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
        #        #Determine v
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
def CD(x,n,m):
    L =np.zeros((n,m))
    R =np.zeros((m,m))
    #print R[:,0]
    for i in range (0,m):
        z = SSV(x,n,m)
        R[:,[i]]  = np.dot(np.transpose(x),z)/LA.norm(np.dot(np.transpose(x),z))
        L[:,i] = np.dot(x,R[:,i])
        x = x - np.dot(L[:,[i]],np.transpose(R[:,[i]]))
    return L,R


