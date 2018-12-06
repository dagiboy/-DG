#include "stdafx.h"

#include "../DG/Matrix.hpp"

void DeleteMatrixArr(double** arr, int size)
{
	for (int i = 0; i < size; ++i)
		delete[] arr[i];

	delete[] arr;
}

TEST(MatrixTests, Test1)
{
	try
	{
		Matrix matrix1(-10);

		FAIL() << "Expected std::runtime_error";
	}
	catch (std::runtime_error &e)
	{
		ASSERT_STREQ("Invalid size!", e.what());
	}

	try
	{
		Matrix matrix2(0);

		FAIL() << "Expected std::runtime_error";
	}
	catch (std::runtime_error &e)
	{
		ASSERT_STREQ("Invalid size!", e.what());
	}

	Matrix matrix3(3);

	ASSERT_EQ(3, matrix3.GetSize());

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			ASSERT_DOUBLE_EQ(0, matrix3[i][j]);
}

TEST(MatrixTests, Test2)
{
	double arr[3][3] =
	{
		{ 1, 2, 3 },
		{ 2, 4, 6 },
		{ 7, 8, 9 }
	};

	double** arrInHeap = new double*[3];

	for (int i = 0; i < 3; ++i)
		arrInHeap[i] = new double[3];

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			arrInHeap[i][j] = arr[i][j];

	Matrix matrix1(arrInHeap, 3);

	ASSERT_EQ(3, matrix1.GetSize());

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			ASSERT_DOUBLE_EQ(arr[i][j], matrix1[i][j]);

	Matrix matrix2(matrix1);

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			ASSERT_DOUBLE_EQ(matrix1[i][j], matrix2[i][j]);

	Matrix matrix3 = matrix1;

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			ASSERT_DOUBLE_EQ(matrix1[i][j], matrix3[i][j]);

	matrix3 = matrix3;

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			ASSERT_DOUBLE_EQ(matrix1[i][j], matrix3[i][j]);

	DeleteMatrixArr(arrInHeap, 3);
}

TEST(MatrixTests, Test3)
{
	double arr1[3][3] = 
	{ 
		{ 1, 2, 3 },
		{ 2, 4, 6 },
		{ 7, 8, 9 }
	};

	double arr2[3][3] = 
	{ 
		{ 5, 4, 3 },
		{ 1, 4, 1 },
		{ 7, 8, 9 } 
	};

	double sumArr[3][3] = 
	{ 
		{ 6, 6, 6 },
		{ 3, 8, 7 },
		{ 14, 16, 18 } 
	};

	double productArr1[3][3] = 
	{
		{ 28, 36, 32 },
		{ 56, 72, 64 },
		{ 106, 132, 110 }
	};

	double productArr2[3][3] =
	{
		{ 34, 50, 66 },
		{ 16, 26, 36 },
		{ 86, 118, 150 }
	};

	double** arrInHeap1 = new double*[3];
	double** arrInHeap2 = new double*[3];

	for (int i = 0; i < 3; ++i)
	{
		arrInHeap1[i] = new double[3];
		arrInHeap2[i] = new double[3];
	}

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			arrInHeap1[i][j] = arr1[i][j];
			arrInHeap2[i][j] = arr2[i][j];
		}
	}

	Matrix matrix1(arrInHeap1, 3);
	Matrix matrix2(arrInHeap2, 3);

	Matrix sum = matrix1 + matrix2;

	ASSERT_EQ(3, sum.GetSize());

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			ASSERT_DOUBLE_EQ(sumArr[i][j], sum[i][j]);

	Matrix product1 = matrix1 * matrix2;

	ASSERT_EQ(3, sum.GetSize());

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			ASSERT_DOUBLE_EQ(productArr1[i][j], product1[i][j]);

	Matrix product2 = matrix2 * matrix1;

	ASSERT_EQ(3, sum.GetSize());

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			ASSERT_DOUBLE_EQ(productArr2[i][j], product2[i][j]);

	DeleteMatrixArr(arrInHeap1, 3);
	DeleteMatrixArr(arrInHeap2, 3);
}

TEST(MatrixTests, Test4)
{
	double arr[3][3] =
	{
		{ 1, 2, 3 },
		{ 2, 4, 6 },
		{ 7, 8, 9 }
	};

	double** arrInHeap = new double*[3];

	for (int i = 0; i < 3; ++i)
		arrInHeap[i] = new double[3];

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			arrInHeap[i][j] = arr[i][j];

	Matrix matrix1(arrInHeap, 3);

	Matrix matrix2 = 12 * matrix1;

	ASSERT_EQ(3, matrix2.GetSize());

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			ASSERT_DOUBLE_EQ(12 * arr[i][j], matrix2[i][j]);

	Matrix matrix3 = matrix1 * 14;

	ASSERT_EQ(3, matrix3.GetSize());

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			ASSERT_DOUBLE_EQ(14 * arr[i][j], matrix3[i][j]);

	DeleteMatrixArr(arrInHeap, 3);
}

TEST(MatrixTests, Test5)
{
	std::string matrixStr = "{{0, 0, 1}, {0, 0, 0.5}, {1, 1, 2.5}}";

	double arrForTest[3][3] =
	{
		{ 0, 0, 1 },
		{ 0, 0, 0.5 },
		{ 1, 1, 2.5 }
	};

	Matrix matrix(matrixStr, 3);

	ASSERT_EQ(3, matrix.GetSize());

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			ASSERT_DOUBLE_EQ(arrForTest[i][j], matrix[i][j]);
}