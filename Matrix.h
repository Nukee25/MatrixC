#include <iostream>
using namespace std;

/**
 * @brief A class representing a mathematical matrix and its operations
 *
 * This class implements various matrix operations including:
 * - Basic arithmetic (addition, subtraction, multiplication)
 * - Matrix transformations (transpose, inverse)
 * - Matrix properties (determinant)
 * - Linear equation solving
 *
 * @note Matrix dimensions are limited to 10x10
 */
class Matrix {
public:
    double matrix[10][10];  ///< The 2D array storing matrix elements

private:
    string name;     ///< Name identifier for the matrix
    int rows;        ///< Number of rows in the matrix
    int columns;     ///< Number of columns in the matrix

public:
    /**
     * @brief Default constructor
     * Creates a matrix with default name and 0x0 dimensions
     */
    Matrix() {
        this->name = "default";
        this->rows = 0;
        this->columns = 0;
    }

    /**
     * @brief Parameterized constructor
     * @param name Matrix identifier
     * @param rows Number of rows
     * @param columns Number of columns
     */
    Matrix(string name, int rows, int columns) {
        this->name = name;
        this->rows = rows;
        this->columns = columns;
    }

    /**
     * @brief Reads matrix elements from user input
     */
    void read() {
        cout << this->name << "\n";
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                cout << "Element " << (i + 1) << "," << (j + 1) << ": ";
                cin >> this->matrix[i][j];
            }
        }
    }

    /**
     * @brief Displays the matrix contents
     */
    void display() {
        cout << this->name << "\n";
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                cout << this->matrix[i][j] << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }

    /**
     * @brief Adds two matrices
     * @param m Matrix to add to this matrix
     * @return Result matrix
     * @throws Runtime error if dimensions don't match
     */
    Matrix add(Matrix m) {
        Matrix result("result", this->rows, this->columns);
        if (this->rows != m.rows) {
            cout << "Error: Rows must be equal for addition";
            exit(1);
        }
        if (this->columns != m.columns) {
            cout << "Error: Columns must be equal for addition";
            exit(2);
        }

        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                result.matrix[i][j] = this->matrix[i][j] + m.matrix[i][j];
            }
        }
        return result;
    }

    /**
     * @brief Subtracts two matrices
     * @param m Matrix to subtract from this matrix
     * @return Result matrix
     * @throws Runtime error if dimensions don't match
     */
    Matrix sub(Matrix m) {
        Matrix result("result", this->rows, this->columns);
        if (this->rows != m.rows) {
            cout << "Error: Rows must be equal for subtraction";
            exit(1);
        }
        if (this->columns != m.columns) {
            cout << "Error: Columns must be equal for subtraction";
            exit(2);
        }

        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                result.matrix[i][j] = this->matrix[i][j] - m.matrix[i][j];
            }
        }
        return result;
    }

    /**
     * @brief Addition operator overload
     * @param m Matrix to add
     * @return Result matrix
     */
    Matrix operator +(Matrix m) {
        return this->add(m);
    }

    /**
     * @brief Subtraction operator overload
     * @param m Matrix to subtract
     * @return Result matrix
     */
    Matrix operator -(Matrix m) {
        return this->sub(m);
    }

    /**
     * @brief Multiplies matrix by a scalar
     * @param n Scalar multiplier
     * @return Result matrix
     */
    Matrix scalMultiply(double n) {
        Matrix result("result", this->rows, this->columns);
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                result.matrix[i][j] = n * this->matrix[i][j];
            }
        }
        return result;
    }

    /**
     * @brief Multiplies two matrices
     * @param m Matrix to multiply with
     * @return Result matrix
     * @throws Runtime error if dimensions are incompatible
     */
    Matrix multiply(Matrix m) {
        if (this->columns != m.rows) {
            cout << "Error: Invalid matrix dimensions for multiplication";
            exit(1);
        }
        Matrix result("result", this->rows, m.columns);
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < m.columns; j++) {
                double sum = 0;
                for (int k = 0; k < this->columns; k++) {
                    sum += this->matrix[i][k] * m.matrix[k][j];
                }
                result.matrix[i][j] = sum;
            }
        }
        return result;
    }

    /**
     * @brief Multiplication operator overload
     * @param m Matrix to multiply with
     * @return Result matrix
     */
    Matrix operator *(Matrix m) {
        return this->multiply(m);
    }

    /**
     * @brief Calculates matrix transpose
     * @return Transposed matrix
     */
    Matrix transpose() {
        Matrix result("result", this->columns, this->rows);
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                result.matrix[j][i] = this->matrix[i][j];
            }
        }
        return result;
    }

    /**
     * @brief Calculates matrix determinant
     * @return Determinant value
     * @throws Runtime error if matrix is not square
     */
    double determinant() {
        if (this->rows != this->columns) {
            cout << "Error: Matrix must be square to calculate determinant";
            exit(1);
        }
        if (this->rows == 1 && this->columns == 1) {
            return this->matrix[0][0];
        }
        if (this->rows == 2 && this->columns == 2) {
            return this->matrix[0][0] * this->matrix[1][1] - this->matrix[1][0] * this->matrix[0][1];
        }
        double result = 0;
        for (int i = 0; i < this->columns; i++) {
            Matrix sub = this->subMatrix(0, i);
            result += ((i % 2 == 0) ? 1 : -1) * this->matrix[0][i] * sub.determinant();
        }
        return result;
    }

    /**
     * @brief Creates a submatrix by removing specified row and column
     * @param row Row to remove
     * @param col Column to remove
     * @return Resulting submatrix
     */
    Matrix subMatrix(int row, int col) {
        Matrix result("submatrix", this->rows - 1, this->columns - 1);
        for (int i = 0; i < this->rows; i++) {
            if (i != row) {
                for (int j = 0; j < this->columns; j++) {
                    if (j == col) continue;
                    result.matrix[(i > row) ? (i - 1) : i][(j > col) ? (j - 1) : j] = this->matrix[i][j];
                }
            }
        }
        return result;
    }

    /**
     * @brief Calculates the minor matrix
     * @return Minor matrix
     * @throws Runtime error if matrix is not square
     */
    Matrix minorMatrix() {
        Matrix result("result", this->rows, this->columns);
        if (this->rows != this->columns) {
            cout << "Error: Matrix must be square";
            exit(1);
        }
        if (this->columns == 1 && this->rows == 1) {
            result.matrix[0][0] = this->matrix[0][0];
            return result;
        }
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                Matrix sub = this->subMatrix(i, j);
                result.matrix[i][j] = sub.determinant();
            }
        }
        return result;
    }

    /**
     * @brief Calculates the cofactor matrix
     * @return Cofactor matrix
     */
    Matrix cofactorMatrix() {
        Matrix m("m", this->rows, this->columns);
        m = this->minorMatrix();
        Matrix result("result", this->rows, this->columns);
        for (int i = 0; i < m.rows; i++) {
            for (int j = 0; j < m.columns; j++) {
                result.matrix[i][j] = (((i + j) % 2 == 0) ? 1 : -1) * m.matrix[i][j];
            }
        }
        return result;
    }

    /**
     * @brief Calculates matrix adjoint
     * @return Adjoint matrix
     * @throws Runtime error if matrix is not square
     */
    Matrix adj() {
        if (this->rows != this->columns) {
            cout << "Error: Matrix must be square";
            exit(1);
        }
        Matrix result("result", this->rows, this->columns);
        result = this->cofactorMatrix();
        return result.transpose();
    }

    /**
     * @brief Calculates matrix inverse
     * @return Inverse matrix
     * @throws Runtime error if matrix is singular or not square
     */
    Matrix inv() {
        double m = this->determinant();
        if (this->rows != this->columns) {
            cout << "Error: Matrix must be square";
            exit(1);
        }
        if (m == 0) {
            cout << "Error: Singular matrix cannot have inverse";
            return this->adj();
        }
        Matrix temp = this->adj();
        return temp / m;
    }

    /**
     * @brief Solves system of linear equations Ax = b
     * @param m Matrix b in Ax = b
     * @return Solution matrix x
     * @throws Runtime error if dimensions are incompatible
     */
    Matrix solvingLinEqn(Matrix m) {
        Matrix result("result", this->rows, m.columns);
        if (this->rows != m.rows) {
            cout << "Error: Number of rows must match";
            exit(1);
        }
        if (m.columns > 1 || m.rows != this->rows) {
            cout << "Error: Invalid case";
            exit(2);
        }
        result = this->inv();
        return result.multiply(m);
    }

    /**
     * @brief Scalar multiplication operator overload
     * @param n Scalar multiplier
     * @return Result matrix
     */
    Matrix operator *(double n) {
        return this->scalMultiply(n);
    }

    /**
     * @brief Scalar division operator overload
     * @param n Scalar divisor
     * @return Result matrix
     */
    Matrix operator /(double n) {
        Matrix result("result", this->rows, this->columns);
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                result.matrix[i][j] = this->matrix[i][j] / n;
            }
        }
        return result;
    }
};