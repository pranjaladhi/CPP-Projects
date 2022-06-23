//Leverages the Beam, Matrix, and Vector classes to solve the PDE of the Beam using command line arguments inputted by the user
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>
#include "vector.hpp"
#include "matrix.hpp"
#include "beam.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 5) {
        cout << "---------------------------------------\nBeam Solver 9003\n   -> Solving a simply supported beam\n---------------------------------------\n \n";
        cout << "Usage: beam [n] [L] [EI] [q] <turbo>\n \nwhere:\n  [n]            number of points\n  [L]            length of the beam\n";
        cout << "  [EI]           (Young's modulus)*(2nd moment of inertia)\n  [q]            distributed load per unit length\n  <turbo>        optional argument (1=turbo mode)" << endl;
        exit(0);
    }
    int numPoints = atoi(argv[1]), turb;
    double length = atof(argv[2]), EI = atof(argv[3]), q = atof(argv[4]), l2norm;
    if (numPoints < 0 || length < 2 || EI < 0 || q < 0) {
        cout << "Error. No values can be negative." << endl;
        exit(1);
    }
    Beam deflection(numPoints, length, EI, q);
    if (argc == 6) { //Checking to see if user opted to use turbo
        turb = atoi(argv[5]);
        if (turb != 1) {
            cout << "Error. Leave blank or put 1 for <turbo>." << endl;
            exit(1);
        }
        cout << "-->Turbo enabled." << endl;
        deflection.setTurbo(true);
        Matrix stiffMatrix = deflection.getStiffnessMatrix();
        Vector RHSVector = deflection.getSystemRHS();
        Vector approxDeflections = deflection.getApproxSoln();
        Vector exactDeflections = deflection.getExactSoln();
        l2norm = deflection.l2norm(exactDeflections, approxDeflections);
    } else { //If user doesn't opt for turbo, it is disabeled
        cout << "-->Turbo disabled." << endl;
        deflection.setTurbo(false);
        Matrix stiffMatrix = deflection.getStiffnessMatrix();
        Vector RHSVector = deflection.getSystemRHS();
        cout << "-->Might take a while." << endl;
        Vector approxDeflections = deflection.getApproxSoln();
        cout << "-->Patience is key." << endl;
        Vector exactDeflections = deflection.getExactSoln();
        l2norm = deflection.l2norm(exactDeflections, approxDeflections);
    }
    cout << "Constant mesh interval (h): " << length / (numPoints-1) << endl;
    return 0;
}
