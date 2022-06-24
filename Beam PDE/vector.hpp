//Initializing needed private/public variables/functions for the Vector class to utilize it in solving the PDE
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

class Vector
{
private:
    vector<double> vecData_;
public:
    Vector();                                  // constructor
    void allocateData(int nelems);             // allocate space for nelem entries (of double type)
    void initFromFile(string fileName);        // read the vector from a file
    int numElems();                            // return number of elements
    double getVal(int i);                      // return the ith element
    double l2norm();                           // return l2 norm
    void setVal(int i, double val);            // set the ith element to val
    void setAllVals(double val);               // set all elements of the vector to val
    void Print();                              // print the vector contents to stdout
    void Print(string name);                   // print the vector contents to stdout with a name prefix
};
