all: runge prob27 prob28

runge: runge_kutta.cpp runge_kutta.h
	g++ runge_kutta.cpp -D RUNGE_KUTTA_TEST -o runge

prob27: prob27.cpp runge_kutta.cpp runge_kutta.h
	g++ prob27.cpp runge_kutta.cpp -D PROB_27 -o Q27

prob28: prob28.cpp
	g++ prob28.cpp -D PROB_28 -o Q28