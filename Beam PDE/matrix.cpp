//Functions to be utilized within the Matrix class to solve the PDE
#include "matrix.hpp"
#include "vector.hpp"

using namespace std;

//Matrix constructor
Matrix::Matrix() {
    
}

//Creating the identity matrix with size nxn
void Matrix::initIdentity(int n) {
    this->data_.resize(n, vector<double>(n));
    for (int i = 0; i < n; i++) {
        this->data_[i][i] = 1;
    }
}

//Reading from file with the given matrix size and values stored at each index
void Matrix::initFromFile(string fileName) {
    ifstream file(fileName);
    int row, col;
    double val;
    if (file.is_open()) {
        file >> row >> col;
        this->data_.resize(row, vector<double>(col));
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                file >> val;
                this->data_[i][j] = val;
            }
        }
        file.close();
    } else {
        cout << "Error. Input file does not exist in the directory." << endl;
        exit(1);
    }
}

//Determining and returning if the matrix given is a square matrix
bool Matrix::isSquare() {
    if (this->data_.size() == this->data_[0].size()) {
        return true;
    } else {
        return false;
    }
}

//Determining and returning the number of rows of the given matrix
int Matrix::numRows() {
    return this->data_.size();
}

//Determining and returning the number of columns of the given matrix
int Matrix::numCols() {
    return this->data_[0].size();
}

//Returning the value of the matrix at index row and col
double Matrix::getVal(int row, int col) {
    return this->data_[row][col];
}

//Setting the value of the matrix at index row and col to val
void Matrix::setVal(int row, int col, double val) {
    this->data_[row][col] = val;
}

//Performing and returning the matrix after matrix multiplication with the given matrix and matrix B
Matrix Matrix::Multiply(Matrix B) {
    Matrix C;
    C.data_.resize(this->numRows(), vector<double>(B.numCols()));
    if (this->data_[0].size() != B.numRows()) {
        cout << "Error. The matrices cannot be multiplied together." << endl;
        exit(1);
    } else {
        for (int i = 0; i < this->numRows(); i++) {
            for (int j = 0; j < B.numCols(); j++) {
                double tempStor = 0;
                for (int k = 0; k < this->numCols(); k++) {
                    tempStor += this->data_[i][k] * B.getVal(k, j);
                }
                C.setVal(i, j, tempStor);
            }
        }
        return C;
    }
}

//Performing and returning the matrix after scalar multiplication by the value A
Matrix Matrix::Multiply(double A) {
    Matrix D;
    D.data_.resize(this->numRows(), vector<double>(this->numCols()));
    double val;
    for (int i = 0; i < this->data_.size(); i++) {
        for (int j = 0; j < this->data_[0].size(); j++) {
            val = A*this->data_[i][j];
            D.setVal(i, j, val);
        }
    }
    return D;
}

//Returning the transpose matrix of the given matrix
Matrix Matrix::Transpose() {
    Matrix E;
    E.data_.resize(this->numCols(), vector<double>(this->numRows()));
    for (int i = 0; i < E.numRows(); i++) {
        for (int j = 0; j < E.numCols(); j++) {
            E.setVal(i, j, this->data_[j][i]);
        }
    }
    return E;
}

//Determining and returning the diagonal values of the matrix 
vector<double> Matrix::Diagonal() {
    vector<double> diagMat;
    diagMat.resize(this->numCols());
    for (int i = 0; i < this->data_.size(); i++) {
        for (int j = 0; j < this->data_[0].size(); j++) {
            if (i == j) {
                diagMat[i] = this->data_[i][j];
            }
        }
    }
    return diagMat;
}

//Printing the matrix given
void Matrix::Print() {
    for (int i = 0; i < this->data_.size(); i++) {
        cout << "| ";
        for (int j = 0; j < this->data_[0].size(); j++) {
            cout << this->data_[i][j] << " ";
        }
        cout << "|" << endl;
    }
}

//Printing the matrix given along with the name
void Matrix::Print(string name) {
    cout << name << " = |";
    for (int i = 0; i < this->data_.size(); i++) {
        if (i == 0) {
            cout << setw(2);
        } else {
            cout << setw(11) << "|";
        }
        for (int j = 0; j < this->data_[0].size(); j++) {
            cout << setw(9) << data_[i][j];
        }
        cout << "|" << endl;
    }
}

//Solver to get deflection vector using Gauss-Siedel
Vector Matrix::Solve(Vector b, int mode) {
    Vector y;
    y.allocateData(b.numElems());
    Vector oldVec;
    oldVec.allocateData(b.numElems());
    int iter = 0;
    double error = 50, val, rowdiv, yValDif;
    if (mode != 1) { //SNAIL
        this->time_.Start();
        while (error > 1e-8) {
            for (int k = 0; k < b.numElems(); k++) {
                oldVec.setVal(k, y.getVal(k));
            }
            for (int i = 0; i < numRows(); i++) {
                val = b.getVal(i);
                rowdiv = this->data_[i][i];
                for (int j = 0; j < this->numCols(); j++) {
                    if (i != j) {
                        val -=  this->data_[i][j] * y.getVal(j);
                    }
                }
                y.setVal(i, val/rowdiv);
            }
            iter++;
            Vector errorVec;
            errorVec.allocateData(y.numElems());
            for (int i = 0; i < y.numElems(); i++) {
                yValDif = y.getVal(i) - oldVec.getVal(i);
                errorVec.setVal(i, yValDif); 
            }
            error = abs(errorVec.l2norm()/y.l2norm());
        }
        this->time_.Stop();
        this->totalIters_ = iter;
        cout << "# of iterations: " << iter << endl;
        cout << "Wall-clock time (secs): " << this->time_.ElapsedTime() << endl;
        return y;
    } else { //wheeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
        this->time_.Start();
        while (error > 1e-8) {
            for (int k = 0; k < b.numElems(); k++) {
                oldVec.setVal(k, y.getVal(k));
            }
            for (int i = 0; i < numRows(); i++) {
                val = b.getVal(i);
                rowdiv = this->data_[i][i];
                for (int j = i - 1; j <= i + 1; j++) {
                    if (i != j) {
                        val -=  this->data_[i][j] * y.getVal(j);
                    }
                }
                y.setVal(i, val/rowdiv);
            }
            iter++;
            Vector errorVec;
            errorVec.allocateData(y.numElems());
            for (int i = 0; i < y.numElems(); i++) {
                yValDif = y.getVal(i) - oldVec.getVal(i);
                errorVec.setVal(i, yValDif); 
            }
            error = abs(errorVec.l2norm()/y.l2norm());
        }
        this->time_.Stop();
        this->totalIters_ = iter;
        cout << "# of iterations: " << iter << endl;
        cout << "Wall-clock time (secs): " << this->time_.ElapsedTime() << endl;
    }
    return y;
}

//Number of iterations required to solve
int Matrix::getSolveIters() {
    return this->totalIters_;
}

//Time required to solve
double Matrix::getSolveTime() {
    return this->time_.ElapsedTime();
}
