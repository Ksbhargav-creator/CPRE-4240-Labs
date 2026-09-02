import random
import time

n = 10000000

print("For N = 100")

L = [random.random() for _ in range(n)]
start_p0 = time.perf_counter()
L.pop()
end_p0 = time.perf_counter()
print(end_p0 - start_p0)

start_p1 = time.perf_counter()
L.pop(0)
end_p1 = time.perf_counter()
print(end_p1 - start_p1)

start_r0 = time.perf_counter()
L.reverse()
end_r0 = time.perf_counter()
print(end_r0 - start_r0)

start_r1 = time.perf_counter()
R = L[::-1]
end_r1 = time.perf_counter()
print(end_r1 - start_r1)
L.clear()

L = [random.random() for _ in range(2*n)] 

print("For 2N")

start_p0 = time.perf_counter()
L.pop()
end_p0 = time.perf_counter()
print(end_p0 - start_p0)

start_p1 = time.perf_counter()
L.pop(0)
end_p1 = time.perf_counter()
print(end_p1 - start_p1)

start_r0 = time.perf_counter()
L.reverse()
end_r0 = time.perf_counter()
print(end_r0 - start_r0)

start_r1 = time.perf_counter()
R = L[::-1]
end_r1 = time.perf_counter()
print(end_r1 - start_r1)

print("For 4N")

L = [random.random() for _ in range(4*n)] 
start_p0 = time.perf_counter()
L.pop()
end_p0 = time.perf_counter()
print(end_p0 - start_p0)

start_p1 = time.perf_counter()
L.pop(0)
end_p1 = time.perf_counter()
print(end_p1 - start_p1)

start_r0 = time.perf_counter()
L.reverse()
end_r0 = time.perf_counter()
print(end_r0 - start_r0)

start_r1 = time.perf_counter()
R = L[::-1]
end_r1 = time.perf_counter()
print(end_r1 - start_r1)

print("For 8N")

L = [random.random() for _ in range(8*n)] 
start_p0 = time.perf_counter()
L.pop()
end_p0 = time.perf_counter()
print(end_p0 - start_p0)

start_p1 = time.perf_counter()
L.pop(0)
end_p1 = time.perf_counter()
print(end_p1 - start_p1)

start_r0 = time.perf_counter()
L.reverse()
end_r0 = time.perf_counter()
print(end_r0 - start_r0)

start_r1 = time.perf_counter()
R = L[::-1]
end_r1 = time.perf_counter()
print(end_r1 - start_r1)

# The pop(0) function grows linearly by N as it has to move all the elements of the list by one place
# The pop() function only grows by a constant
# The L.reverse() function grows linearly by N as it has to go through every element of the list
# The R = L[::-1] function grows linearly by N and some constant as it needs to be allocated new memory for the new list
