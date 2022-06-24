//Vector class functions to be used to solve the PDE
#include "vector.hpp"

using namespace std;

//Constructor
Vector::Vector() {

}

//Allocating space for nelems entries
void Vector::allocateData(int nelems) {
    this->vecData_.resize(nelems);
}

//Reading vector from fileName
void Vector::initFromFile(string fileName) {
    ifstream file(fileName);
    int num;
    double val;
    if (file.is_open()) {
        file >> num;
        this->vecData_.resize(num);
        for (int i = 0; i < num; i++) {
            file >> val;
            this->vecData_[i] = val;
        }
        file.close();
    } else {
        cout << "Error. Such file did not open or does not exist in the directory." << endl;
        exit(1);
    }
}

//Returning number of elements present in vector
int Vector::numElems() {
    return this->vecData_.size();
}

//Getting and returning value at index i of vector
double Vector::getVal(int i) {
    return this->vecData_[i];
}

//Determining and returning l2 norm of vector
double Vector::l2norm() {
    double total = 0;
    for (int i = 0; i < this->vecData_.size(); i++) {
        total += pow(this->vecData_[i], 2);
    }
    return sqrt(total);
}

//Setting the index i value in vector to val
void Vector::setVal(int i, double val) {
    this->vecData_[i] = val;
}

//Setting all values in the vector to val
void Vector::setAllVals(double val) {
    for (int i = 0; i < this->vecData_.size(); i++) {
        this->vecData_[i] = val;
    }
}

//Printing the given vector
void Vector::Print() {
    cout << "| ";
    for (int i = 0; i < this->vecData_.size(); i++) {
        cout << this->vecData_[i] << " ";
    }
    cout << "|" << endl;
}

//Printing the given vector along with the name
void Vector::Print(string name) {
    cout << name << " = ";
    for (int i = 0; i < this->vecData_.size(); i++) {
        if (i > 0) {
            cout << setw(25);
        }
        cout << "| " << setw(3) << this->vecData_[i] << setw(3) << "|" << endl;
    }
}
