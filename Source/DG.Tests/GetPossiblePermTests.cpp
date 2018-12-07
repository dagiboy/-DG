#include "stdafx.h"

#include "../DG/CommonFunc.hpp"
#include "../DG/Matrix.hpp"

TEST(GetPossiblePermTests, Test1)
{
	std::string matrixStr = "{{1, 0, 0, 1}, {0, 1, 0, 1}, {1, 1, 1, 1}, {0, 0, 1, 0}};";
	Matrix matrix(matrixStr, 4);

	std::list<std::vector<int>> possiblePerm = GetPossiblePerm(matrix);
	std::list<std::vector<int>> truePossiblePerm = { { 0,1,3,2 },{ 0,3,1,2 },{ 3,1,0,2 } };

	ASSERT_EQ(possiblePerm.size(), truePossiblePerm.size());


	for (auto it1 = possiblePerm.begin(), it2 = truePossiblePerm.begin(); it1 != possiblePerm.end() && it2 != truePossiblePerm.end(); ++it1, ++it2)
	{
		ASSERT_EQ(it1->size(), it2->size());

		for (size_t j = 0; j < it1->size(); ++j)
			ASSERT_EQ((*it1)[j], (*it2)[j]);
	}

}


TEST(GetPossiblePermTests, Test2)
{
	std::string matrixStr = "{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 1}, {0, 0, 0, 1}};";
	Matrix matrix(matrixStr, 4);

	std::list<std::vector<int>> possiblePerm = GetPossiblePerm(matrix);
	std::list<std::vector<int>> truePossiblePerm = { { 0,1,2,3 } };

	ASSERT_EQ(possiblePerm.size(), truePossiblePerm.size());


	for (auto it1 = possiblePerm.begin(), it2 = truePossiblePerm.begin(); it1 != possiblePerm.end() && it2 != truePossiblePerm.end(); ++it1, ++it2)
	{
		ASSERT_EQ(it1->size(), it2->size());

		for (size_t j = 0; j < it1->size(); ++j)
			ASSERT_EQ((*it1)[j], (*it2)[j]);
	}

}

TEST(RandomTest, Test2)
{
	int size = 15;
	Matrix matr(size);
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
			matr[i][j] = rand() % 2;
	}

	auto f = GetPossiblePerm(matr);
	f.size();
}