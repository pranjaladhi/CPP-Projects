//Functions within the Beam class to solve the PDE
#include "beam.hpp"
#include "matrix.hpp"
#include "vector.hpp"

using namespace std;

//Constructor
Beam::Beam(int n, double L, double EI, double q) {
    this->K_.initIdentity(n);
    this->f_.allocateData(n);
    n_ = n;
    L_ = L;
    EI_ = EI;
    q_ = q;
}

//Returns system stiffness matrix
Matrix Beam::getStiffnessMatrix() {
    for (int i = 0; i < this->n_; i++) {
        for (int j = 0; j < this->n_; j++) {
            if ((i == 0 && j == 0) || (i == this->n_-1 && j == this->n_-1)) {
                this->K_.setVal(i, j, 1);
            } else if (i == j && i != 0 && i != this->n_-1) {
                this->K_.setVal(i, j, -2);
            } else if (i == 1 && j == 0) {
                this->K_.setVal(i, j, 1); 
            } else if (i == j + 1 || i == j - 1) {
                this->K_.setVal(i, j, 1);
            } else {
                this->K_.setVal(i, j, 0);
            }
        }
    }
    this->K_.setVal(0, 1, 0);
    this->K_.setVal(this->n_-1, this->n_-2, 0);
    return this->K_;
}

//Returns system forcing vector
Vector Beam::getSystemRHS() {
    double fVal, xVal, deltaX = this->L_/(this->n_-1);
    for (int i = 0; i < this->n_; i++) {
        if (i == 0 || i == this->n_-1) {
            this->f_.setVal(i, 0);
        } else {
            xVal = i * deltaX;
            fVal = ((-(this->q_)*pow(deltaX, 2))/(2*this->EI_))*(pow(xVal, 2) - xVal*this->L_);
            this->f_.setVal(i, fVal);
        }
    }
    return this->f_;
}

//Returns exact solution
Vector Beam::getExactSoln() {
    Vector exactSoln;
    exactSoln.allocateData(this->n_);
    double yVal, xVal, deltaX = this->L_/(this->n_-1);
    for (int i = 0; i < this->n_; i++) {
        xVal = i*deltaX;
        yVal = ((-1*this->q_)/(2*this->EI_)*((pow(xVal, 4)/12) - ((pow(xVal, 3)*this->L_)/6))) - ((this->q_*pow(this->L_, 3)*xVal)/(24*this->EI_));
        exactSoln.setVal(i, yVal);
    }
    return exactSoln;
}

//Returns finite-difference solution
Vector Beam::getApproxSoln() {
    Vector approxSoln;
    approxSoln.allocateData(this->n_);
    approxSoln = this->K_.Solve(this->f_, this->turbo_);
    return approxSoln;
}

//Returns discretized x-coord values
Vector Beam::getCoordValues() {
    Vector xCoords;
    xCoords.allocateData(this->n_);
    double deltaX = this->L_/(this->n_-1), xVal;
    for (int i = 0; i < this->n_; i++) {
        xVal = deltaX * i;
        xCoords.setVal(i, xVal);
    }
    return xCoords;
}

//Returns l2 error norm between exact and approx. solutions
double Beam::l2norm (Vector exact, Vector approx) {
    Vector exactApprox;
    exactApprox.allocateData(this->n_);
    for (int i = 0; i < this->n_; i++) {
        exactApprox.setVal(i, exact.getVal(i) - approx.getVal(i));
    }
    cout << "l2 error: " << exactApprox.l2norm() << endl;
    return exactApprox.l2norm();
}

//Sets turbo mode setting to determine whether to skip unnecessary solvers to create a faster solve time
void Beam::setTurbo(bool mode) {
    if (mode == true) {
        this->turbo_ = 1;
    } else {
        this->turbo_ = 0;
    }
}
