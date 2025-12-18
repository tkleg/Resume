all: bisection angle trough

bisection:
	gfortran -c bisectionMod.f90

angle:
	gfortran AngleChange.f90 bisectionMod.f90 -o angle

trough:
	gfortran TroughDepth.f90 bisectionMod.f90 -o trough