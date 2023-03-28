#include "menu.h"

//#define CONTINUE

int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	MenuItems item;
	Tree rbtMap;
	HashMap hashMap;
	string sInp;
	int iInp;
	bool isOverride = false;

	do {
		cout << '\n';
		PrintMenu();
		cout << '\n';

		do {
			cout << "Выберете пункт меню: ";
		} while (!GetInt(iInp, 0, MENU_RBT_ITEMS_CNT + MENU_HASH_ITEMS_CNT + MENU_ADDITIONAL_ITEMS_CNT - 1));
		cout << '\n';

		item = static_cast<MenuItems>(iInp);
		switch (item) {
		case MenuItems::kRbtPrint:
			ExecRbtPrint(rbtMap);
			break;
		case MenuItems::kRbtFind:
			ExecRbtFind(rbtMap);
			break;
		case MenuItems::kRbtInsert:
			ExecRbtInsert(rbtMap);
			break;
		case MenuItems::kRbtDelete:
			ExecRbtDelete(rbtMap);
			break;
		case MenuItems::kRbtClear:
			ExecRbtClear(rbtMap);
			break;
		case MenuItems::kRbtLoad:
			ExecRbtLoad(rbtMap);
			break;
		case MenuItems::kRbtSave:
			ExecRbtSave(rbtMap);
			break;
		case MenuItems::kHashPrint:
			ExecHashPrint(hashMap);
			break;
		case MenuItems::kHashFind:
			ExecHashFind(hashMap);
			break;
		case MenuItems::kHashInsert:
			ExecHashInsert(hashMap);
			break;
		case MenuItems::kHashDelete:
			ExecHashDelete(hashMap);
			break;
		case MenuItems::kHashClear:
			ExecHashClear(hashMap);
			break;
		case MenuItems::kHashLoad:
			ExecHashLoad(hashMap);
			break;
		case MenuItems::kHashSave:
			ExecHashSave(hashMap);
			break;
		case MenuItems::kExit:
			isOverride = true;
			break;
		default:
			break;
		}

		cout << '\n';
#ifndef CONTINUE
	} while (IsContinue(isOverride));
#else 
	} while (true);
#endif 

	return 0;
}