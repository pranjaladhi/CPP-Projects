//Stores the private and public variables to utilize in the functions to solve the PDE 
#pragma once
#include <vector>
#include <cmath>
#include "matrix.hpp"
#include "vector.hpp"

using namespace std;

class Beam
{
private:
    Matrix K_;          // system stiffness matrix
    Vector f_;          // right-hand forcing vector
    int n_;             // number of points
    double L_;          // length of the beam
    double EI_;         // (Young's modulus)*(2nd moment of interia)
    double q_;          // distributed load per unit length
    int turbo_;         // turbo mode setting to turn on or off
public:
    Beam(int n, double L, double EI, double q); // constructor
    Matrix getStiffnessMatrix();                // return system stiffness matrix
    Vector getSystemRHS();                      // return system forcing vector
    Vector getExactSoln();                      // return exact solution
    Vector getApproxSoln();                     // return finit-difference solution
    Vector getCoordValues();                    // return discretized x-coord values
    double l2norm(Vector exact, Vector approx); // return l2 error norm between exact and approx. solutions
    int getSolveIters();                        // return number of solver iterations
    double getSolveTime();                      // return solver time (secs)
    void setTurbo(bool mode);                   // set turbo mode setting
};
