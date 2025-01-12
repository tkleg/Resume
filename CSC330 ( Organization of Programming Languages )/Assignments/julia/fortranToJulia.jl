#!/usr2/local/julia-1.10.4/bin/julia

function read_text_file(filename::String, path::String)
    fullpath = joinpath(path, filename)

    open(fullpath, "r") do file
        line_of_text = readline(file)
        println(line_of_text)
    end
end

read_text_file("testhands", "/pub/pounds/CSC330/poker/")
