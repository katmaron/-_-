#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Matrix
{
public:

    int numRows, numCols;
    double** matrix;

    Matrix() {
        numRows = 0;
        numCols = 0;
        matrix = NULL;
    }

    Matrix(int r, int c): numRows(r), numCols(c) {
        matrix = new double* [numRows];

        for (int row = 0; row < numRows; row++) {
            matrix[row] = new double[numCols];
        }
    }

    Matrix operator + (const Matrix& m) {
        Matrix result(m.numRows, m.numCols);
        for (int row = 0; row < numRows; row++) {
            for (int col = 0; col < numCols; col++) {
                result.matrix[row][col] = matrix[row][col] + m.matrix[row][col];
            }
        }
        return result;
    }

    Matrix operator - (const Matrix& m) {
        Matrix result(m.numRows, m.numCols);
        for (int row = 0; row < numRows; row++) {
            for (int col = 0; col < numCols; col++) {
                result.matrix[row][col] = matrix[row][col] - m.matrix[row][col];
            }
        }
        return result;
    }

    Matrix operator * (const Matrix& m) {
        Matrix result(numRows, m.numCols);
        // initialization to 0
        for (int row = 0; row < result.numRows; row++) {
            for (int col = 0; col < result.numCols; col++) {
                result.matrix[row][col] = 0;
            }
        }

        //actual multiplication
        for (int row = 0; row < numRows; row++) {
            for (int col = 0; col < m.numCols; col++) {
                for (int k = 0; k < numCols; k++) {
                    result.matrix[row][col] += matrix[row][k] * m.matrix[k][col];
                }
            }
        }

        return result;
    }

    void printMatrix() {
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void resize(int nr, int nc) {
        // cleaning the memory
        for (int i = 0; i < numRows; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;

        // creating a new matrix
        numRows = nr;
        numCols = nc;
        
        matrix = new double* [numRows];

        for (int row = 0; row < numRows; row++) {
            matrix[row] = new double[numCols];
        }
    }

    ~Matrix() {
        for (int i = 0; i < numRows; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
};

void readFromFile(Matrix &a, Matrix &b) {
    string filename;
    cout << "The file must contain data in the form of:" << endl;
    cout << "QuantityNumberA and number of columns, then the content of matrix A" << endl << "Then the same for matrix B" << endl;

    cout << "Specify the name of the file containing the data (example attached file is input.txt): ";
    cin >> filename;

    ifstream file;
    file.open(filename, ios::in);


    int numRowsA, numColsA;
    int numRowsB, numColsB;

    // loading the size of the first
    file >> numRowsA >> numColsA;
    a.resize(numRowsA, numColsA);
    // loading the contents of the first
    for (int i = 0; i < numRowsA; i++) {
        for (int j = 0; j < numColsA; j++) {
            file >> a.matrix[i][j];
        }
    }

    // loading the size of the second
    file >> numRowsB >> numColsB;
    b.resize(numRowsB, numColsB);
    // loading the content of the second
    for (int i = 0; i < numRowsB; i++) {
        for (int j = 0; j < numColsB; j++) {
            file >> b.matrix[i][j];
        }
    }

    file.close();
}

void readFromKeyboard(Matrix& a, Matrix& b) {
    cout << "Enter data in the form: quantityNumberA and quantityColumnA, then the content of matrix A" << endl << "Then the same for matrix B" << endl;
    int numRowsA, numColsA;
    int numRowsB, numColsB;

    // loading the size of the first
    cin >> numRowsA >> numColsA;
    a.resize(numRowsA, numColsA);
    // loading the contents of the first
    for (int i = 0; i < numRowsA; i++) {
        for (int j = 0; j < numColsA; j++) {
            cin >> a.matrix[i][j];
        }
    }

    // loading the size of the second
    cin >> numRowsB >> numColsB;
    b.resize(numRowsB, numColsB);
    // loading the content of the second
    for (int i = 0; i < numRowsB; i++) {
        for (int j = 0; j < numColsB; j++) {
            cin >> b.matrix[i][j];
        }
    }
}


int main()
{
    char choice;
    Matrix a, b;
    Matrix result;

    cout << "Hello" << endl << "Do you want to enter matrices from a file or keyboard?" << endl;
    cout << "1- file" << endl << "2- keyboard" << endl;
    cin >> choice;
    // loading data
    switch (choice) {
    case '1':
        readFromFile(a, b);
        break;
    case '2':
        readFromKeyboard(a, b);
        break;
    default:
        cout << "wrong option !!!!" << endl;
        return 0;
    }


    cout << "What operation do you want to perform on these arrays?" << endl;
    cout << "1- addition" << endl << "2- subtraction" << endl << "3- multiplication" << endl;
    cin >> choice;
    // performing the appropriate operation on the arrays
    switch (choice) {
    case '1':
        if (a.numRows != b.numRows || a.numCols != b.numCols) {
            cout << " Inappropriate matrix sizes!!!" << endl;
            return 0;
        }
        result = a + b;
        break;
    case'2':
        if (a.numRows != b.numRows || a.numCols != b.numCols) {
            cout << " Inappropriate matrix sizes!!!" << endl;
            return 0;
        }
        result = a - b;
        break;
    case '3':
        if (a.numCols != b.numRows) {
            cout << " Inappropriate matrix sizes!!!" << endl;
            return 0;
        }
        result = a * b;
        break;
    default:
        cout << "wrong option !!!!" << endl;
        return 0;
    }

    // writing out the result
    result.printMatrix();


    return 0;
}
