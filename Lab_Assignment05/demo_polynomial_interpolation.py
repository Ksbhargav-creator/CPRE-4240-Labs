import numpy as np

# Gauss Elimination
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
	
# Find the cubic polynomial p(x) = ax3 + bx2 + cx + d that interpolates f(x) = cos(x) at the 
# following four points - (-0.1, cos(-0.1)),(-0.02,cos(-0.02)),(0.02,cos(0.02)),(0.1,cos(0.1)).

f = lambda x: np.cos(x)
A = np.array([[(-0.1)**3, (-0.1)**2, -0.1, 1],[(-0.02)**3, (-0.02)**2, -0.02, 1],[0.02**3, 0.02**2, 0.02, 1],[0.1**3, 0.1**2, 0.1, 1]])
p = np.array([-0.1,-0.02,0.02,0.1])
b = f(p)

x = GaussElimination(A,b)
print('Co-efficients [a,b,c,d]:')
print(x)
