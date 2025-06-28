#include <iostream>
using namespace std;
class Matrix
{
public:
	double matrix[10][10];
	Matrix() {
		this->name = "default";
		this->rows = 0;
		this->columns = 0;
	}
	Matrix(string name, int rows, int columns) {
		this->name = name;
		this->rows = rows;
		this->columns = columns;
	}
	void read() {
		cout << this->name << "\n";
		for (int i = 0;i < this->rows;i++)
		{
			for (int j = 0; j < this->columns; j++)
			{
				cout << "Element " << (i + 1) << "," << (j + 1) << ": ";
				cin >> this->matrix[i][j];
			}
		}
	}
	void display() {
		cout << this->name << "\n";
		for (int i = 0;i < this->rows;i++)
		{
			for (int j = 0; j < this->columns; j++)
			{
				cout << this->matrix[i][j] << "\t";
			}
			cout << endl;
		}
		cout << endl;
	}
	Matrix add(Matrix m) {
		Matrix result("result", this->rows, this->columns);
		if (this->rows != m.rows) {
			cout << "row barabar honi chahiye";
			exit(1);
		}
		if (this->columns != m.columns) {
			cout << "column barabar honi chahiye";
			exit(2);
		}

		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0;j < this->columns;j++) {
				result.matrix[i][j] = this->matrix[i][j] + m.matrix[i][j];
			}
		}
		return result;
	}
	Matrix sub(Matrix m) {
		Matrix result("result", this->rows, this->columns);
		if (this->rows != m.rows) {
			cout << "row barabar honi chahiye";
			exit(1);
		}
		if (this->columns != m.columns) {
			cout << "column barabar honi chahiye";
			exit(2);
		}

		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0;j < this->columns;j++) {
				result.matrix[i][j] = this->matrix[i][j] - m.matrix[i][j];
			}
		}
		return result;
	}
	Matrix operator +(Matrix m) {
		return this->add(m);
	}
	Matrix operator -(Matrix m) {
		return this->sub(m);
	}
	Matrix scalMultiply(double n) {
		Matrix result("result",this->rows,this->columns);
		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0;j < this->columns;j++) {
				result.matrix[i][j] = n*this->matrix[i][j];
			}
		}
		return result;
	}
	Matrix multiply(Matrix m) {
		if (this->columns != m.rows) {
			cout << "sahi matrix nahi aahe";
			exit(1);
		}
		Matrix result("result", this->rows, m.columns);
		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < m.columns; j++)
			{
				double sum = 0;
				for (int k = 0;k < this->columns;k++) {
					sum += this->matrix[i][k] * m.matrix[k][j];
				}
				result.matrix[i][j] = sum;
			}
		}
		return result;
	}
	Matrix operator *(Matrix m) {
		return this->multiply(m);
	}
	Matrix transpose() {
		Matrix result("result", this->columns, this->rows);
		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0;j < this->columns;j++) {
				result.matrix[j][i] = this->matrix[i][j];
			}
		}
		return result;
	}
	double determinant() {
		if (this->rows != this->columns) {
			cout << "Matrix Not Square";
			exit(1);
		}
		if (this->rows == 1 && this->columns == 1) {
			return this->matrix[0][0];
		}
		if (this->rows == 2 && this->columns == 2) {
			return this->matrix[0][0] * this->matrix[1][1] - this->matrix[1][0] * this->matrix[0][1];
		}
		double result = 0;
		for (int i = 0; i < this->columns; i++)
		{
			Matrix sub = this->subMatrix(0, i);
			result += ((i % 2 == 0) ? 1 : -1) * this->matrix[0][i] * sub.determinant();
		}
		return result;
	}
	Matrix subMatrix(int row, int col) {
	Matrix result("submatrix", this->rows - 1, this->columns - 1);
	for (int i = 0; i < this->rows; i++)
	{
		if (i != row) {
			for (int j = 0; j < this->columns; j++)
			{
				if (j == col)continue;
				result.matrix[(i > row) ? (i - 1) : i][(j > col) ? (j - 1) : j] = this->matrix[i][j];
			}
		}
	}
	return result;
	}
	Matrix minorMatrix() {
		
		Matrix result("result", this->rows, this->columns);
		if (this->rows!=this->columns) {
			cout << "not square matrix";
			exit(1);
		}
		if (this->columns == 1 && this->rows == 1) {
			result.matrix[0][0] = this->matrix[0][0];
			return result;
		}
		for (int i = 0; i < this->rows; i++) 
		{
			for (int j = 0; j < this->columns;j++) 
			{
				Matrix sub = this->subMatrix(i,j);
				result.matrix[i][j] = sub.determinant();
			}
		}
		return result;
	}
	Matrix cofactorMatrix() {
		Matrix m("m", this->rows, this->columns);
		m = this->minorMatrix();
		Matrix result("result",this->rows,this->columns);
		for (int i = 0; i < m.rows; i++)
		{
			for (int j = 0; j < m.columns; j++) {
				result.matrix[i][j] = (((i + j) % 2 == 0) ? 1 : -1) * m.matrix[i][j];
			}
		}
		return result;
	}
	Matrix	adj() {
		if (this->rows != this->columns) {
			cout << "not square matrix";
			exit(1);
		}
		Matrix result("result", this->rows, this->columns);
		result = this->cofactorMatrix();
		return result.transpose();
	}
	Matrix inv() {
		double m = this->determinant();
		if (this->rows != this->columns) {
			cout << "not square matrix";
			exit(1);
		}
		if (m==0) {
			cout << "singular matrix can't have inverse";
			return this->adj();
		}
		Matrix temp = this->adj();
		return temp/m;
	}
	Matrix solvingLinEqn(Matrix m) {
		Matrix result("result",this->rows,m.columns);
		if (this->rows != m.rows) {
			cout << "row barabar honi chahiye";
			exit(1);
		}
		if (m.columns > 1 || m.rows != this->rows)
		{
			cout << "case invalid";
			exit(2);
		}
		result = this->inv();
		return result.multiply(m);
	}
	Matrix operator *(double n) {
		return this->scalMultiply(n);
	}
	Matrix operator /(double n) {
		Matrix result("result", this->rows, this->columns);
		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0;j < this->columns;j++) {
				result.matrix[i][j] = this->matrix[i][j] / n;
			}
		}
		return result;
	}
	Matrix magicSquare(int n) {
		Matrix mat("Magic Square", n + 2, n + 2);
		if (!n % 2)
		{
			exit(1);
		}
		int nhalf = (n+1)/2;
		int nquart = (nhalf + 1) / 2;
		for (int i = 0; i < mat.rows ; i++)
		{
			for (int j = 0;i < mat.columns; j++) {
				if (j == 0) {
					if (i == nhalf) {}
				}
			}
		}
		return mat;
	}
	private:
	string name;
	int rows = 0;
	int columns = 0;
};
