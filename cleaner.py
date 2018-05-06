def towrite(handle, size, entries):
	handle.write(str(size) + "\n")
	for i in range(size):
		handle.write(entries[i])



name = raw_input("file to be cleaned: ") 
out = raw_input("name of new file: ")
handle1 = open(name, "r")
handle2 = open(out, "w+")

ctr = 0
buff = list()
cur = (handle1.readline().split())[0]
n = 0
handle1.seek(0,0)
for line in handle1:
	words = line.split()
	if (cur == words[0]):
		buff.append(line)
		ctr += 1
	else:
		n += 1
		towrite(handle2, ctr, buff)
		buff = []
		buff.append(line)
		ctr = 1
		cur = words[0]
towrite(handle2, ctr, buff)
n += 1
print "vertices: " + str(n)
handle1.close()
handle2.close()