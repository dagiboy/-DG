#include "stdafx.h"

#include "CommonFunc.hpp"

using namespace std;

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

bool GetAllPerm(const vector<vector<int>>& positionList, vector<vector<int>>& possiblePerm, size_t recursionLevel = 0, vector<int> curentPerm = {})
{
	if (recursionLevel >= positionList.size())
	{
		possiblePerm.push_back(curentPerm);
		return true;
	}
	else
	{
		for (size_t i = 0; i < positionList[recursionLevel].size(); ++i)
		{
			if (find(curentPerm.begin(), curentPerm.end(), positionList[recursionLevel][i]) == curentPerm.end())
			{
				curentPerm.push_back(positionList[recursionLevel][i]);
				if (GetAllPerm(positionList, possiblePerm, recursionLevel + 1, curentPerm))
					return true;
				curentPerm.pop_back();
			}
		}
	}
	return false;
}

// На вход функция получает матрицу, состоящую из 0 и 1.
// Функция должна вернуть список перестановок, матрицы которых меньше или равна входной матрице.
vector<vector<int>> GetPossiblePerm(const Matrix& matr)
{
	//Для каждой строчки найдем номера позиций на которых стоян не нулевые элементы
	vector<vector<int>> posList;
	int matrixSize = matr.GetSize();

	for (int i = 0; i < matrixSize; ++i)
	{
		vector<int> vect;

		for (int j = 0; j < matrixSize; ++j)
		{
			if (abs(matr[i][j] - 1) < DBL_EPSILON)
				vect.push_back(j);
		}

		posList.push_back(vect);
	}

	vector<vector<int>> possiblePerm;
	GetAllPerm(posList, possiblePerm);

	return possiblePerm;
}

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

vector<pair<double, vector<int>>> GetPermDecomposition(const Matrix& matrix)
{
	vector<pair<double, vector<int>>> result;
	if (matrix.Isnull())
		return result;

	vector<vector<int>> perms;
	double b = Minmax(matrix) + 1;

	while (b != 0 && perms.size() == 0)
	{
		b = b - 1;
		if (b == 0)
			throw runtime_error("Can't decomp matrix");

		perms = GetPossiblePerm(GetBitMatrix(matrix, b));
	}

	vector<int> perm = perms[0];
	Matrix P = GetPermMatrix(perm);
	Matrix C = matrix - b * P;
	result.push_back(pair<double, vector<int>>(b, perm));
	auto nextDecomp = GetPermDecomposition(C);
	for (size_t i = 0; i < nextDecomp.size(); ++i)
		result.push_back(nextDecomp[i]);

	return result;

}