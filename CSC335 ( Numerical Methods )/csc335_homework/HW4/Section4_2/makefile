all: richardsons sec4_2Q1and2

richardsons: richardsons.cpp richardsons.h
	g++ richardsons.cpp -D RICHARDSONS -o richardsons

sec4_2Q1and2: sec4_2Q1and2.cpp richardsons.h richardsons.cpp
	g++ sec4_2Q1and2.cpp richardsons.cpp -o Q1and2