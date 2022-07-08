#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>

using namespace std;

//Computing the fourth order polynomial for the given set of parameters at x
double computePoly (double dd0, double dd1, double dd2, double dd3, double dd4, double xX) {
    double fX = dd4*pow(xX, 4) + dd3*pow(xX, 3) + dd2*pow(xX, 2) + dd1*xX + dd0;
    return fX;
}

//Function to utilize the two bracketing methods (bisection and false position) to determine the midpoint for each iteration and the subsequent
//error when trying to find the root
void bracketingM (double dd0, double dd1, double dd2, double dd3, double dd4, double bmode, double gg1, double gg2, double maxIter) {
    double tol = 1e-8, error = 10*tol;
    int iter = 1;
    if (bmode == 1) {
        cout << "# Root finding mode: Bisection" << endl;
    } else {
        cout << "# Root finding mode: False position" << endl;
    }
    cout << "# Iter    x_m          error" << endl;
    while (abs(error) > tol && iter <= maxIter) {
        double xm, fxm, fgg1 = computePoly(dd0, dd1, dd2, dd3, dd4, gg1), fgg2 = computePoly(dd0, dd1, dd2, dd3, dd4, gg2);
        if (bmode == 1) { //Bisection method to find the midpoint for each iteration
            xm = (gg1 + gg2) * .5;
            fxm = computePoly(dd0, dd1, dd2, dd3, dd4, xm);
        } else if (bmode == 2) { //False position method to find the midpoint for each iteration
            xm = gg2-((fgg2*(gg2-gg1))/(fgg2-fgg1));
            fxm = computePoly(dd0, dd1, dd2, dd3, dd4, xm);
        }
        iter++;
        cout << fixed << setprecision(8);
        if (fgg1 * fxm < 0) {
            gg2 = xm;
            cout << left << setw(7) << iter-1 << setw(14) << xm; 
        } else if (fgg2 * fxm < 0) {
            gg1 = xm;
            cout << left << setw(7) << iter-1 << setw(14) << xm;
        }
        error = fxm;
        cout << right << setw(12) << error << endl;
    }
}

//Function to utilize the open method (secant) to determine midpoint for each iteration and the subsequent error when trying to find the root
void secantM (double dd0, double dd1, double dd2, double dd3, double dd4, double gg1, double maxIters) {
    double tol = 1e-8, error = 10*tol, xk = gg1, xkmone = 1.05*xk, xkpone;
    int iter = 1;
    cout << "# Root finding mode: Secant" << endl;
        cout << "# Iter    x_m          error" << endl;
    while (abs(error) > tol && iter <= maxIters) {
        iter++;
        double fxk = computePoly(dd0, dd1, dd2, dd3, dd4, xk), fxkmone = computePoly(dd0, dd1, dd2, dd3, dd4, xkmone);
        xkpone = xk - ((fxk*(xk-xkmone))/(fxk-fxkmone));
        double fxkpone = computePoly(dd0, dd1, dd2, dd3, dd4, xkpone);
        error = fxkpone;
        cout << fixed << setprecision(8) << left << setw(7) << iter-1 << setw(14) << xkpone << right << setw(12) << fxkpone << endl;
        xkmone = xk;
        xk = xkpone;
    }
}

//Reading 8 or 9 arguments (depending on method) from the command line to determine which method to use to find the root of the function given
//a lower and upper limit or an initial guess
int main(int argc, char* argv[]) {
    double mode = atof(argv[1]), maxIters = atof(argv[2]), d0 = atof(argv[7]), d1 = atof(argv[6]), d2 = atof(argv[5]), d3 = atof(argv[4]), d4 = atof(argv[3]);
    if (mode < 1 || mode > 3 || mode != floor(mode)) {
        cout << "Error. Enter mode as 1 (bisection), 2 (false position), or 3 (secant)." << endl;
        exit(0);
    } else if (mode == 1 || mode == 2) {
        double g1 = atof(argv[8]), g2 = atof(argv[9]);
        if (g1 > g2) {
            cout << "Error. g1 should be less than g2." << endl;
            exit(0);
        }
        bracketingM(d0, d1, d2, d3, d4, mode, g1, g2, maxIters);
    } else if (mode == 3) {
        double g1 = atof(argv[8]);
        secantM(d0, d1, d2, d3, d4, g1, maxIters);
    }
    return 0;
}
