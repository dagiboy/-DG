#include "stdafx.h"

#include "CommonFunc.hpp"

using namespace std;

//������� ������������ ������ ��������� ����������� �� 0,1 �������
//������� ���������: positionList - ����� ������� �� ������� ����� 1; recursionLevel - ������� ��������; curentPerm - ������������ ������� ������� �� ���������� ������� ��������
//�����: ������������ ��������������� ����� ��������
//����� ���������� ���� �� �������� � �������� ���������� ��� ��������� ����������, �� ���� ������� ���� �� ������ �� ��������� ������ 
vector<int> GetPermRecursive(const vector<vector<int>>& positionList, size_t recursionLevel = 0, vector<int> curentPerm = {})
{
	//���� ������� �������� ����� �� ������� ������� �������, �� �� ����� ������ ��� ������������ � ���������� �������� ������������ ������������
	if (recursionLevel >= positionList.size())
		return curentPerm;

	//�� recursionLevel ���� �������� ��� ������ � ������� recursionLevel ���������� ��� ��������� �������� ������� ������ 1
	for (size_t i = 0; i < positionList[recursionLevel].size(); ++i)
	{
		//���� ������� � ����� ������� ��� �� ������������ �  ����� ������������ �� ������ ���� ����� � ���� ������������
		if (find(curentPerm.begin(), curentPerm.end(), positionList[recursionLevel][i]) == curentPerm.end())
		{
			// ������ ����� �������� � ���� ������������
			curentPerm.push_back(positionList[recursionLevel][i]);
			//� ���������� ������� ���� ������� ��� ���������� ������������
			vector<int> perm = GetPermRecursive(positionList, recursionLevel + 1, curentPerm);
				
			//���� ������������ ����������� �������, �� ���������� �� � ������� �� ��������
			//� ����� ���������� ��� ��������� ���������
			if (perm.size() == positionList.size())
				return perm;

			// ������ ����� �������� �� ������������
			curentPerm.pop_back();
		}
	}

	//���� ��� ���������, �������������� ����� ��������, ���������� ������ ������������
	return {};
}

// �� ���� ������� �������� �������, ��������� �� 0 � 1.
// ������� ���������� ������������, ������� ������� ������ ��� ����� ������� �������, ��� ������ ������������ ���� ������ ������� �� ����������.
vector<int> GetPossiblePerm(const Matrix& matr)
{
	//��� ������ ������� ������ ������ ������� �� ������� ����� �� ������� ��������( ����� ������� �� ������� ����� 1)
	vector<vector<int>> posList;

	//������ �������
	int matrixSize = matr.GetSize();

	//���� �� �������
	for (int i = 0; i < matrixSize; ++i)
	{
		//��� i ������ ������ �������� �� ������� ����� �������
		vector<int> vect;

		for (int j = 0; j < matrixSize; ++j)
		{
			//��������� , ��� matr[i][j] == 1, ���� ��� �� ��������� ������� �  ������ �������� ��� i ������
			if (abs(matr[i][j] - 1) < DBL_EPSILON)
				vect.push_back(j);
		}

		//� ����� �������� ��������� ������ �������� ��� i ������
		posList.push_back(vect);
	}

	//���� � ���������� ���� ������������
	return GetPermRecursive(posList);
}