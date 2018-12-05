#pragma once

#include "DGApi.hpp"

#include <string>

class Matrix
{
public:
	DG_API Matrix(int size);

	// matr - строка, представл€юща€ матрицу, элементы которой сто€т через любой пробельный символ.
	DG_API Matrix(std::string matr, int size);
	DG_API Matrix(const Matrix& other);
	DG_API ~Matrix();

	int DG_API GetSize() const;

	Matrix DG_API friend operator +(Matrix lMatr, Matrix rRmatr);
	Matrix DG_API friend operator *(Matrix lMatr, Matrix rRmatr);
	Matrix DG_API friend operator *(Matrix lMatr, double num);
	Matrix DG_API friend operator *(double num, Matrix rRmatr);	
	Matrix DG_API operator = (const Matrix& other);
	double * DG_API operator [](int index);

private:
	double **_matr;
	int _size;
};
