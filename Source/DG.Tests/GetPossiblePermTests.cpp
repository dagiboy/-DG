#include "stdafx.h"

#include "../DG/CommonFunc.hpp"
#include "../DG/Matrix.hpp"

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

TEST(RandomTest, Test2)
{
	Matrix matrix("{{5, 5, 2, 3}, {4, 3, 6, 2}, {2, 5, 3, 5}, {4, 2, 4, 5}}", 4);
	auto permDecomp = GetPermDecomposition(matrix);

	for (size_t i = 0; i < permDecomp.size(); ++i)
	{
		std::cout << permDecomp[i].first << std::endl << GetPermMatrix(permDecomp[i].second).OutMatrix() << "\n";
	}
}