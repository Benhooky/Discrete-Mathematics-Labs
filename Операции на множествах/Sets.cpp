#include "Sets.h"
#include "functions.h"
#include <algorithm>
#include <iterator>
Sets::Sets()
{
	size = 0;
	set_power = 0;
}

Sets::Sets(Universum* u)
{
	int user_kr;
	size = u->get_n();
	this->my_u = u;

	if (size > 0) {
		cout << "������� ���������� ��������� ���������" << "(�� ����� ��������� " << (1 << size) << "): ";
		while ((set_power < 0) | (set_power > (1 << size))) {
			set_power = getnum();
			if ((set_power >= 0) & (set_power <= (1 << size)))
				break;
			else
				cout << "���������� ��������� ��������� �� ������ ���� ������ 0 ��� ��������� " << (1 << size) << ". ���������� ��� ���..\n>";
		}
		if (set_power > 0) {
			cout << "\n��� ������ ��������� ? \n0.������� 1.�������������\n> ";
			int user_answer = -1;
			while ((user_answer != 0) | (user_answer != 1)) {
				user_answer = getnum();
				if ((user_answer == 0) | (user_answer == 1))
					break;
				else
					cout << "��� ������ �������� ������. ���������� ��� ���..\n>";
			}


			if (user_answer == 1) {
				while (set.size() != set_power) {
					int randchislo = (rand() % (1 << size));
					set[u->uni[randchislo]] = (1 + rand() % (u->multi[randchislo]));
				}
			}
			else if (user_answer == 0) {
				int user_chislo = -1;
				while (set.size() != set_power) {
					{
						user_chislo = -1;
						while ((user_chislo < 1) | (user_chislo > (1 << size))) {
							cout << "\n������� ���������� ����� ��������: ";
							user_chislo = getnum();
							if ((user_chislo < 1) | (user_chislo > (1 << size))) {
								cout << "������ �������� �� ����������. ���������� ��� ���..\n>";
							}
						}
					}
					bool my_flag = false;
					while (my_flag != true) { //���� �� ������� ������ �������
						map<int, int>::iterator check_repeat;
						int test_user_chislo = user_chislo - 1; //������ ��� ��������� � ������� ���������� � 0
						check_repeat = set.find(u->uni[test_user_chislo]);
						if (check_repeat != set.end()) {
							user_chislo = -1;
							cout << "����� ������� ��� ��� ����� �����. ���������� ��� ���..\n>";
						}
						else { my_flag = true; };
					}
					user_chislo--;
					cout << "������� ��������� ��������(max = " << u->multi[user_chislo] << "): ";
					user_kr = -1;
					while ((user_kr < 1) | (user_kr > u->multi[user_chislo])) {
						user_kr = getnum();
						if ((user_kr < 1) | (user_kr > u->multi[user_chislo]))
							cout << "��������� �������� �� ����� ���� ������ 1 ��� ��������� " << u->multi[user_chislo] << ". ���������� ��� ���..\n>";
					}
					set[u->uni[user_chislo]] = user_kr;
				}
			}
		}
		cout << "\n������������ ���������:\n";
		PrintSet();
	}
	else if (size == 0) {
		cout << "������ ���������!";
	}
}

void Sets::PrintSet()
{
	if (set_power > 0) {
		for (auto set_it = set.begin(); set_it != set.end(); set_it++) {
			int element = (*set_it).first;
			cout << "  (";
			for (int temp = 1 << size - 1; temp > 0; temp = temp / 2)
			{
				if (temp & element)
				{
					cout << "1";
				}
				else
				{
					cout << "0";
				}
			}
			cout << ")  : " << set_it->second << "\n";
		}
	}
	else
		cout << "������ ���������! \n";
}

