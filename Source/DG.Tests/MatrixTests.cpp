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

TEST(MatrixTests, Test6)
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

	ASSERT_ANY_THROW(Matrix matrix(arrInHeap, 0));

	ASSERT_ANY_THROW(Matrix matrix(nullptr, 1));
}

TEST(MatrixTests, Test7)
{
	std::string matrixStr = "{{0, 0, 1}, {0, 0, 0.5}, {1, 1, 2.5}}";

	ASSERT_ANY_THROW(Matrix matrix(matrixStr, 0));

	ASSERT_ANY_THROW(Matrix matrix("", 1));

	ASSERT_ANY_THROW(Matrix matrix("{}", 1));
}

TEST(MatrixTests, Test8)
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

TEST(MatrixTests, Test9)
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

	double** sourceMatrixArr = new double*[3];
	double** destMatrixArr = new double*[3];

	for (int i = 0; i < 3; ++i)
	{
		sourceMatrixArr[i] = new double[3];
		destMatrixArr[i] = new double[3];
	}

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			sourceMatrixArr[i][j] = arr1[i][j];
			destMatrixArr[i][j] = arr2[i][j];
		}
	}

	Matrix sourceMatrix(sourceMatrixArr, 3);
	Matrix destMatrix(destMatrixArr, 3);

	destMatrix = sourceMatrix;

	for (int i = 0; i < 3; ++i)
	{ 
		for (int j = 0; j < 3; ++j)
		{
			ASSERT_DOUBLE_EQ(destMatrix[i][j], sourceMatrix[i][j]);
		}
	}
}

TEST(MatrixTests, Test10)
{
	double arr[3][3] =
	{
		{ 1, 2, 3 },
		{ 2, 4, 6 },
		{ 7, 8, 9 }
	};

	double** sourceMatrixArr = new double*[3];

	for (int i = 0; i < 3; ++i)
	{
		sourceMatrixArr[i] = new double[3];
	}

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			sourceMatrixArr[i][j] = arr[i][j];
		}
	}

	Matrix sourceMatrix(sourceMatrixArr, 3);

	ASSERT_ANY_THROW(sourceMatrix[-1]);
}

TEST(MatrixTests, Test11)
{
	double arr1[3][3] =
	{
		{ 1, 2, 3 },
		{ 2, 4, 6 },
		{ 7, 8, 9 }
	};

	double** arr1MatrixArr = new double*[3];

	for (int i = 0; i < 3; ++i)
	{
		arr1MatrixArr[i] = new double[3];
	}

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			arr1MatrixArr[i][j] = arr1[i][j];
		}
	}

	double arr2[2][2] =
	{
		{ 1, 2 },
		{ 2, 4 }
	};

	double** arr2MatrixArr = new double*[2];

	for (int i = 0; i < 2; ++i)
	{
		arr2MatrixArr[i] = new double[2];
	}

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			arr2MatrixArr[i][j] = arr2[i][j];
		}
	}

	Matrix arr1Matrix(arr1MatrixArr, 3);
	Matrix arr2Matrix(arr2MatrixArr, 2);

	ASSERT_ANY_THROW(arr1Matrix + arr2Matrix);
}

TEST(MatrixTests, Test12)
{
	double arr1[3][3] =
	{
		{ 1, 2, 3 },
		{ 2, 4, 6 },
		{ 7, 8, 9 }
	};

	double** arr1MatrixArr = new double*[3];

	for (int i = 0; i < 3; ++i)
	{
		arr1MatrixArr[i] = new double[3];
	}

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			arr1MatrixArr[i][j] = arr1[i][j];
		}
	}

	double arr2[2][2] =
	{
		{ 1, 2 },
		{ 2, 4 }
	};

	double** arr2MatrixArr = new double*[2];

	for (int i = 0; i < 2; ++i)
	{
		arr2MatrixArr[i] = new double[2];
	}

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			arr2MatrixArr[i][j] = arr2[i][j];
		}
	}

	Matrix arr1Matrix(arr1MatrixArr, 3);
	Matrix arr2Matrix(arr2MatrixArr, 2);

	ASSERT_ANY_THROW(arr1Matrix * arr2Matrix);
}

TEST(MatrixTests, Test13)
{
	int counter = 0;

	double** arr1MatrixArr = new double*[7];
	double** arr2MatrixArr = new double*[7];

	for (int i = 0; i < 7; ++i)
	{
		arr1MatrixArr[i] = new double[7];
		arr2MatrixArr[i] = new double[7];
	}

	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 7; ++j)
		{
			++counter;
			arr1MatrixArr[i][j] = counter;
			arr2MatrixArr[6 - i][6 - j] = counter;
		}
	}

	Matrix arr1Matrix(arr1MatrixArr, 7);
	Matrix arr2Matrix(arr2MatrixArr, 7);

	arr1Matrix = arr1Matrix * arr2Matrix;

	double result[7][7] = 
	{
		{ 588, 560, 532, 504, 476, 448, 420 },
		{ 1960, 1883, 1806, 1729, 1652, 1575, 1498 },
		{ 3332, 3206, 3080, 2954, 2828, 2702, 2576 },
		{ 4704, 4529, 4354, 4179, 4004, 3829, 3654 },
		{ 6076, 5852, 5628, 5404, 5180, 4956, 4732 },
		{ 7448, 7175, 6902, 6629, 6356, 6083, 5810 },
		{ 8820, 8498, 8176, 7854, 7532, 7210, 6888 },		
	};

	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 7; ++j)
		{
			ASSERT_DOUBLE_EQ(arr1Matrix[i][j], result[i][j]);
		}
	}
}

TEST(MatrixTests, Test14)
{
	std::string matrixStr = "{{}, {}, {}}";

	ASSERT_ANY_THROW(Matrix matrix(matrixStr, 0));

	ASSERT_ANY_THROW(Matrix matrix("", 1));
}