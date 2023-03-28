#include "Universum.h"
Universum::Universum(int n)
{
	this->n = n;

	if (n == 0) {
		cout << "Пустой универсум!";
	}
	else {
		int power = 1 << n; //2^n
		uni.reserve(power);
		for (int i = 0; i < power; i++) {
			if (i == 0) 
				uni.push_back(0);
			else {
				int q = QGray(i); //узнаём какой бит надо инвертировать
				uni.push_back(uni[i - 1] ^ (1 << q)); //получаем десятичное значение элемента кода Грея
			}
			cout << "\t" << i + 1 << ".\t" ;
			PrintBits(i);
			multi.reserve(power);
			multi.push_back(1 + rand()%maxmulti); //заполняем массив кратности элементов в диапазоне [1..maxmulti(5)]
			cout << "  Кратность: " << multi[i] << endl;
		}
	}
}

int Universum::QGray(int i)
{
	int q = 0;
	while ((i & 1) == 0)
	{
		i >>= 1;
		q++;
	}
	return q;
}

void Universum::PrintBits(int i)
{
	cout << "(";
	for (int temp = 1<<n-1; temp > 0; temp = temp / 2)
	{
		if (temp & uni[i])
		{
			cout << "1";
		}
		else
		{
			cout << "0";
		}
	}
	cout << ")";

}

int Universum::get_n()
{
	return this->n;
}
