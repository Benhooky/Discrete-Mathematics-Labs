#include "globals.h"
#include "MyGraph.h"
#include "easy_menu.h"

void main() {
	setlocale(LC_ALL, "Russian");
	int menuItem;
	MenuItems item;
	bool overrideFlag = false;

	MyGraph graph = GenGraph();
	ofstream fout("out.txt");
	for (int i = 0; i < 1000; i++) {
		fout << PascalRngg() << std::endl;
	}
	fout.close();
	do {
		PrintMenu();
		cout << '\n';

		do {
			cout << "Выберете пункт меню:\n";
		} while (!GetInputInt(menuItem, MENU_ITEMS_MIN, MENU_ITEMS_MAX));
		cout << '\n';

		item = static_cast<MenuItems>(menuItem);
		switch (item) {
		case MenuItems::kGenGraph:
			graph = GenGraph();
			break;
		case MenuItems::kShimbell:
			ExecShimbell(graph);
			break;
		case MenuItems::kReachability:
			Rch_show(graph);
			break;
		case MenuItems::kDijkstra:
			ExecDijkstra(graph);
			break;
		case MenuItems::kBellmanFoTmpBase:
			ExecBellmanFoTmpBase(graph);
			break;
		case MenuItems::kFloydWarshall:
			ExecFloydWarshall(graph);
			break;
		case MenuItems::kMinCostFlow:
			ExecMinCostFlow(graph);
			break;
		case MenuItems::kKruskal:
			ExecKruskal(graph);
			break;
		case MenuItems::kPrim:
			ExecPrim(graph);
			break;
		case MenuItems::kAmountMinTrees:
			ExecAmountMinTrees(graph);
			break;
		case MenuItems::kPrufer:
			ExecPrufer(graph);
			break;
		case MenuItems::kEulerCycle:
			ExecEulerCycle(graph);
			break;
		case MenuItems::kHamiltonCycle:
			ExecHamiltonCycle(graph);
			break;
		case MenuItems::kExit:
			overrideFlag = true;
			break;
		default:
			break;
		}
	} while (IsContinue(overrideFlag));

}
