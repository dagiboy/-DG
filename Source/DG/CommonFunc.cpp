#include "stdafx.h"

#include "CommonFunc.hpp"

using namespace std;

// Находит матрицу B где B[i][j] = matr[i][j] >= b ? 1 : 0
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

// Находим минимакс матрицы
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

// Получаем перестановочную матрицу
Matrix GetPermMatrix(const vector<int>& perm)
{
	int size = perm.size();
	Matrix result(size);
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
			result[i][j] = perm[i] == j ? 1 : 0;
	}

	return result;
}

// Находит раложение матрицы на линейную сумму перестановочных матриц.
vector<pair<double, vector<int>>> GetPermDecomposition(const Matrix& matrix)
{
	vector<pair<double, vector<int>>> result;
	if (matrix.Isnull())
		return result;

	vector<int> perm;
	double b = Minmax(matrix) + 1;

	while (b != 0 && perm.size() == 0)
	{
		b = b - 1;
		if (b == 0)
			throw runtime_error("Can't decomp matrix");

		perm = GetPossiblePerm(GetBitMatrix(matrix, b));
	}

	Matrix P = GetPermMatrix(perm);
	Matrix C = matrix - b * P;
	result.push_back(pair<double, vector<int>>(b, perm));
	auto nextDecomp = GetPermDecomposition(C);
	for (size_t i = 0; i < nextDecomp.size(); ++i)
		result.push_back(nextDecomp[i]);

	return result;

}