Sets Sets::Union(Sets& s2)
{
	Sets tmp;
	tmp.size = this->size;
	map<int, int>::iterator map1_it = this->set.begin();
	map<int, int>::iterator map2_it = s2.set.begin();
	vector<int>::iterator find_it;
	for (; map1_it != this->set.end(); map1_it++) {
		map2_it = s2.set.find((*map1_it).first);
		if (map2_it != s2.set.end()) { //���� ������� ���� � ���� ����������
			tmp.set[(*map2_it).first] = std::max((*map2_it).second, (*map1_it).second); //������������ ��������� �� ����
		}
		else if (map2_it == s2.set.end()) {//���� ������� �� ������� ��������� �� ��� ������ �� ������
			tmp.set[(*map1_it).first] = (*map1_it).second;
		}
	}
	for (map2_it = s2.set.begin(); map2_it != s2.set.end(); map2_it++) {
		map1_it = this->set.find((*map2_it).first);
		if (map1_it == this->set.end()) { //���� ������� ���� �� ������ �������� �� ��� � ������
			tmp.set[(*map2_it).first] = (*map2_it).second;
		}
	}
	tmp.set_power = tmp.set.size();
	return tmp;
}

Sets Sets::Intersection(Sets& s2)
{
map<int, int>::iterator map_it; //�������� �� ������ ���������
map<int, int>::iterator map_true_find; //�������� �� ������ ���������
	Sets tmp;
	tmp.size = this->size;
	if (this->set.size() >= s2.set.size()) {
		for (map_it = this->set.begin(); map_it != this->set.end(); map_it++) {
			map_true_find = s2.set.find((*map_it).first);
			if (map_true_find != s2.set.end()) {
				tmp.set[(*map_it).first] = std::min((*map_it).second, (*map_true_find).second);
				tmp.set_power++;
			}
		}
	}
	else if (this->set.size() < s2.set.size()) {
		for (map_it = s2.set.begin(); map_it != s2.set.end(); map_it++) {
			map_true_find = this->set.find((*map_it).first);
			if (map_true_find != this->set.end()) {
				tmp.set[(*map_it).first] = std::min((*map_it).second, (*map_true_find).second);
				tmp.set_power++;
			}
		} 
	}
	return tmp;
}

Sets Sets::Add(Universum* u)
{
	Sets tmp;
	if (u->n > 0) {
	tmp.size = u->n;
	map<int, int>::iterator map_it;
	for (int i = 0; i < 1 << u->n; i++) {
		map_it = this->set.find(u->uni[i]);
		if (map_it == this->set.end()) { //���� � ��������� ��� ��������
			tmp.set[u->uni[i]] = u->multi[i];
		}
		else {
			if ((*map_it).second != u->multi[i]) {
				tmp.set[u->uni[i]] = u->multi[i] - (*map_it).second;
			}
		}
	}
	tmp.set_power = tmp.set.size();
   }
	return tmp;
}

Sets Sets::Sub(Sets& s2, Universum* u)
{
	Sets tmp;
	tmp = s2.Add(u);
	Sets tmp2;
	tmp2 = this->Intersection(tmp);
	return tmp2;
}

Sets Sets::operator+(Sets& s2)
{
	Sets tmp;
	int common_krat = 0;
	tmp.size = this->size;
	map<int, int>::iterator map1_it = this->set.begin();
	map<int, int>::iterator map2_it = s2.set.begin();
	vector<int>::iterator find_it;
	for (; map1_it!=this->set.end(); map1_it++) {
		map2_it = s2.set.find((*map1_it).first);
		if (map2_it != s2.set.end()) { //���� ������� ���� � ���� ����������
			common_krat = (*map2_it).second + (*map1_it).second;
			find_it = find(s2.my_u->uni.begin(), s2.my_u->uni.end(), (*map2_it).first);
			if (common_krat > s2.my_u->multi[find_it - s2.my_u->uni.begin()]) { //���� ������������ ��������� ������ ��� ��������� � ����������
				tmp.set[(*map2_it).first] = s2.my_u->multi[find_it - s2.my_u->uni.begin()]; //����� ��������� � ����������
			}
			else
				tmp.set[(*map2_it).first] = common_krat;
		}
		else if (map2_it == s2.set.end()) {//���� ������� �� ������� ��������� �� ��� ������ �� ������
			tmp.set[(*map1_it).first] = (*map1_it).second;
		}
	}
	for (map2_it = s2.set.begin(); map2_it != s2.set.end(); map2_it++) {
		map1_it = this->set.find((*map2_it).first);
		if (map1_it == this->set.end()) { //���� ������� ���� �� ������ �������� �� ��� � ������
			tmp.set[(*map2_it).first] = (*map2_it).second;
		}
	}
	tmp.set_power = tmp.set.size();
	return tmp;
}

