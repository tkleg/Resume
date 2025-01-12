#!/usr/bin/python3
import sys

sys.setrecursionlimit(2000)

start = int(sys.argv[1])
end = int(sys.argv[2])

if start > end:
    start, end = end, start
    
global count

def collatz(num):
    global count
    if ( num == 1 ):
        return count
    count += 1
    if ( num % 2 == 0 ):
        return collatz(int(num/2))
    else:
        return collatz(num * 3 + 1)

class CollatzPair:
    def __init__(self, newStart, newLength):
        self.seqStart = newStart
        self.length = newLength


listj = [CollatzPair(0,0)] * 10
for number in range(start, end+1):
    global count
    curNum = number
    count = 0
    newPair = CollatzPair( number, collatz(number) )
    for i in range(len(listj)):
        if newPair.seqStart == 1:
                listj.insert(0, newPair)
                listj.pop()
                break
        elif listj[i].length == newPair.length:
            break
        elif listj[i].length < newPair.length:
            listj.insert(i, newPair)
            listj.pop()
            break

for i in range(len(listj)):
    if listj[i].seqStart == 0:
        listj = listj[:i]
        break
        
print("Sorted based on sequence length")
for pair in listj:
    print(f"{pair.seqStart:>20} {pair.length:>20}" )

anotherPassNeeded = True
while anotherPassNeeded:
    anotherPassNeeded = False
    for i in range(len(listj)-1):
        if listj[i].seqStart < listj[i+1].seqStart:
            anotherPassNeeded = True
            listj[i], listj[i+1] = listj[i+1], listj[i]

print("Sorted based on integer size")
for pair in listj:
    print(f"{pair.seqStart:>20} {pair.length:>20}" )
