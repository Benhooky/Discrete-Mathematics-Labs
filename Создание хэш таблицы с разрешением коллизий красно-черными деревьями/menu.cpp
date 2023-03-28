#include "menu.h"

bool IsContinue(bool overrideFlag) {
	if (overrideFlag) {
		return false;
	}

	boost::basic_regex<char, boost::cpp_regex_traits<char>> expr;
	expr.imbue(std::locale{ "russian" });
	expr = "^[YNyn]$";

	string inp;
	char decision;

	do {
		cout << "Продолжить? (Y/N): ";
		getline(cin, inp);
		if (boost::regex_match(inp, expr)) {
			decision = inp[0];

			switch (decision) {
			case 'Y':
			case 'y':
				return true;
			case 'N':
			case 'n':
				return false;
			}
		}
		else {
			cout << "Некорректный ввод!\n\n";
		}
	} while (true);
}

bool GetInt(int& inp, int min, int max, int* forbidden) {
	string str;
	bool res;

	boost::basic_regex<char, boost::cpp_regex_traits<char>> expr;
	expr.imbue(std::locale{"russian"});
	expr = "^(([1-9])([0-9])*)|(0)$";

	getline(cin, str);
	if (boost::regex_match(str, expr)) {
		inp = stoi(str);

		if ((forbidden != nullptr) && ((*forbidden) == inp)) {
			res = false;
		}
		else if (IS_IN_RANGE_CLOSED(inp, min, max)) {
			res = true;
		}
		else {
			res = false;
		}
	}
	else {
		res = false;
	}

	if (res) {
		return true;
	}
	else {
		cout << "Некорректный ввод!\n\n";
		return false;
	}
}

bool GetStr(string& inp, string rx) {
	boost::basic_regex<char, boost::cpp_regex_traits<char>> expr;
	expr.imbue(std::locale{"russian"});
	expr = rx;

	getline(cin, inp);
	if (boost::regex_match(inp, expr)) {
		return true;
	}
	else {
		cout << "Некорректный ввод!\n\n";
		return false;
	}
}

void PrintMenu() {
	cout << "Словарь на основе красно-черного дерва:\n";
	for (int i = 0; i < MENU_RBT_ITEMS_CNT; i++) {
		cout << std::setw(3) <<"("<< i << ")" << kMenuStrings[i] << '\n';
	}
	cout << "Словарь на основе хэш-таблицы:\n";
	for (int i = 0; i < MENU_RBT_ITEMS_CNT; i++) {
		cout << std::setw(3) <<"(" << i + MENU_RBT_ITEMS_CNT << ")"<< kMenuStrings[i] << '\n';
	}

	cout << '\n' << std::setw(3) << MENU_RBT_ITEMS_CNT + MENU_HASH_ITEMS_CNT + MENU_ADDITIONAL_ITEMS_CNT - 1 \
		 << kMenuStrings[MENU_HASH_ITEMS_CNT] << '\n';
	cout << '\n';
}

void ExecRbtPrint(Tree& map) {
	if (!map.GetSize()) {
		cout << "Словарь пуст!\n";
		return;
	}

	cout << "Содержимое словаря:\n";
	map.Print(cout);
}

void ExecRbtFind(Tree& map) {
	if (!map.GetSize()) {
		cout << "Словарь пуст!\n";
		return;
	}

	string inp;
	Node *found = nullptr, *parent = nullptr;

	do {
		cout << "Введите слово:\n";
	} while (!GetStr(inp, "(\\b[а-яА-ЯёЁ]*\\b)"));
	cout << '\n';

	found = map.Find(inp, parent);

	if (found) {
		cout << setw(15) << *(found->key) << setw(3) << found->val << " -- ";

		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		if (found->Amnt == 1) {
			SetConsoleTextAttribute(console, FOREGROUND_RED);
		}
		else {
			SetConsoleTextAttribute(console, FOREGROUND_GREEN);
		}
		cout << setw(7) << kColors[found->Amnt];
		SetConsoleTextAttribute(console, TEXT_COLOR_DEFAULT);

		if (parent) {
			cout << " " << setw(6) << kDirections[(parent->ptrs[1] == found)] << " потомок " << *(parent->key);
		}
		else {
			cout << " корень дерева";
		}
		cout << '\n';
	}
	else {
		cout << "Запись не найдена!\n";
	}
}