Sets Sets::operator-(Sets& s2)
{
	Sets tmp;
	int common_krat = 0;
	tmp.size = s2.size;
	if (this->set_power != 0) { //���� ��������� �� ������ 
		tmp.set = this->set; 
		map<int, int>::iterator map1_it = tmp.set.begin();
		map<int, int>::iterator map2_it;
		for (; map1_it != tmp.set.end(); map1_it++) {
			map2_it = s2.set.find((*map1_it).first);
			if (map2_it != s2.set.end()) { //���� ������� ���� � ���� ����������
				common_krat = (*map1_it).second - (*map2_it).second;
				if (common_krat <= 0) {
					common_krat = 0;
				}
				tmp.set[(*map1_it).first] = common_krat;
			}
			
		}
	map<int, int>::iterator it = tmp.set.begin(); 
	//������� �� ��������� �������� � ���������� 0
	while (it != tmp.set.end()) {
		if ((*it).second == 0) {
			tmp.set.erase(it++);
		}
		else
			++it;
	}
    }
    tmp.set_power = tmp.set.size();
	return tmp;
}

Sets Sets::operator*(Sets& s2)
{
	map<int, int>::iterator map_it; //�������� �� ������ ���������
	map<int, int>::iterator map_true_find; //�������� �� ������ ���������
	vector<int>::iterator find_it; 
	Sets tmp;
    int common_krat = 1;
	tmp.size = this->size;
	if (this->set.size() >= s2.set.size()) {
		for (map_it = this->set.begin(); map_it != this->set.end(); map_it++) {
			map_true_find = s2.set.find((*map_it).first);
			if (map_true_find != s2.set.end()) { //���� ������� ���� � ���� ����������
				common_krat = (*map_it).second * (*map_true_find).second;
				find_it = find(s2.my_u->uni.begin(), s2.my_u->uni.end(), (*map_true_find).first);
				if (common_krat > s2.my_u->multi[find_it - s2.my_u->uni.begin()]) {
					tmp.set[(*map_true_find).first] = s2.my_u->multi[find_it - s2.my_u->uni.begin()]; //����� ��������� � ����������
				}
				else
					tmp.set[(*map_true_find).first] = common_krat;
			}
		}
	}
	else if (this->set.size() < s2.set.size()) {
		for (map_it = s2.set.begin(); map_it != s2.set.end(); map_it++) {
			map_true_find = this->set.find((*map_it).first);
			if (map_true_find != this->set.end()) {
				common_krat = (*map_it).second * (*map_true_find).second;
				find_it = find(this->my_u->uni.begin(), this->my_u->uni.end(), (*map_true_find).first);
				if (common_krat > this->my_u->multi[find_it - this->my_u->uni.begin()]) {
					tmp.set[(*map_true_find).first] = this->my_u->multi[find_it - this->my_u->uni.begin()]; //����� ��������� � ����������
				}
				else
					tmp.set[(*map_true_find).first] = common_krat;
			}
		}
	}
	tmp.set_power = tmp.set.size();
	return tmp;
}

Sets Sets::operator/(Sets& s2)
{
	Sets tmp;
	tmp.size = s2.size;
	int common_krat;
	if (this->set_power != 0) {
		map<int, int>::iterator map1_it = this->set.begin();
		map<int, int>::iterator map2_it;
		for (; map1_it != this->set.end(); map1_it++) {
			map2_it = s2.set.find((*map1_it).first);
			if (map2_it != s2.set.end()) { //���� ������� ���� � ���� ����������
				common_krat = (*map1_it).second / (*map2_it).second;
				if (common_krat <= 0) {
					common_krat = 0;
				}
				tmp.set[(*map1_it).first] = common_krat;
			}
		}
	}
	tmp.set_power = tmp.set.size();
	return tmp;
}

Sets Sets::operator^(int n)
{
	Sets tmp;
	tmp.size = this->size;
	tmp.set = this->set;
	if (n == 0) {
		tmp = (*this) / (*this);
	}
	else {
        for (int i = 0; i < n - 1; i++) {
	    	tmp = tmp * (*this);
	    }
	}
	tmp.set_power = tmp.set.size();
	return tmp;
}

