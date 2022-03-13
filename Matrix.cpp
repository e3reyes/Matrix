#include "Matrix.h"

Matrix::Matrix()
{
	rows = 0;
	cols = 0;

	mat = 0;
}


Matrix::Matrix(std::initializer_list<std::initializer_list<float>> newMat)
{
	rows = newMat.size();
	cols = newMat.begin()->size();

	mat = new float* [rows];

	for (int i = 0; i < rows; i++)
	{
		mat[i] = new float[cols];
		for (int j = 0; j < cols; j++)
		{
			mat[i][j] = ((newMat.begin() + i)->begin())[j];
		}
	}
}

Matrix::Matrix(int rows, int cols, bool random)
{
	this->rows = rows;
	this->cols = cols;
	mat = new float* [rows];

	for (int i = 0; i < rows; i++)
	{
		mat[i] = new float[cols];
		for (int j = 0; j < cols; j++)
		{
			if (random == false)
				mat[i][j] = 0;
			else
				mat[i][j] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		}
	}

}


Matrix::Matrix(int size)
{
	rows = size;
	cols = size;
	mat = new float* [rows];

	for (int i = 0; i < rows; i++)
	{
		mat[i] = new float[cols];
		for (int j = 0; j < cols; j++)
		{
			mat[i][j] = i == j ? (float)1 : (float)0;
		}
	}
}


Matrix::Matrix(const Matrix& mat)
{
	rows = mat.getRows();
	cols = mat.getCols();

	this->mat = new float* [rows];
	for (int i = 0; i < rows; i++)
	{
		this->mat[i] = new float[cols];

		for (int j = 0; j < cols; j++)
		{
			this->mat[i][j] = mat[i][j];
		}
	}
}


Matrix& Matrix::operator=(const Matrix& mat)
{

	if (this != &mat)
	{
		deleteMatrix();
		rows = mat.getRows();
		cols = mat.getCols();

		this->mat = new float* [rows];

		for (int i = 0; i < rows; i++)
		{
			this->mat[i] = new float[cols];
			for (int j = 0; j < cols; j++)
			{
				this->mat[i][j] = mat[i][j];
			}
		}
	}

	return *this;
}



float*& Matrix::operator[](int i) const
{
	return mat[i];
}



int Matrix::getRows() const
{
	return rows;
}


int Matrix::getCols() const
{
	return cols;
}



Matrix Matrix::operator+(const Matrix& mat)
{
	// empty matrix
	Matrix newMat(1, 1);
	// same size
	if (rows == mat.getRows() && cols == mat.getCols())
	{
		Matrix temp(rows, cols);
		newMat = temp;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				newMat[i][j] = this->mat[i][j] + mat[i][j];
			}
		}
	}
	return newMat;
}


Matrix Matrix::operator-(const Matrix& mat)
{

	// empty matrix
	Matrix newMat(1, 1);
	// same size
	if (rows == mat.getRows() && cols == mat.getCols())
	{
		Matrix temp(rows, cols);
		newMat = temp;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				newMat[i][j] = this->mat[i][j] - mat[i][j];
			}
		}
	}
	return newMat;
}


Matrix Matrix::operator*(const Matrix& mat)
{
	// if error
	if (cols != mat.getRows())
	{
		Matrix newMat(1, 1);
		return newMat;
	}

	Matrix newMat(this->getRows(), mat.getCols());
	// N X M * M X O = N X O



	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			for (int k = 0; k < mat.getCols(); k++)
			{
				newMat[i][k] += this->mat[i][j] * mat[j][k];
			}
		}
	}

	return newMat;
}


Matrix Matrix::transpose()
{
	Matrix newMat(cols, rows);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			newMat[j][i] = mat[i][j];
		}
	}

	return newMat;
}


Matrix Matrix::scale(float value)
{
	Matrix newMat(*this);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			newMat[i][j] *= value;
		}
	}
	return newMat;
}


void Matrix::deleteMatrix()
{
	for (int i = 0; i < rows; i++)
		delete[] mat[i];

	delete[] mat;
}


Matrix::~Matrix()
{
	deleteMatrix();
}


std::ostream& operator<<(std::ostream& os, const Matrix& mat)
{

	for (int i = 0; i < mat.getCols(); i++)
		os << std::setw(7) << std::setfill('-') << "";
	os << std::endl;
	for (int i = 0; i < mat.getRows(); i++)
	{
		os << "|";
		for (int j = 0; j < mat.getCols(); j++)
		{
			os << std::fixed << std::setprecision(2) << std::left << std::setw(6) << std::setfill(' ') << mat[i][j] << "|";
		}

		os << std::endl;

		for (int j = 0; j < mat.getCols(); j++)
			os << std::setw(7) << std::setfill('-') << "";

		os << std::endl;
	}

	return os;
}