#pragma once

#include "DGApi.hpp"
#include <list>
#include "Matrix.hpp"

// На вход функция получает матрицу, состоящую из 0 и 1.
// Функция должна вернуть список перестановок, матрицы которых меньше или равна входной матрице.
DG_API std::list<std::vector<int>> GetPossiblePerm(const Matrix& matr);

// Возращает матрицу, в которой элемент равен 0, если соответсвующий ему элемент в матрице matr меньше b, 1 в противном случае.
DG_API Matrix GetBitMatrix(const Matrix& matr, double b);

// Возращает minmax матрицы.
DG_API double Minmax(const Matrix& matr);