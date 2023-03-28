#include "easy_menu.h"
using namespace std;
bool IsContinue(bool overrideFlag) {
	if (overrideFlag) {
		return false;
	}
	else {
		char d;
		string strInp;
		bool isOk = false;
		do {
			cout << "����������? (Y/N): ";
			getline(cin, strInp);
			if (regex_match(strInp, kRxYn)) {
				isOk = true;
				d = strInp[0];
				switch (d) {
				case 'Y':
				case 'y':
					return true;
				case 'N':
				case 'n':
					return false;
				}
			}
			else {
				isOk = false;
				cout << "������������ ����!\n";
			}
		} while (!isOk);
	}
}

void PrintMenu() {
	cout << '\n';
	for (int i = 0; i <= MENU_ITEMS_MAX; i++) {
		cout << i << ": " << kMenuItemsArr[i] << '\n';
	}
	cout << '\n';
}

bool GetInputInt(int& iInp, int min, int max, int forbidden) {
	string strInp;
	bool res;
	getline(cin, strInp);
	if (regex_match(strInp, kRxNumber)) {
		iInp = stoi(strInp);
		if (InRange(iInp, min, max)) {
			if (forbidden == INT_MAX) {
				res = true;
			}
			else {
				if (iInp != forbidden) {
					res = true;
				}
				else {
					res = false;
				}
			}

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
		cout << "������������ ����!\n";
		return false;
	}
}


MyGraph GenGraph() {
	int vertCnt;
	do {
		cout << "������� ���������� ������ ����� n (" << 2 << " <= n <= " << 50 << "):\n";
	} while (!GetInputInt(vertCnt, 2, 50));
	cout << '\n';

	MyGraph graph(vertCnt);

	cout << "������� ��������� ������:\n";
	PrintMatrix(graph.GetAdjMatrix());
	cout << "������� �����\n";
	graph.AssignWeights();
	PrintMatrix(graph.GetWMatrix(WeightsType::Pos));
	cout << '\n';

	return graph;
}

void ExecShimbell(const MyGraph& graph) {
	int edgesCnt, mType;
	do {
		cout << "������� ���������� �����:\n";
	} while (!GetInputInt(edgesCnt, 1, graph.GetsecondCount() - 1));
	cout << '\n';
	do {
		cout << "�������� ���������� � �������:\n������� ���������� ��������� (0), ������� ���������� ��������� (1)\n";
	} while (!GetInputInt(mType, 0, 1));
	cout << '\n';
	cout << "������� �����:\n";
	PrintMatrix(graph.GetWMatrix(WeightsType::Pos));
	cout << '\n';
	cout << "������� ��������:\n";
	PrintMatrix(graph.Shimbell(edgesCnt, static_cast<SrtOrLng>(mType)));
	cout << '\n';
}

void Rch_show(const MyGraph& graph) {
	int vert1, vert2;
	vector<vector<int>> RchMatrix = graph.GetRchMatrix();
	do {
		cout << "������� ����� ������ �������:\n";
	} while (!GetInputInt(vert1, 1, graph.GetsecondCount()));
	cout << '\n';
	do {
		cout << "������� ����� ������ �������:\n";
	} while (!GetInputInt(vert2, 1, graph.GetsecondCount()));
	cout << '\n';
	vert1--;
	vert2--;
	cout << "������� ������������:\n";
	PrintMatrix(RchMatrix);
	cout << '\n';
	if (vert1 == vert2) {
		cout << "�� ��� �������� ���� ��������\n";
	}
	else {
		if (RchMatrix[vert1][vert2]) {
			cout << "C��������� " << RchMatrix[vert1][vert2] << " ��������� ����� ������� ���������!\n";
		}
		else {
			cout << "�� ���������� ��������� ����� ������� ���������!\n";
		}
	}
	
	cout << '\n';
}

void ExecDijkstra(const MyGraph& graph) {
	int InVert, Counter = 0;
	do {
		cout << "������� �������� �������:\n"<<'\n';;
	} while (!GetInputInt(InVert, 1, graph.GetsecondCount()));
	cout << "������� �����:\n" << '\n';
	PrintMatrix(graph.GetWMatrix(WeightsType::Pos));
	vector<int> distances = graph.Dijkstra(InVert-1, Counter);
	vector<vector<int>> Paths = graph.Revive(InVert-1, distances, graph.GetWMatrix(WeightsType::ModPos));
	for (int i = 0; i < graph.GetsecondCount(); i++) {
		if (i != InVert-1) {
			if (Paths[i][0] != 999) {
				cout << "���������� ���� ������ " << setw(2) << distances[i] << " �� ������� " << setw(2) << i + 1 << ": ";
				for (int j = Paths[i].size() - 1; j > 0; j--) {
					cout << setw(2) << Paths[i][j] + 1 << "->";
				}
				cout << setw(2) << Paths[i][0] + 1 << '\n';
			}
			else {
				cout << "�� ������� " << setw(2) << i + 1 << " ���� ���!\n";
			}
		}
	}
	cout << '\n' << "���������� ��������: " << Counter << '\n' << '\n';

}

void ExecBellmanFoTmpBase(const MyGraph& graph) {
	int InVert, Counter = 0;

	do {
		cout << "������� �������� �������:\n";;
	} while (!GetInputInt(InVert, 1, graph.GetsecondCount()));
	cout << '\n';
	InVert--;
	cout << "������ �� �� ��������� ������� ����� �������������� ����������? (Y/N)\n";
	string check;
	vector<int> distances;
	vector<vector<int>> Paths;
	while (check != "Y" and check != "N") {
		cin >> check;
		if (check == "Y") {
			cout << "������� �����:\n";
			PrintMatrix(graph.GetWMatrix(WeightsType::Mx));
			cout << '\n';

			distances = graph.BellmanFoTmpBase(InVert, graph.GetWMatrix(WeightsType::Mx), Counter);
			Paths = graph.Revive(InVert, distances, graph.GetWMatrix(WeightsType::ModMx));
		}
		else if (check == "N") {
			cout << "������� �����:\n";
			PrintMatrix(graph.GetWMatrix(WeightsType::Pos));
			cout << '\n';

			distances = graph.BellmanFoTmpBase(InVert, graph.GetWMatrix(WeightsType::Pos), Counter);
			Paths = graph.Revive(InVert, distances, graph.GetWMatrix(WeightsType::Pos));
		}
		else {
			cout << "�������� ����, ������ Y ��� N:\n";
		}
	}
	for (int i = 0; i < graph.GetsecondCount(); i++) {
		if (i != InVert) {
			if (Paths[i][0] != 999) {
				cout << "���������� ���� ������ " << setw(3) << distances[i] << " �� ������� " << setw(2) << i + 1 << ": ";
				for (int j = Paths[i].size() - 1; j > 0; j--) {
					cout << setw(2) << Paths[i][j] + 1 << " -> ";
				}
				cout << setw(2) << Paths[i][0] + 1 << '\n';
			}
			else {
				cout << "�� ������� " << setw(2) << i + 1 << " ���� ���!\n";
			}
		}
	}
	cout << '\n';
	cout << "���������� ��������: " << Counter << '\n';
	cout << '\n';
}

void ExecFloydWarshall(const MyGraph& graph) {
	int Counter = 0;
	cout << '\n';
	cout << "������ �� �� ��������� ������� ����� �������������� ����������? (Y/N)\n";
	char check;
	cin >> check;
	while (check != 'Y' and check != 'N') {
		cout << "�������� ����, ������� Y ��� N?\n";
		cin >> check;
	}
	vector<vector<int>> distancesMx = graph.FloydWarshall(Counter,check);

	cout << "������� ����������:\n";
	for (int i = 0; i < graph.GetsecondCount(); i++) {
		for (int j = 0; j < graph.GetsecondCount(); j++) {
			if (distancesMx[i][j] != 999) {
				cout << setw(3) << distancesMx[i][j] << " ";
			}
			else {
				cout << setw(3) << "999" << " ";
			}
		}
		cout << '\n';
	}
	cout << '\n';

	cout << "���������� ��������: " << Counter << '\n';
	cout << '\n';
}
void ExecMinCostFlow(const MyGraph& graph) {
	int vert1, vert2;
	do {
		cout << "������� ����� ������ �������:\n";
	} while (!GetInputInt(vert1, 1, graph.GetsecondCount()));
	cout << '\n';
	do {
		cout << "������� ����� ������ �������:\n";
	} while (!GetInputInt(vert2, 1, graph.GetsecondCount(), vert1));
	cout << '\n';
	vert1--;
	vert2--;

	cout << "������� ���������� ������������:\n";
	PrintMatrix(graph.GetMxFlowMatrix());
	cout << '\n';

	int maxFlow = graph.foTmpBaseFulkerson(vert1, vert2);
	cout << "������������ �����: " << maxFlow << '\n';
	cout << "������������ �����: " << maxFlow * 2 / 3 << '\n';
	cout << '\n';

	cout << "������� ���������� �� ������� ������:\n";
	PrintMatrix(graph.GetWMatrix(WeightsType::ModPos));
	cout << '\n';

	McfRetVals retVals;
	int mcf = graph.MinCostFlow(vert1, vert2, (maxFlow * 2 / 3), retVals);

	int resCnt = retVals.Flows.size();
	for (int k = 0; k < resCnt; k++) {
		cout << "����� �������� " << retVals.Flows[k] << " �� ���������� " << retVals.CostForPath[k] << " �� ������� ������\n";
		cout << "�� ����: ";
		for (int i = retVals.Paths[k].size() - 1; i > 0; i--) {
			cout << retVals.Paths[k][i] + 1 << " -> ";
		}
		cout << retVals.Paths[k][0] + 1;
		cout << '\n';
		cout << "�������� ���������: " << retVals.Flows[k] * retVals.CostForPath[k] << '\n';
		cout << '\n';
	}

	cout << "�������� ������ ����������� ���������: " << mcf << '\n';
	cout << '\n';
}


void ExecKruskal(const MyGraph& graph) {
	int Counter = 0, sum = 0;
	vector<vector<int>> Tree = graph.Kruskal(graph.GetWMatrix(WeightsType::Pos), &Counter, &sum);

	cout << "������� ����� ����������� ������:\n";
	PrintMatrix(Tree);
	cout << '\n';

	cout << "��� ����������� ������: " << sum << '\n';
	cout << '\n';

	cout << "���������� ��������: " << Counter << '\n';
	cout << '\n';
}

void ExecPrim(const MyGraph& graph) {
	int Counter = 0, sum = 0;
	vector<vector<int>> Tree = graph.Prim(graph.GetWMatrix(WeightsType::Pos), &Counter, &sum);

	cout << "������� ����� ����������� ������:\n";
	PrintMatrix(Tree);
	cout << '\n';

	cout << "��� ����������� ������: " << sum << '\n';
	cout << '\n';

	cout << "���������� ��������: " << Counter << '\n';
	cout << '\n';
}

void ExecAmountMinTrees(const MyGraph& graph) {
	cout << "������� ��������:\n";
	PrintMatrix(graph.GenKirchhoffMatrix());
	cout << '\n';

	cout << "���������� �������� �������� � �����: " << graph.AmountMinTrees() << '\n';
	cout << '\n';
}

void ExecPrufer(const MyGraph& graph) {
	vector<vector<int>> WMx = graph.Kruskal(graph.GetWMatrix(WeightsType::Pos));
	vector<vector<int>> decodedMx;
	vector<int> prufCode, prufWeights;

	cout << "������� ����� ����������� ������:\n";
	PrintMatrix(WMx);
	cout << '\n';
	graph.PruferEncode(WMx, prufCode, prufWeights);

	cout << "��� �������:\n";
	for (int i = 0; i < prufCode.size(); i++) {
		cout << prufCode[i] << ' ';
	}
	cout << '\n';

	cout << "���� ����:\n";
	for (int i = 0; i < prufWeights.size(); i++) {
		cout << prufWeights[i] << ' ';
	}
	cout << '\n';

	decodedMx = graph.PruferDecode(prufCode, prufWeights);
	cout << "\n��������������� ������� ����� ����������� ������:\n";
	PrintMatrix(decodedMx);
	cout << '\n';

	if (decodedMx == WMx) {
		cout << "������������� �����.\n";
	}
	else {
		cout << "������������� �������.\n";
	}

	cout << '\n';
}

void ExecEulerCycle(const MyGraph& graph) {
	Euler_Hamilton res;
	vector<vector<int>> resWMx;
	vector<int> eulerPath = graph.EulerCycles(graph.GetWMatrix(WeightsType::Pos), resWMx, res);

	switch (res) {
	case Euler_Hamilton::FalseVert:
		cout << "���� �� ���� ������ �� ����� ������� ����!\n";
		break;
	case Euler_Hamilton::FalseMod:
		cout << "���� �� �������� ���������. ��������������� �� �������� ����� ��������.\n\n";
	case Euler_Hamilton::True:
		cout << "������� ������� �������� �����:\n";
		PrintMatrix(resWMx);
		cout << '\n';
		cout << "������� ����:\n";
		for (int i = 0; i < eulerPath.size() - 1; i++) {
			cout << eulerPath[i] + 1 << " -> ";
		}
		cout << eulerPath[eulerPath.size() - 1] + 1 << '\n';
		break;
	default:
		break;
	}
	cout << '\n';
}

void ExecHamiltonCycle(const MyGraph& graph) {
	Euler_Hamilton res;
	vector<vector<int>> resWMx;
	int minLen;
	vector<int> minPath = graph.Hamilton(graph.GetWMatrix(WeightsType::Pos), resWMx, res, minLen);

	switch (res) {
	case Euler_Hamilton::FalseVert:
		cout << "���� �� ���� ������ �� ����� ����������� ����!\n";
		break;
	case Euler_Hamilton::FalseMod:
		cout << "���� �� �������� �������������. ��������������� �� ������������ ����� ��������.\n\n";
	case Euler_Hamilton::True:
		cout << "������� ������� ������������ �����:\n";
		PrintMatrix(resWMx);
		cout << '\n';
		cout << "����������� ����������� ����:\n";
		for (int i = 0; i < minPath.size() - 1; i++) {
			cout << minPath[i] + 1 << " -> ";
		}
		cout << minPath[minPath.size() - 1] + 1 << '\n';
		cout << "��� ����: " << minLen << '\n';
		break;
	default:
		break;
	}
	cout << '\n';
}