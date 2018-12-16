#include "stdafx.h"

#include "CommonFunc.hpp"

using namespace std;

// К левому вектору прибавляет правый вектор
void AddToVector(vector<double> &l, vector<double> &r)
{
	if (l.size() != r.size())
		throw;

	for (size_t i = 0; i < l.size(); ++i)
		l[i] += r[i];
}

// Реализует перестанку п
BYTE GetPi(int num)
{
	BYTE result = 0;

	result |= (num & 1);
	result |= (num & 2) * 2;
	result |= (num & 4) * 4;
	result |= (num & 8) * 8;
	result |= (num & 16) / 8;
	result |= (num & 32) / 4;
	result |= (num & 64) / 2;
	result |= (num & 128);

	return result;
}

// Получает произведение вектора слева на тензорное произведение 2х перестановочных матриц
vector<double> GetVectorOnTensorProduct(vector<double>& vect, vector<int> lPerm, vector<int> rPerm)
{
	if (vect.size() != lPerm.size() * rPerm.size())
		throw;

	if (lPerm.size() != rPerm.size())
		throw;
	
	vector<double> result(vect.size());
	int k = lPerm.size();

	for (size_t i = 0; i < vect.size(); ++i)
		result[lPerm[i / k]*k + rPerm[i % k]] = vect[i];

	return result;
}

// Производит умножение каждой координаты вектора на число
void ProductVectorToNum(vector<double>& vect, double num)
{
	for (size_t i = 0; i < vect.size(); ++i)
		vect[i] *= num;
}

// Вычислет вроизведение вектора слева на матрицу P=(lPxrP).П(п)
vector<double> GetVectorProduct(vector<double> &vect, Matrix& lP, Matrix& rP)
{
	if ((int)vect.size() != lP.GetSize() * rP.GetSize())
		throw;

	if (lP.GetSize() != rP.GetSize())
		throw;

	vector<double> tmp(vect.size());

	// Получаем разложение матрицы на линейную сумму перестановочных матриц.
	auto lDecomp = GetPermDecomposition(lP);
	auto rDecomp = GetPermDecomposition(rP);

	for (size_t i = 0; i < lDecomp.size(); ++i)
	{
		for (size_t j = 0; j < rDecomp.size(); ++j)
		{
			// Находим каждый член линейного разложения умноженного на данный вектор
			vector<double> product = GetVectorOnTensorProduct(vect, lDecomp[i].second, rDecomp[j].second);
			ProductVectorToNum(product, lDecomp[i].first);
			ProductVectorToNum(product, rDecomp[j].first);

			// Суммируем получившийся вектор к результату.
			AddToVector(tmp, product);
		}
	}

	// Умножаем результат на матрицу П(п)
	vector<double> result(vect.size());
	for (size_t i = 0; i < result.size(); ++i)
		result[GetPi(i)] = tmp[i];
	
	return result;
}