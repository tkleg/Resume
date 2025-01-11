#!/usr2/local/julia-1.10.4/bin/julia
using Pkg
using OffsetArrays

println("Hello World; Goodybye Fall Break")

arr = zeros( Int64, 10 )
ints = OffsetArray(arr, 0:9)
ints[0] = 5
println(ints[0])

exit(0)
