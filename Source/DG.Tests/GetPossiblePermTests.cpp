#include "stdafx.h"

#include "../DG/CommonFunc.hpp"
#include "../DG/Matrix.hpp"

TEST(RandomTest, Test2)
{
	Matrix matrix("{{5, 5, 2, 3}, {4, 3, 6, 2}, {2, 5, 3, 5}, {4, 2, 4, 5}}", 4);
	auto permDecomp = GetPermDecomposition(matrix);

	for (size_t i = 0; i < permDecomp.size(); ++i)
	{
		std::cout << permDecomp[i].first << std::endl << GetPermMatrix(permDecomp[i].second).OutMatrix() << "\n";
	}
	

}