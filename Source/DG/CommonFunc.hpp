#pragma once

#include "DGApi.hpp"
#include <list>
#include "Matrix.hpp"

// �� ���� ������� �������� �������, ��������� �� 0 � 1.
// ������� ���������� ������������, ������� ������� ������ ��� ����� ������� �������, ��� ������ ������������ ���� ������ ������� �� ����������.
DG_API std::vector<int> GetPossiblePerm(const Matrix& matr);

DG_API std::vector<std::pair<double, std::vector<int>>> GetPermDecomposition(const Matrix& matrix);

// ��������� �������, � ������� ������� ����� 0, ���� �������������� ��� ������� � ������� matr ������ b, 1 � ��������� ������.
DG_API Matrix GetBitMatrix(const Matrix& matr, double b);

DG_API Matrix GetPermMatrix(const std::vector<int>& perm);

// ��������� minmax �������.
DG_API double Minmax(const Matrix& matr);

DG_API std::vector<double> GetVectorProduct(std::vector<double> &vect, Matrix& lP, Matrix& rP);