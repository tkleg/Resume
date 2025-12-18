all: runge_kutta_systems prob1 prob5 prob6

runge_kutta_systems: runge_kutta_systems.cpp
	g++ runge_kutta_systems.cpp -D RUNGE_KUTTA_SYSTEMS_TEST -o runge_kutta_systems

prob1: prob1.cpp runge_kutta_systems.cpp runge_kutta_systems.h
	g++ prob1.cpp runge_kutta_systems.cpp -D PROB_1B -o Q1

prob5: prob5.cpp runge_kutta_systems.cpp runge_kutta_systems.h
	g++ prob5.cpp runge_kutta_systems.cpp -D PROB_5 -o Q5

prob6: prob6.cpp runge_kutta_systems.cpp runge_kutta_systems.h
	g++ prob6.cpp runge_kutta_systems.cpp -D PROB_6 -o Q6