#include "stdafx.h"

#include "CommonFunc.hpp"

using namespace std;

void AddToVector(vector<double> &l, vector<double> &r)
{
	if (l.size() != r.size())
		throw;

	for (size_t i = 0; i < l.size(); ++i)
		l[i] += r[i];
}

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

void ProductVectorToNum(vector<double>& vect, double num)
{
	for (size_t i = 0; i < vect.size(); ++i)
		vect[i] *= num;
}

vector<double> GetVectorProduct(vector<double> &vect, Matrix& lP, Matrix& rP)
{
	if ((int)vect.size() != lP.GetSize() * rP.GetSize())
		throw;

	if (lP.GetSize() != rP.GetSize())
		throw;

	vector<double> tmp(vect.size());

	auto lDecomp = GetPermDecomposition(lP);
	auto rDecomp = GetPermDecomposition(rP);

	for (size_t i = 0; i < lDecomp.size(); ++i)
	{
		for (size_t j = 0; j < rDecomp.size(); ++j)
		{
			vector<double> product = GetVectorOnTensorProduct(vect, lDecomp[i].second, rDecomp[j].second);
			ProductVectorToNum(product, lDecomp[i].first);
			ProductVectorToNum(product, rDecomp[j].first);

			AddToVector(tmp, product);
		}
	}

	vector<double> result(vect.size());
	for (size_t i = 0; i < result.size(); ++i)
		result[GetPi(i)] = tmp[i];
	
	return result;
}