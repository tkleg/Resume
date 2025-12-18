all: prob1 prob2

prob1: prob1.cpp ../Section4/runge_kutta.cpp ../Section4/runge_kutta.h
	g++ prob1.cpp ../Section4/runge_kutta.cpp -D PROB_1 -o Q1

prob2: prob2.cpp ../Section4/runge_kutta.cpp ../Section4/runge_kutta.h ../Section2/eulers.h ../Section2/eulers.cpp
	g++ prob2.cpp ../Section4/runge_kutta.cpp ../Section2/eulers.cpp -D PROB_2 -o Q2