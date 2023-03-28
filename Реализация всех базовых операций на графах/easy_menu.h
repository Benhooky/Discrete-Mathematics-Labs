#pragma once

#include "globals.h"
#include "MyGraph.h"

#define MENU_ITEMS_MAX 13
#define MENU_ITEMS_MIN 0

enum class MenuItems {
	kGenGraph,
	kShimbell,
	kReachability,
	kDijkstra,
	kBellmanFoTmpBase,
	kFloydWarshall,
	kMinCostFlow,
	kKruskal,
	kPrim,
	kAmountMinTrees,
	kPrufer,
	kEulerCycle,
	kHamiltonCycle,
	kExit
};

const regex kRxYn("[YNyn]$");
const regex kRxNumber("^(([1-9])([0-9])*)|(0)$");


static const char* kMenuItemsArr[] = {
"Сгенерировать новый граф",
"Метод Шимбелла",
"Определение возможности построения маршрута",
"Алгоритм Дейкстры",
"Алгоритм Беллмана-Форда",
"Алгоритм Флойда-Уоршелла",
"Расчёт потока минимальной стоимости",
"Алгоритм Краскала",
"Алгоритм Прима",
"Подсчёт количества остовных деревьев в графе",
"Закодировать граф кодом Прюфера",
"Поиск эйлерова цикла",
"Поиск гамильтонова цикла",
"Выход"
};

bool IsContinue(bool overrideFlag = false);
bool GetInputInt(int& iInp, int min, int max, int forbidden = INT_MAX);
void PrintMenu();

MyGraph GenGraph();
void ExecShimbell(const MyGraph& graph);
void Rch_show(const MyGraph& graph);
void ExecDijkstra(const MyGraph& graph);
void ExecBellmanFoTmpBase(const MyGraph& graph);
void ExecFloydWarshall(const MyGraph& graph);
void ExecMinCostFlow(const MyGraph& graph);
void ExecKruskal(const MyGraph& graph);
void ExecPrim(const MyGraph& graph);
void ExecAmountMinTrees(const MyGraph& graph);
void ExecPrufer(const MyGraph& graph);
void ExecEulerCycle(const MyGraph& graph);
void ExecHamiltonCycle(const MyGraph& graph);


