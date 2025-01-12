#!/usr/bin/python3
import sys
#start = int(input("Enter a positive number to start the sequence: "))
#end = int(input("Enter another positive number to start the sequence: "))
start = int(sys.argv[1])
end = int(sys.argv[2])

if start > end:
    start, end = end, start

class CollatzPair:
    def __init__(self, newStart, newLength):
        self.seqStart = newStart
        self.length = newLength
    def __str__(self):
        return f"{self.seqStart} {self.length}"
    

listj = [CollatzPair(0,0)] * 10
for number in range(start, end+1):
    curNum = number
    count = 0
    while curNum != 1:
        if ( curNum % 2  == 0 ):
            curNum = curNum / 2
        else:
            curNum = curNum * 3 + 1
        count += 1
    newPair = CollatzPair( number, count )
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
