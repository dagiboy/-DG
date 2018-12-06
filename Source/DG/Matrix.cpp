#include "stdafx.h"

#include "Matrix.hpp"

// Создает нулевую матрицу размера size x size
Matrix::Matrix(int size)
{
	if (size < 1)
		throw std::runtime_error("Invalid size!");
	
	_size = size;

	AllocateMatrix();

	for (int i = 0; i < _size; ++i)
		for (int j = 0; j < _size; ++j)
			_matrix[i][j] = 0;
}

Matrix::Matrix(double** matrix, int size)
{
	if (size < 1)
		throw std::runtime_error("Invalid size!");

	if (matrix == nullptr)
		throw std::runtime_error("Invalid matrix!");

	InitializeFrom(matrix, size);
}

bool Functor(char ch) 
{	
	std::string separators = "{},()_\t\n\r";

	return std::find(separators.begin(), separators.end(), ch) != separators.end();
}

// matrix - строка, представляющая матрицу, элементы которой стоят через любой пробельный символ.
// Числа типа double в строке должны записываться через точку, т.е 6.666, а не 6,666
Matrix::Matrix(std::string matrix, int size)
{
	if (size < 1)
		throw std::runtime_error("Invalid size!");

	if (matrix.empty())
		throw std::runtime_error("Invalid matrix!");

	_size = size;

	// Заменяем все ненужные символы на пробелы
	std::replace_if(matrix.begin(), matrix.end(), Functor, ' ');

	// Меняем '.' в записи чисел на ','
	std::replace(matrix.begin(), matrix.end(), '.', ',');

	std::stringstream ss(matrix);
	std::string item;

	AllocateMatrix();

	for (int i = 0; i < _size; ++i)
	{
		for (int j = 0; j < _size; ++j)
		{
			ss >> item;
			if (item.length() == 0)
				throw std::runtime_error("Invalid string!");

			_matrix[i][j] = stod(item);
		}
	}
}

Matrix::Matrix(const Matrix& other)
{
	InitializeFrom(other._matrix, other._size);
}

Matrix::~Matrix()
{
	ClearMatrix();
}

int Matrix::GetSize() const
{
	return _size;
}

Matrix Matrix::operator=(const Matrix& other)
{
	if (this == &other)
		return *this;

	ClearMatrix();

	InitializeFrom(other._matrix, other._size);

	return *this;
}

double* Matrix::operator[](int index) const
{
	if (index < 0 || index >= _size)
		throw std::runtime_error("Invalid index!");

	return _matrix[index];
}

Matrix Matrix::operator+(const Matrix& right) const
{
	// Генерация исключения при несоответствии размеров матриц
	if (_size != right._size)
		throw std::runtime_error("Invalid size");

	Matrix sum(_size);

	for (int i = 0; i < _size; ++i)
		for (int j = 0; j < _size; ++j)
			sum._matrix[i][j] = _matrix[i][j] + right._matrix[i][j];

	return sum;
}

Matrix Matrix::operator*(const Matrix& right) const
{
	// Генерация исключения при несоответствии размеров матриц
	if (_size != right._size)
		throw std::runtime_error("Invalid size");

	Matrix product(_size);

	for (int i = 0; i < _size; ++i)
		for (int j = 0; j < _size; ++j)
			for (int k = 0; k < _size; ++k)
				product._matrix[i][j] += _matrix[i][k] * right._matrix[k][j];

	return product;
}

Matrix Matrix::operator*(double number) const
{
	Matrix product(_size);

	for (int i = 0; i < _size; ++i)
	for (int j = 0; j < _size; ++j)
		product._matrix[i][j] = _matrix[i][j] * number;

	return product;
}

Matrix operator*(double number, Matrix rightMatrix)
{
	Matrix product(rightMatrix._size);

	for (int i = 0; i < rightMatrix._size; ++i)
	for (int j = 0; j < rightMatrix._size; ++j)
		product._matrix[i][j] = number * rightMatrix._matrix[i][j];

	return product;
}

void Matrix::AllocateMatrix()
{
	_matrix = new double*[_size];

	for (int i = 0; i < _size; ++i)
		_matrix[i] = new double[_size];
}

void Matrix::InitializeFrom(double** matrix, int size)
{
	_size = size;

	AllocateMatrix();

	for (int i = 0; i < _size; ++i)
		for (int j = 0; j < _size; ++j)
			_matrix[i][j] = matrix[i][j];
}

void Matrix::ClearMatrix() const
{
	for (int i = 0; i < _size; ++i)
		delete[] _matrix[i];

	delete[] _matrix;
}