#pragma once

#include "DGApi.hpp"

class Matrix
{
public:
	// —оздает нулевую матрицу размера size x size
	DG_API Matrix(int size);

	DG_API Matrix(double** matrix, int size);

	// matrix - строка, представл€юща€ матрицу, элементы которой сто€т через любой пробельный символ.
	// „исла типа double в строке должны записыватьс€ через точку, т.е 6.666, а не 6,666
	DG_API Matrix(std::string matrix, int size);
	DG_API Matrix(const Matrix& other);
	DG_API ~Matrix();

	DG_API int GetSize() const;

	DG_API Matrix operator=(const Matrix& other);
	DG_API double* operator[](int index) const;

	DG_API Matrix operator+(const Matrix& right) const;
	DG_API Matrix operator-(const Matrix& right) const;
	DG_API Matrix operator*(const Matrix& right) const;
	DG_API Matrix operator*(double number) const;
	DG_API Matrix friend operator*(double number, Matrix rightMatrix);
	
	DG_API std::string OutMatrix() const;
	DG_API bool Isnull() const;

private:
	void AllocateMatrix();
	void InitializeFrom(double** matrix, int size);
	void ClearMatrix() const;

	double **_matrix;
	int _size;
};