#pragma once
#include <iostream>
#include <vector>
using namespace std;
class Universum {
	int n; //Разрядность
	vector<int> uni; //Массив сформированный алгоритмом Грея
	vector<int> multi; //кратность каждого элемента в универсуме
	int maxmulti = 5; //максимальная кратность, которую позволяет программа
	friend class Sets;
public:
	Universum(int n);
	int QGray(int i);
	void PrintBits(int i);
	int get_n();
};