mutable struct CPair
    seqStart::Int128
    length::Int128
end

function newCPair( newStart::Int128, newLength::Int128 )
    return CPair(newStart, newLength)
end

function pairToString( pair::CPair )
    return "$(lpad(pair.seqStart, 20)) $(lpad(pair.length, 20))"
end

function collatz( num::UInt128, count::Int128 )
    if num == 1
        return count
    end
    count += 1
    if num % 2 == 0
        return collatz(convert(UInt128, num / 2), convert(Int128, count))
    else
        return collatz(convert(UInt128, num * 3 + 1), convert(Int128, count))
    end
end

start = parse(Int, ARGS[1])
endN = parse(Int, ARGS[2])

if start > endN
        start, endN = endN, start
end

listj = [newCPair(convert(Int128, 0),convert(Int128, 0)) for _ in 0:9]
for number in start:endN
    curNum = number
    newPair = newCPair(convert(Int128, number), collatz(convert(UInt128, number), convert(Int128, 0)) )
    for i in 1:10
        if newPair.seqStart == 1
            for k in 10:-1:2
                listj[k] = listj[k-1]
            end
            listj[1] = newPair
            break
        elseif listj[i].length == newPair.length
            break
        elseif listj[i].length < newPair.length
            for k in 10:-1:i+1
                listj[k] = listj[k-1]
            end
            listj[i] = newPair
            break
        end
    end
end

println("Sorted based on sequence length")
for x in 1:10
    if listj[x].seqStart == 0
        break
    end
    println(pairToString(listj[x]))
end

global anotherPassNeeded = true
while anotherPassNeeded
    global anotherPassNeeded = false
    for i in 1:9
        if listj[i].seqStart < listj[i+1].seqStart
            global anotherPassNeeded = true
            temp = listj[i]
            listj[i], listj[i+1] = listj[i+1], listj[i]
        end
    end
end

println("Sorted based on integer size")
for x in 1:10
    if listj[x].seqStart == 0
        break
    end
    println(pairToString(listj[x]))
end
