//Creating the private/public variables/functions needed to create a matrix and utilize it to solve the PDE
#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <iomanip>
#include "vector.hpp"
#include "timer.hpp"

using namespace std;

//Matrix class
class Matrix
{
private:
    vector<vector<double>> data_;
    int maxIters_;
    int tol_;
    int totalIters_;
    Timer time_;
public:
    Matrix();                                  // constructor
    void initIdentity(int n);                  // initialize as an identity matrix of size nxn
    void initFromFile(string fileName);        // read the matrix from a file
    bool isSquare();                           // test whether matrix is square
    int numRows();                             // return number of rows
    int numCols();                             // return number of columns
    double getVal(int row, int col);           // return matrix value at given row/col location (0-indexed based)
    void setVal(int row, int col, double val); // set the matrix value at given row/col location (0-index based)
    Matrix Multiply(Matrix B);                 // post-multiply by B and return resulting matrix
    Matrix Multiply(double A);                 // multiply by a scalar and return resulting matrix
    Matrix Transpose();                        // return transpose of matrix
    vector<double> Diagonal();                 // return a vector containing diagonal elements of the matrix
    void Print();                              // print the matrix to stdout
    void Print(string name);                   // print the matrix to stdout with a name prefix
    Vector Solve(Vector b, int mode);          // solver to get deflections vector
    double getSolveTime();                     // wall clock time (in secs) required for last solve

    // Support methods for iterative methods
    void setSolveTolerance(double tol);        // set desired stopping tolerance
    int  getSolveIters();                      // number of iterations required to solve
};
