#pragma once
#include "Universum.h"
#include <set>
#include <map>
#include <vector>
#include <iterator>
using namespace std;
class Sets
{
	Universum* my_u; //указатель на универсум
	int size; //мощность кода Грея
	int set_power = -1; //количество элементов в множестве
	map<int, int> set;
public:
	Sets();
	Sets(Universum* u); //универсум
	void PrintSet();
	Sets Union(Sets& s2); //операция объединение
	Sets Intersection(Sets& s2); //операция пересечение
	Sets Add(Universum* u); //операция дополнение
	Sets Sub(Sets& s2, Universum* u); //операция разность
	Sets operator+(Sets& s2); //арифметическое сложение
	Sets operator-(Sets& s2); //арифметическая разность
	Sets operator*(Sets& s2); //арифметическое произведение
	Sets operator/(Sets& s2); //арифметическое деление
	Sets operator^(int n); //возведение в степень
};
