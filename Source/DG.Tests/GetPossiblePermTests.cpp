#include "stdafx.h"

#include "../DG/CommonFunc.hpp"
#include "../DG/Matrix.hpp"

using namespace std;

TEST(RandomTest, Test1)
{
	Matrix matrix("{{0,1,1,0}, {0,0,0,1}, {1,0,0,0}, {0,1,1,0}}", 4);
	std::vector<int> expectedPerm = { 1,3,0,2 };
	auto posPerm= GetPossiblePerm(matrix);

	for (size_t i = 0; i < posPerm.size(); ++i)
	{
		ASSERT_EQ(posPerm[i], expectedPerm[i]);
	}
}

TEST(GetPermDecompositionTest, Test2)
{
	string lPstr = (string)
		"{{8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }," +
		"{ 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1 }, " +
		"{ 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 2 }," +
		"{ 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 2, 0 }," +
		"{ 0, 1, 1, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 1, 1, 0 }," +
		"{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 1, 1, 1, 1 }," +
		"{ 0, 1, 0, 0, 1, 0, 0, 2, 0, 1, 0, 0, 1, 2, 0, 0 }," +
		"{ 0, 0, 0, 1, 0, 1, 0, 2, 1, 0, 0, 0, 0, 0, 1, 2 }," +
		"{ 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0 }, " +
		"{ 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 2, 0, 0, 0, 0, 1 }, " +
		"{ 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 2, 1, 0, 0, 0, 0 }, " +
		"{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 2, 1, 0, 1, 0 }," +
		"{ 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0 }, " +
		"{ 0, 0, 1, 0, 2, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1 }, " +
		"{ 0, 2, 1, 1, 0, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 }," +
		"{ 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 2, 0, 0 }}";

	string rPstr = (string)
		"{{8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }," +
		"{ 0, 1, 0, 2, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 2 }, " +
		"{ 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 2, 1, 0, 0, 0 }," +
		"{ 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 2, 0, 0, 1, 0, 1 }," +
		"{ 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 2 }," +
		"{ 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 2, 0, 1, 0 }," +
		"{ 0, 2, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1 }," +
		"{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 0, 1, 1, 2, 0 }," +
		"{ 0, 0, 1, 1, 1, 1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0 }, " +
		"{ 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0 }, " +
		"{ 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1 }, " +
		"{ 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 2, 0, 0, 0 }," +
		"{ 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0 }, " +
		"{ 0, 0, 1, 2, 0, 0, 0, 1, 1, 0, 0, 2, 0, 1, 0, 0 }, " +
		"{ 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 2, 1, 0 }," +
		"{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 1, 0, 1, 2, 1 }}";

	Matrix lP(lPstr, 16);
	Matrix rP(rPstr, 16);

	auto lDecomp = GetPermDecomposition(lP);
	auto rDecomp = GetPermDecomposition(rP);

	Matrix lTest(16);
	Matrix rTest(16);

	for (size_t i = 0; i < lDecomp.size(); ++i)
	{
		lTest = lTest + lDecomp[i].first * GetPermMatrix(lDecomp[i].second);
		rTest = rTest + rDecomp[i].first * GetPermMatrix(rDecomp[i].second);
	}

	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 16; ++j)
		{
			ASSERT_EQ(lTest[i][j], lP[i][j]);
			ASSERT_EQ(rTest[i][j], rP[i][j]);
		}
	}
}

// ������ ������ ������� ������� P ����������� � 4�� �������
TEST(FindSecondStr, Test1)
{
	string lPstr = (string)
		"{{8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }," +
		"{ 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1 }, " +
		"{ 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 2 }," +
		"{ 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 2, 0 }," +
		"{ 0, 1, 1, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 1, 1, 0 }," +
		"{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 1, 1, 1, 1 }," +
		"{ 0, 1, 0, 0, 1, 0, 0, 2, 0, 1, 0, 0, 1, 2, 0, 0 }," +
		"{ 0, 0, 0, 1, 0, 1, 0, 2, 1, 0, 0, 0, 0, 0, 1, 2 }," +
		"{ 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0 }, " +
		"{ 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 2, 0, 0, 0, 0, 1 }, " +
		"{ 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 2, 1, 0, 0, 0, 0 }, " +
		"{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 2, 1, 0, 1, 0 }," +
		"{ 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0 }, " +
		"{ 0, 0, 1, 0, 2, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1 }, " +
		"{ 0, 2, 1, 1, 0, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 }," +
		"{ 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 2, 0, 0 }}";

	string rPstr = (string)
		"{{8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }," +
		"{ 0, 1, 0, 2, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 2 }, " +
		"{ 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 2, 1, 0, 0, 0 }," +
		"{ 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 2, 0, 0, 1, 0, 1 }," +
		"{ 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 2 }," +
		"{ 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 2, 0, 1, 0 }," +
		"{ 0, 2, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1 }," +
		"{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 0, 1, 1, 2, 0 }," +
		"{ 0, 0, 1, 1, 1, 1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0 }, " +
		"{ 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0 }, " +
		"{ 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1 }, " +
		"{ 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 2, 0, 0, 0 }," +
		"{ 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0 }, " +
		"{ 0, 0, 1, 2, 0, 0, 0, 1, 1, 0, 0, 2, 0, 1, 0, 0 }, " +
		"{ 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 2, 1, 0 }," +
		"{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 1, 0, 1, 2, 1 }}";

	Matrix lP(lPstr, 16);
	Matrix rP(rPstr, 16);

	vector<double> e1(256);
	e1[1] = 1;
	e1 = GetVectorProduct(e1, lP, rP);
	e1 = GetVectorProduct(e1, lP, rP);
	e1 = GetVectorProduct(e1, lP, rP);
	e1 = GetVectorProduct(e1, lP, rP);

	for (size_t i = 0; i < 256; ++i)
		cout << e1[i] << ' ';
}