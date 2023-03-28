#pragma once
#include "Universum.h"
#include <set>
#include <map>
#include <vector>
#include <iterator>
using namespace std;
class Sets
{
	Universum* my_u; //��������� �� ���������
	int size; //�������� ���� ����
	int set_power = -1; //���������� ��������� � ���������
	map<int, int> set;
public:
	Sets();
	Sets(Universum* u); //���������
	void PrintSet();
	Sets Union(Sets& s2); //�������� �����������
	Sets Intersection(Sets& s2); //�������� �����������
	Sets Add(Universum* u); //�������� ����������
	Sets Sub(Sets& s2, Universum* u); //�������� ��������
	Sets operator+(Sets& s2); //�������������� ��������
	Sets operator-(Sets& s2); //�������������� ��������
	Sets operator*(Sets& s2); //�������������� ������������
	Sets operator/(Sets& s2); //�������������� �������
	Sets operator^(int n); //���������� � �������
};
