#include "stdafx.h"
#include "Universum.h"
#include "Sets.h"
#include "functions.h" 
int main()
{
	setlocale(LC_ALL, "Russian");
	srand(0);
	cout << "\n=====================================================\n Lab 1: Мультимножества, бинарный код Грея, универсум\n====================\n\n\n\n";
	int u_razr = -1; //разрядность универсума max = 6
	while ((u_razr < 0) | (u_razr > 6)) {
    cout << "Введите разрядность универсума(min = 0, max = 6): \n>";
	u_razr = getnum();
    }
	cout << "\n\n Универсум:\n";
	Universum u(u_razr);
	cout << "\n\n Множество А:\n";
	Sets A(&u); 
	cout << "\n\n Множество B:\n";
	Sets B(&u);

	bool stop_flag = 1;
	while (stop_flag != 0) {
		cout << "\n\n Выберете операцию:\n[0]  Выход из программы\n[1]  Объединение\n[2]  Пересечение\n[3]  Дополнение к А\n[4]  Дополнение к B\n[5]  Разность A и B\n[6]  Разность B и A\n[7]  Арифметическое сложение\n[8]  Арифметическая разность A - B\n";
		cout << "[9]  Арифметическая разность B - A\n[10] Арифметичское произведение\n[11] Арифметичское деление A/B\n[12] Арифметическое деление B/A\n[13] Возведение в степень A^n\n[14] Возведение в степень B^n\n[15] Симметрическая разность\n[16] Пересоздать универсум\n[17] Вывести множество A и B\n";
		cout << "\n>";
		int in;
		in = getnum();
		switch (in) {
		case 0: { stop_flag = 0; break; }
		case 1: {
			Sets uunion = A.Union(B);
			cout << "Объединение\n";
			uunion.PrintSet();
			break;
		}
		case 2: {
			Sets inter = A.Intersection(B);
			cout << "Пересечение\n";
			inter.PrintSet();
			break;
		}
		case 3: { 
			Sets AddA = A.Add(&u);
			cout << "Дополнение к А:\n";
			AddA.PrintSet();
			break; }
		case 4: {
			Sets AddB = B.Add(&u);
			cout << "Дополнение к B:\n";
			AddB.PrintSet();
			break;
		}
		case 5: {
			Sets SubAB = A.Sub(B, &u);
			cout << "Разность A и B:\n";
			SubAB.PrintSet();
			break;
		}
		case 6: {
			Sets SubBA = B.Sub(A, &u);
			cout << "Разность B и A:\n";
			SubBA.PrintSet();
			break;
		}
		case 7: {
			Sets sum = A + B;
			cout << "Арифметическое сложение A+B:\n";
			sum.PrintSet();
			break;
		}
		case 8: {
			Sets DiffAB = A - B;
			cout << "Арифметичсекая разность A - B:\n";
			DiffAB.PrintSet();
			break;
		}
		case 9: {
			Sets DiffBA = B - A;
			cout << "Арифметичсекая разность B - A:\n";
			DiffBA.PrintSet();
			break;
		}
		case 10: {
			Sets mult = A * B;
			cout << "Арифметическое произведение A * B:\n";
			mult.PrintSet();
			break;
		}
		case 11: {
			Sets DivAB = A / B;
			cout << "Арифметичское деление A/B:\n";
			DivAB.PrintSet();
			break;
		}
		case 12: {
			Sets DivBA = B / A;
			cout << "Арифметичское деление B/A:\n";
			DivBA.PrintSet();
			break;
		}
		case 13: {
			int n = -1;
			while (n < 0) { 
               cout << "\nВ какую степень возвести?\n>";
			   n = getnum();
			}
			Sets RankA = A ^ n;
			RankA.PrintSet();
			break;
		}
		case 14: {
			int n = -1;
			while (n < 0) {
				cout << "\nВ какую степень возвести?\n>";
				n = getnum();
			}
			Sets RankB = B ^ n;
			RankB.PrintSet();
			break;
		}
		case 15: {
			Sets t1 = A.Intersection(B);
			Sets t2 = A.Union(B);
			Sets Symmetrical = t2 - t1;
			cout << "Симметрическая разность:\n";
			Symmetrical.PrintSet();
			break;
		}
		case 16: {
			int u_razr = -1; //разрядность универсума max = 6
			while ((u_razr < 0) | (u_razr > 6)) {
				cout << "Введите разрядность универсума(min = 0, max = 6): \n>";
				u_razr = getnum();
			}
			cout << "\n\n Универсум:\n";
			Universum u_new(u_razr);
			u = u_new;
			cout << "\n\n Множество А:\n";
			Sets A_new(&u_new);
			cout << "\n\n Множество B:\n";
			Sets B_new(&u_new);

			A = A_new;
			B = B_new;
			break;
		}
		case 17:
		{
			cout << "Множество A:\n";
			A.PrintSet();
			cout << "Множество B:\n";
			B.PrintSet();
			break;
		}
		default: cout << "Неправильный ввод!\n";
		}
	}
	cout << "\n\n Спасибо за использование программы! Приходите ещё!";
	return 0;
}

