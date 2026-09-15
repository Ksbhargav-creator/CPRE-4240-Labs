import numpy as np

def GaussElimination(A,b):
	num_rows = A.shape[0]
	num_columns = A.shape[1]
	
	# Check if it's a square matrix
	if num_rows != num_columns:
		print("Please input a square matrix for A")
		return
	
	# Main loop
	for col in range(num_columns - 1):
		for row in range(col+1,num_rows):
			m = (A[row][col]/A[col][col])
			A[row][col:] = A[row][col:] - m*A[col][col:]
			b[row] = b[row] - m*b[col]
		
	# Back substitution
	x = np.zeros(num_rows)
	x[num_rows-1] = b[num_rows-1]/A[num_rows-1][num_columns-1]
	for row in range(num_rows-2,-1,-1):
		x[row] = (b[row] - np.dot(A[row][row+1:],x[row+1:]))/A[row][row]
	
	return x

def LeastSquareApprox(x,f,n):
    
    # Size of x
    s = len(x)
    
    # Building matrix V
    V = np.zeros((s,n+1))
    for i in range(s):
        for j in range(n+1):
            V[i,j] = x[i]**j
            
    # Transposing V
    VT = V.T

    # Calculating A = V^T*V and b = V^T*f
    A = np.dot(VT, V)
    b = np.dot(VT, f)

    coefs = GaussElimination(A, b)

    return coefs

if __name__ == "__main__":
    import numpy as np
    import matplotlib.pyplot as plt
    
    x = np.linspace(-np.pi, np.pi, 51)
    f = np.cos(x)
    n = 5

    l = LeastSquareApprox(x,f,n)

    # evaluate polynomial with co-eff
    p = sum(l[k] * x**k for k in range(n+1))
    
    plt.plot(x,f)
    plt.plot(x,p)
    plt.show()
    
