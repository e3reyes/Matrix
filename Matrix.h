#include <initializer_list>
#include <iostream>
#include <iomanip>

#ifndef MATRIX_float_H
#define MATRIX_float_H


class Matrix
{
	friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);


public:
	Matrix();
	Matrix(std::initializer_list<std::initializer_list<float>> newMat);

	Matrix(int rows, int cols, bool random = false);
	// create identy matrix with row cols
	Matrix(int size);
	// copy constructor
	Matrix(const Matrix& mat);

	Matrix& operator=(const Matrix& mat);

	float*& operator[](int i) const;




	int getRows() const;
	int getCols() const;

	// operations
	Matrix operator+(const Matrix& mat);
	Matrix operator-(const Matrix& mat);
	Matrix operator*(const Matrix& mat);


	Matrix transpose();
	Matrix scale(float value);


	~Matrix();

protected:
private:
	float** mat;
	int rows;
	int cols;


	void deleteMatrix();
};


#endif
