def sqrt(x):
	# Change it into float
	x = 1.0*x
	# Check if the input is wrong
	if x == 0.0:
		return 0
	if x < 0.0:
		print("Please input a non-negative integer")
		return -1.0
	# Initial root guess
	sold = 1.0

	while abs(sold * sold - x) > 0.000001:
		s = sold - (sold*sold - x)/(2*sold)
		sold = s

	return s

def fac(x):
	f = 1
	# Simple loop
	for k in range(1,x):
		f = f*(k+1)
	return f

def exp(x):
	# Store the value of e
	e = 2.7182818284590451
	# Round x into nearest integer
	x0 = int(round(x))
	z = x - x0
	e_z = 1.0
	t = 1.0
	n = 0

	# Compute e_x0
	e_x0 = 1.0
	if x0 >= 0.0:
		for _ in range(x0):
			e_x0 *= e
	else:
		for _ in range(x0):
			e_x0 /= e

	while abs(t) > 0.00000001:
		n += 1
		t =  t*z/n
		e_z += t
	return e_x0*e_z

def ln(x):
	# Change the number to float
	x = 1.0*x
	# Check if input is wrong
	if x <= 0.0:
		print("Please input a positive integer")
		return -1.0
	# Initial logarithmic guess
	lold = 1.0
	l = 1.0

	while abs(exp(lold) - x )> 0.00000001:
		lold += x/exp(lold) - 1

	return lold

s = sqrt(2)
f = fac(5)
e = exp(2)
l = ln(2)
print("Natural logarthimic of 2")
print(l)


	

