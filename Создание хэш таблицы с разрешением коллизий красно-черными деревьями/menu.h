#pragma once

#include "global.h"
#include "rbtMap.h"
#include "HashMap.h"


#define MENU_RBT_ITEMS_CNT 7
#define MENU_HASH_ITEMS_CNT 7
#define MENU_ADDITIONAL_ITEMS_CNT 1

enum class MenuItems {
	kRbtPrint,
	kRbtFind,
	kRbtInsert,
	kRbtDelete,
	kRbtClear,
	kRbtLoad,
	kRbtSave,
	kHashPrint,
	kHashFind,
	kHashInsert,
	kHashDelete,
	kHashClear,
	kHashLoad,
	kHashSave,
	kExit
};

const string kMenuStrings[] = {
	"Вывод на экран содержимого словаря",
	"Найти запись",
	"Добавить запись",
	"Удалить запись",
	"Очистить словарь",
	"Загрузить записи из файла",
	"Сохранить записи в файл",
	"Выход"
};

bool IsContinue(bool overrideFlag = false);
bool GetInt(int& inp, int min, int max, int* forbidden = nullptr);
bool GetStr(string& str, string rx);
void PrintMenu();

void ExecRbtPrint(Tree& map);
void ExecRbtFind(Tree& map);
void ExecRbtInsert(Tree& map);
void ExecRbtDelete(Tree& map);
void ExecRbtClear(Tree& map);
void ExecRbtLoad(Tree& map);
void ExecRbtSave(Tree& map);

void ExecHashPrint(HashMap& map);
void ExecHashFind(HashMap& map);
void ExecHashInsert(HashMap& map);
void ExecHashDelete(HashMap& map);
void ExecHashClear(HashMap& map);
void ExecHashLoad(HashMap& map);
void ExecHashSave(HashMap& map);