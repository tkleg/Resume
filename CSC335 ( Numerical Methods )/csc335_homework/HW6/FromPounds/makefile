all: hilbert complexFind complexGraph

hilbert: hilbert.cpp
	g++ hilbert.cpp -D HILBERT -larmadillo -o hilbert

complexFind: complex.cpp
	g++ complex.cpp -D COMPLEX -D FIND_MAX -larmadillo -o findmax

complexGraph: complex.cpp
	g++ complex.cpp -D COMPLEX -D GRAPH -larmadillo -o graph