void ExecRbtInsert(Tree& map) {
	string inp;

	do {
		cout << "Введите слово:\n";
	} while (!GetStr(inp, "(\\b[а-яА-ЯёЁ]*\\b)"));
	cout << '\n';

	if (map.Insert(inp)) {
		cout << "Запись добавлена в словарь!\n";
	}
	else {
		cout << "Запись уже есть в словаре, счётчик повторов записи увеличен!\n";
	}
}

void ExecRbtDelete(Tree& map) {
	if (!map.GetSize()) {
		cout << "Словарь пуст!\n";
		return;
	}

	string inp;

	do {
		cout << "Введите слово:\n";
	} while (!GetStr(inp, "(\\b[а-яА-ЯёЁ]*\\b)"));
	cout << '\n';

	if (map.Delete(inp)) {
		cout << "Запись удалена!\n";
	}
	else {
		cout << "Запись не найдена!\n";
	}
}

void ExecRbtClear(Tree& map) {
	if (!map.GetSize()) {
		cout << "Словарь пуст!\n";
		return;
	}

	map.Clear();
	cout << "Словарь очищен!\n";
}

void ExecRbtLoad(Tree& map) {
	map.Load("tree_input.txt");
	cout << "Записи загружены!\n";
}

void ExecRbtSave(Tree& map) {
	if (!map.GetSize()) {
		cout << "Словарь пуст!\n";
		return;
	}

	map.Save("tree_output.txt");
	cout << "Записи сохранены!\n";
}

void ExecHashPrint(HashMap& map) {
	if (!map.GetSize()) {
		cout << "Словарь пуст!\n";
		return;
	}

	cout << "Содержимое словаря:\n";
	map.Print(cout);
}

void ExecHashFind(HashMap& map) {
	if (!map.GetSize()) {
		cout << "Словарь пуст!\n";
		return;
	}

	string inp;
	Node* found = nullptr, * parent = nullptr;

	do {
		cout << "Введите слово:\n";
	} while (!GetStr(inp, "(\\b[а-яА-ЯёЁ]*\\b)"));
	cout << '\n';

	found = map.Find(inp, parent);

	if (found) {
		cout << setw(15) << *(found->key) << setw(3) << found->val << " -- ";

		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		if (found->Amnt == 1) {
			SetConsoleTextAttribute(console, FOREGROUND_RED);
		}
		else {
			SetConsoleTextAttribute(console, FOREGROUND_GREEN);
		}
		cout << setw(7) << kColors[found->Amnt];
		SetConsoleTextAttribute(console, TEXT_COLOR_DEFAULT);

		if (parent) {
			cout << " " << setw(6) << kDirections[(parent->ptrs[1] == found)] << " потомок " << *(parent->key);
		}
		else {
			cout << " корень дерева";
		}
		cout << '\n';
	}
	else {
		cout << "Запись не найдена!\n";
	}
}

void ExecHashInsert(HashMap& map) {
	string inp;

	do {
		cout << "Введите слово:\n";
	} while (!GetStr(inp, "(\\b[а-яА-ЯёЁ]*\\b)"));
	cout << '\n';

	if (map.Insert(inp)) {
		cout << "Запись добавлена в словарь!\n";
	}
	else {
		cout << "Запись уже есть в словаре, счётчик повторов записи увеличен!\n";
	}
}

void ExecHashDelete(HashMap& map) {
	if (!map.GetSize()) {
		cout << "Словарь пуст!\n";
		return;
	}

	string inp;

	do {
		cout << "Введите слово:\n";
	} while (!GetStr(inp, "(\\b[а-яА-ЯёЁ]*\\b)"));
	cout << '\n';

	if (map.Delete(inp)) {
		cout << "Запись удалена!\n";
	}
	else {
		cout << "Запись не найдена!\n";
	}
}

void ExecHashClear(HashMap& map) {
	if (!map.GetSize()) {
		cout << "Словарь пуст!\n";
		return;
	}

	map.Clear();
	cout << "Словарь очищен!\n";
}

void ExecHashLoad(HashMap& map) {
	map.Load("hash_input.txt");
	cout << "Записи загружены!\n";
}

void ExecHashSave(HashMap& map) {
	if (!map.GetSize()) {
		cout << "Словарь пуст!\n";
		return;
	}

	map.Save("hash_output.txt");
	cout << "Записи сохранены!\n";
}