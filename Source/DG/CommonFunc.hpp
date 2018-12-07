#pragma once

#include "DGApi.hpp"
#include <list>
#include "Matrix.hpp"

// �� ���� ������� �������� �������, ��������� �� 0 � 1.
// ������� ������ ������� ������ ������������, ������� ������� ������ ��� ����� ������� �������.
DG_API std::list<std::vector<int>> GetPossiblePerm(const Matrix& matr);

// ��������� �������, � ������� ������� ����� 0, ���� �������������� ��� ������� � ������� matr ������ b, 1 � ��������� ������.
DG_API Matrix GetBitMatrix(const Matrix& matr, double b);

// ��������� minmax �������.
DG_API double Minmax(const Matrix& matr);