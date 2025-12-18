# Numerical Methods

## Description of Class
- (Direct from the catalog) A study of numerical methods for the solution of mathematical problems and computer application of those methods. Topics will include methods such as the bisection algorithm and fixed point iteration for the solution of equations with a single variable, interpolation and polynomial approximation, numerical differentiation and integration, solution of systems of linear equations, and least squares approximation.
- The class is consisting of homeworks, large projects, and tests
- You will need the Armadillo library installed in order to run the project and some of the later homework questions.
- g++ version 15.2 was used for compilation of all C++ code. Data structures such as pair and optional are used, which do not exist in some older versions.

### Homework
- The homework folder in this directory contains all homework problems that were completed via code ( almost all problems ).
- The problems are mostly about various algorithms that complete problems including the following types, and more.
  - Integration
  - Derivatives
  - Matrices
  - Root Finding
  - Interpolation
  - Filtering

### Project
- This course had one main project split into two parts.
- The first part had us analyze the discrete data from a NMR spectrum.
- If you wish to run the program, you will need to run `make main` to get the executable.
- If the Discrete Fourier Transform option is used, it will take much longer to compute, and temporarily use rather large amounts of RAM. The largest test case, having 8192 data points, involved a matrix in RAM that was approximately 8GB.
- Algorithm (From professor)
  1. Adjust data by a baseline value.
  2. (Optional) Filter data with Boxcar, Savitzky-Golay, or a Discrete Fourier Transform.
  3. Create a natrual cubic spline for the data. This allows access to a y-value for any x-value between the max and min.
  4. Integrate the peaks with Tolerant Composite Simpson's Rule, Tolerant Romberg Extrapolation, Adaptive Quadrature, or 64-point Gauss Legendre Quadrature.