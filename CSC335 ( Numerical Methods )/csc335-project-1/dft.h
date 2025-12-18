#ifndef DFT_H
#define DFT_H

#include"common.h"
#include<armadillo>
#include<cmath>
#include<fstream>
#include<vector>
#include<random>
using namespace arma;
using namespace std;

cx_vec cVector( vector<double> data, cx_mat Z );
/*
    @param data: input data vector
    @param Z: Z matrix
    @return: c vector after multiplying by G matrix
*/

vector<double> recoverInverse(cx_vec c, cx_mat Z);
/*
    @param c: c vector
    @param Z: Z matrix
    @return: recovered data vector after multiplying the conjugate of Z matrix with the c vector
*/

vector<double> recoverDirect(cx_vec c, cx_mat Z);
/*
    @param c: c vector
    @param Z: Z matrix
    @return: recovered data vector v by solving Zv = c
*/

cx_mat zMatrix(int n);
/*
    @param n: size of the matrix
    @return: Z matrix of size n x n
*/

cx_mat gMatrix(int n);
/*
    @param n: size of the matrix
    @return: G matrix of size n x n
*/

cx_vec yVector( vector<double> v );
/*
    @param v: input data vector
    @return: cx_vec with the real part as v and imaginary part as 0
*/

#endif