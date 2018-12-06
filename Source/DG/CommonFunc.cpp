#include "stdafx.h"

#include "CommonFunc.hpp"

Matrix GetBitMatrix(const Matrix &matr, double b)
{
	int size = matr.GetSize();
	Matrix result(size);
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
			result[i][j] = matr[i][j] >= b ? 1 : 0;
	}

	return result;
}

double Minmax(const Matrix& matr)
{
	int size = matr.GetSize();
	double maxInStr;
	double minmax = DBL_MAX;

	for (int i = 0; i < size; ++i)
	{
		maxInStr = matr[i][0];
		for (int j = 0; j < size; ++j)
		{
			if (matr[i][j] > maxInStr)
				maxInStr = matr[i][j];
		}

		if (maxInStr < minmax)
			minmax = maxInStr;
	}
	
	return minmax;
}