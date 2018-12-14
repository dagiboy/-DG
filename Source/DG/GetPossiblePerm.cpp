#include "stdafx.h"

#include "CommonFunc.hpp"

using namespace std;

//Функция рекурсивного поиска возможной подстановки на 0,1 матрице
//Входные параметры: positionList - карта позицию на которых стоят 1; recursionLevel - уровень рекурсии; curentPerm - перестановка которую собрали на предыдущих уровнях рекурсии
//Выход: перестановка удовлетворяющая нашим условиям
//Будем рекурсивно идти по строчкам и выбирать поочередно все возможные комбинации, до того момента пока не дойдем до последней строки 
vector<int> GetPermRecursive(const vector<vector<int>>& positionList, size_t recursionLevel = 0, vector<int> curentPerm = {})
{
	//если уровень рекурсии вышел за пределы размера матрицы, то мы нашли нужную нам перестановку и возвращаем значение получившейся перестановки
	if (recursionLevel >= positionList.size())
		return curentPerm;

	//на recursionLevel шаге рекурсии для строки с номером recursionLevel перебираем все возможные элементы матрицы равные 1
	for (size_t i = 0; i < positionList[recursionLevel].size(); ++i)
	{
		//если элемент с таким номером еще не присутствует в  нашей перестановке то дбавим этот номер в нашу перестановку
		if (find(curentPerm.begin(), curentPerm.end(), positionList[recursionLevel][i]) == curentPerm.end())
		{
			// дбавим номер элемента в нашу перестановку
			curentPerm.push_back(positionList[recursionLevel][i]);
			//и рекурсивно вызовем нашу функцию для вычисления перестановки
			vector<int> perm = GetPermRecursive(positionList, recursionLevel + 1, curentPerm);
				
			//если перестановка вычислилась успешно, то возвращаем ее и выходим из рекурсии
			//а иначе продолжаем для следующих элементов
			if (perm.size() == positionList.size())
				return perm;

			// удалим номер элемента из перестановки
			curentPerm.pop_back();
		}
	}

	//если нет элементов, удовлетворющих нашим условиям, возвращаем пустую перестановку
	return {};
}

// На вход функция получает матрицу, состоящую из 0 и 1.
// Функция возвращает перестановку, матрица которой меньше или равна входной матрице, или пустую перестановку если такоая матрица не существует.
vector<int> GetPossiblePerm(const Matrix& matr)
{
	//Для каждой строчки найдем номера позиций на которых стоят не нулевые элементы( карта позицию на которых стоят 1)
	vector<vector<int>> posList;

	//размер матрицы
	int matrixSize = matr.GetSize();

	//идем по строкам
	for (int i = 0; i < matrixSize; ++i)
	{
		//для i строки вектор индексов на которых стоят единицы
		vector<int> vect;

		for (int j = 0; j < matrixSize; ++j)
		{
			//проверяем , что matr[i][j] == 1, если так до добовляем элемент в  вектор индексов для i строки
			if (abs(matr[i][j] - 1) < DBL_EPSILON)
				vect.push_back(j);
		}

		//в карту индексов добовляем вектор индексов для i строки
		posList.push_back(vect);
	}

	//ищем и возвращаем нашу перестановку
	return GetPermRecursive(posList);
}