all: main main_write filters naturalSpline manifoldFinder input_processor integrals geometricDataGen connect_the_dots dft dualStream

main: main.cpp main.h filters.cpp filters.h naturalSpline.cpp naturalSpline.h manifoldFinder.cpp manifoldFinder.h input_processor.cpp input_processor.h common.cpp common.h integrals.cpp integrals.h peak_and_shift.cpp peak_and_shift.h dft.cpp dft.h dualStream.cpp dualStream.h
	g++ main.cpp filters.cpp naturalSpline.cpp manifoldFinder.cpp input_processor.cpp common.cpp integrals.cpp peak_and_shift.cpp dft.cpp dualStream.cpp -D MAIN -larmadillo -g -o main

main_write: main.cpp main.h filters.cpp filters.h naturalSpline.cpp naturalSpline.h manifoldFinder.cpp manifoldFinder.h input_processor.cpp input_processor.h common.cpp common.h integrals.cpp integrals.h peak_and_shift.cpp peak_and_shift.h dft.cpp dft.h dualStream.cpp dualStream.h
	g++ main.cpp filters.cpp naturalSpline.cpp manifoldFinder.cpp input_processor.cpp common.cpp integrals.cpp peak_and_shift.cpp dft.cpp dualStream.cpp -D MAIN -D WRITE_ALL -larmadillo -o main_write

filters: filters.cpp filters.h common.cpp common.h naturalSpline.cpp naturalSpline.h
	g++ filters.cpp common.cpp naturalSpline.cpp -D TEST_SAVITZKY_GOLAY_READER -o filters

naturalSpline: naturalSpline.cpp naturalSpline.h
	g++ naturalSpline.cpp -D NATURAL_SPLINE_TEST -o naturalSpline

manifoldFinder: manifoldFinder.cpp naturalSpline.cpp naturalSpline.h manifoldFinder.h common.cpp common.h
	g++ manifoldFinder.cpp naturalSpline.cpp common.cpp -D MANIFOLD_FINDER_TEST -o manifoldFinder

input_processor: input_processor.cpp input_processor.h dualStream.cpp dualStream.h
	g++ input_processor.cpp dualStream.cpp -D INPUT_PROCESSOR_TEST -o input_processor

integrals: integrals.cpp integrals.h common.cpp common.h naturalSpline.cpp naturalSpline.h
	g++ integrals.cpp common.cpp naturalSpline.cpp -D NEWTON_COTES_TEST -o integrals

geometricDataGen: data_generators/testdata_gen.cpp integrals.cpp integrals.h naturalSpline.cpp naturalSpline.h common.cpp common.h
	g++ data_generators/testdata_gen.cpp integrals.cpp naturalSpline.cpp common.cpp -D SHAPED_DATA_GEN -o geometricDataGen

connect_the_dots: data_generators/connect_the_dots.cpp
	g++ data_generators/connect_the_dots.cpp -D CONNECT_THE_DOTS_MAIN -o connect_the_dots

dft: dft.cpp dft.h common.cpp common.h naturalSpline.cpp naturalSpline.h
	g++ dft.cpp common.cpp naturalSpline.cpp -larmadillo -D DFT -o dft

dualStream: dualStream.cpp dualStream.h
	g++ dualStream.cpp -D dualStream -o dualStream