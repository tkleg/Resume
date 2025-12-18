all: roundingCalc gaussianElim prob4 prob7

roundingCalc: roundingCalc.cpp roundingCalc.h
	g++ roundingCalc.cpp -D ROUNDINGCALC_CPP -o roundingCalc

gaussianElim: gaussianElim.cpp gaussianElim.h roundingCalc.h roundingCalc.cpp
	g++ gaussianElim.cpp roundingCalc.cpp -D GAUSSIANELIM_CPP -o gaussianElim

prob4: prob4.cpp gaussianElim.h roundingCalc.h roundingCalc.cpp gaussianElim.cpp
	g++ prob4.cpp gaussianElim.cpp roundingCalc.cpp -D PROB_4 -o Q4

prob7: prob7.cpp gaussianElim.h roundingCalc.h roundingCalc.cpp gaussianElim.cpp
	g++ prob7.cpp gaussianElim.cpp roundingCalc.cpp -D PROB_7 -o Q7