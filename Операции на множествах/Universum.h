#pragma once
#include <iostream>
#include <vector>
using namespace std;
class Universum {
	int n; //�����������
	vector<int> uni; //������ �������������� ���������� ����
	vector<int> multi; //��������� ������� �������� � ����������
	int maxmulti = 5; //������������ ���������, ������� ��������� ���������
	friend class Sets;
public:
	Universum(int n);
	int QGray(int i);
	void PrintBits(int i);
	int get_n();
};