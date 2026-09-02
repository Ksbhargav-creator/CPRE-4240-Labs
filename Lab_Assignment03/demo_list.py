# Practice of list methods
list = [1,2,3,4]
# append() method
print("Current list")
print(list)
print("practice append method")
list.append(5)

# clear() method
print("Current list")
print(list)
print("practice clear method")
list.clear()
print(list)

list = [6,7,8,9]
# copy() method
print("Current list")
print(list)
print("practice copy method")
N_list = list.copy()
print(N_list)

# count() method
Clist = ["a","a","a","b","c","c","d"]
print(Clist)
x = Clist.count("a")
print(x)

# extend() method
print("Current list")
print(list)
list.extend(Clist)
print("Practice extend() method")
print(list)

# index() method
print("Practice index() method")
x = list.index("a")
print(x)

# insert() method
print("Current list")
print(list)
print("Practice insert() method")
list.insert(6, 7)
print(list)

# pop() method
print("Current list")
print(list)
print("Practice pop() method")
list.pop(5)
print(list)

# remove() method
print("Current list")
print(list)
print("Practice remove() method")
list.remove("a")
print(list)

# reverse() method
print("Current list")
print(list)
print("Practice reverse() method")
list.reverse() 
print(list)

# sort() method
Nlist = [909, 458, 835, 85, 583, 0, 48, 84, 4]
print("Current list")
print(Nlist)
print("Practice sort() method")
Nlist.sort()
print(Nlist)
