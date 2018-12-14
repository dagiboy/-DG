#pragma once

#include "DGApi.hpp"
#include <list>
#include "Matrix.hpp"

// На вход функция получает матрицу, состоящую из 0 и 1.
// Функция возвращает перестановку, матрица которой меньше или равна входной матрице, или пустую перестановку если такоая матрица не существует.
DG_API std::vector<int> GetPossiblePerm(const Matrix& matr);

DG_API std::vector<std::pair<double, std::vector<int>>> GetPermDecomposition(const Matrix& matrix);

// Возращает матрицу, в которой элемент равен 0, если соответсвующий ему элемент в матрице matr меньше b, 1 в противном случае.
DG_API Matrix GetBitMatrix(const Matrix& matr, double b);

DG_API Matrix GetPermMatrix(const std::vector<int>& perm);

// Возращает minmax матрицы.
DG_API double Minmax(const Matrix& matr);

DG_API std::vector<double> GetVectorProduct(std::vector<double> &vect, Matrix& lP, Matrix& rP);