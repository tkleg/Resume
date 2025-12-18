all: eulers prob_1

eulers: eulers.cpp eulers.h
	g++ eulers.cpp -D EULERS_TEST -o eulers

prob_1: prob_1.cpp eulers.cpp eulers.h
	g++ prob_1.cpp eulers.cpp -D PROB_1 -o Q1