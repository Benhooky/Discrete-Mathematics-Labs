#include "MyGraph.h"
vector<int> MyGraph::Prepare() const {	
	vector<int> VrtxDegr;
	int tmpVertDeg;
	int Cnt = VrtxCnt - 1;
	for (int i = 0; i < Cnt - 1; i++) {
		do {
			tmpVertDeg = PascalRngg();
		} while (tmpVertDeg >= VrtxCnt);
		VrtxDegr.push_back(tmpVertDeg);
	}
	sort(VrtxDegr.begin(), VrtxDegr.end(), greater<int>());
	for (int i = 0; i < Cnt - 1; i++) {
		if (VrtxDegr[i] > (Cnt - i)) {
			VrtxDegr[i] = Cnt - i;
		}
	}
	return VrtxDegr;
}

void MyGraph::AssignWeights() {
	std::random_device TmpBase;
	std::mt19937 mersenne(TmpBase());
	for (int i = 0; i < VrtxCnt; i++) {
		for (int j = i + 1; j < VrtxCnt; j++) {
			if (AdjMatrix[i][j]) {
				PosWMatrix[i][j] = mersenne() % (15 - 1) + 1;
			}
		}
	}
}

void MyGraph::MixWeights() {
	MxdWMatrix = PosWMatrix;
	int posOrNeg;
	std::random_device TmpBase;
	std::mt19937 mersenne(TmpBase());
	for (int i = 0; i < VrtxCnt; i++) {
		for (int j = i + 1; j < VrtxCnt; j++) {
			if (MxdWMatrix[i][j]) {
				posOrNeg = mersenne() % 2;
				if (posOrNeg) {
					MxdWMatrix[i][j] *= -1;
				}
			}
		}
	}
}

void MyGraph::ModifyWeights(vector<vector<int>>& WeightsMatrix, vector<vector<int>>& modified) {
	modified = WeightsMatrix;
	for (int i = 0; i < VrtxCnt; i++) {
		for (int j = 0; j < VrtxCnt; j++) {
			if (modified[i][j] == 0) {
				modified[i][j] = 999;
			}
		}
	}
}

MyGraph::MyGraph(int n) :	VrtxCnt(n), AdjMatrix(n, vector<int>(n, 0)), PosWMatrix(n, vector<int>(n, 0)),
							MxdWMatrix(), ModiPosWMatrix(), ModiMxdWMatrix(), RchMatrix(), MxFlowMatrix()
						{
	if (InRange(VrtxCnt, 2, 50)) {
		vector<int> vertDegrees = Prepare();
		MyShuffler<int> TmpShuffler;
		for (int i = 0; i < VrtxCnt - 2; i++) {
			TmpShuffler.Clear();
			for (int j = i + 1; j < VrtxCnt; j++) {
				TmpShuffler.Push(j);
			}
			TmpShuffler.Shuffle();
			for (int j = 0; j < vertDegrees[i]; j++) {
				AdjMatrix[i][TmpShuffler.Pop()] = 1;
			}
		}
		AdjMatrix[VrtxCnt - 2][VrtxCnt - 1] = 1;
		AssignWeights();
		GenRchMatrix();
		GenMxFlowMatrix();
		MixWeights();
		ModifyWeights(PosWMatrix, ModiPosWMatrix);
		ModifyWeights(MxdWMatrix, ModiMxdWMatrix);
		
	}
}

int MyGraph::GetsecondCount() const{
	return VrtxCnt;
}

vector<vector<int>> MyGraph::GetAdjMatrix() const {
	return AdjMatrix;
}

vector<vector<int>> MyGraph::GetWMatrix(WeightsType type) const {
	switch (type) {
	case WeightsType::Pos:
		return PosWMatrix;
		break;
	case WeightsType::Mx:
		return MxdWMatrix;
		break;
	case WeightsType::ModPos:
		return ModiPosWMatrix;
		break;
	case WeightsType::ModMx:
		return ModiMxdWMatrix;
		break;
	default:
		break;
	}
}

vector<vector<int>> MyGraph::ShimbellMult(const vector<vector<int>> mxA, const vector<vector<int>> mxB, SrtOrLng mode) const {
	vector<vector<int>> resMatrix(VrtxCnt, vector<int>(VrtxCnt, 0));
	vector<int> buf;
	bool check;
	for (int i = 0; i < VrtxCnt; i++) {
		for (int j = 0; j < VrtxCnt; j++) {
			buf.clear();
			check = false;
			for (int k = 0; k < VrtxCnt; k++) {
				if ((mxA[i][k] != 0) && (mxB[k][j] != 0)) {
					buf.push_back(mxA[i][k] + mxB[k][j]);
					check = true;
				}
			}
			if (check) {
				if (mode == SrtOrLng::Srt) {
					resMatrix[i][j] = *std::min_element(buf.begin(), buf.end());
				}
				else {	
					resMatrix[i][j] = *std::max_element(buf.begin(), buf.end());
				}
			}
			else {
				resMatrix[i][j] = 0;
			}
		}
	}
	return resMatrix;
}

vector<vector<int>> MyGraph::Shimbell(int cnt, SrtOrLng mode) const {
	vector<vector<int>> resMatrix = PosWMatrix;
	for (int i = 0; i < cnt - 1; i++) {
		resMatrix = ShimbellMult(resMatrix, PosWMatrix, mode);
	}
	return resMatrix;
}

vector<vector<int>> MyGraph::GetRchMatrix() const {
	return RchMatrix;
}

void MyGraph::GenRchMatrix() {
	vector<vector<int>> boolExpMatrix = AdjMatrix;
	RchMatrix = vector<vector<int>>(VrtxCnt, vector<int>(VrtxCnt, 0));
	for (int i = 0; i < VrtxCnt - 1; i++) {
		boolExpMatrix = matrixBoolMult(boolExpMatrix, AdjMatrix);
		RchMatrix = matrixAdd(RchMatrix, boolExpMatrix);
	}
	for (int i = 0; i < VrtxCnt; i++) {
		RchMatrix[i][i] = 1;
	}
}


vector<int> MyGraph::Dijkstra(int InVert, int& Counter) const {
	Counter = 0;
	vector<int> distances(VrtxCnt, 999);
	distances[InVert] = 0;
	pair<int, int> cur;
	int newfirst;
	priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<pair<int, int>>> pq;
	pq.push(make_pair(0, InVert));
	while (!pq.empty()) {
		cur = pq.top();
		pq.pop();
		for (int i = cur.second + 1; i < VrtxCnt; i++, Counter++) {
			if (ModiPosWMatrix[cur.second][i] != 999) {
				newfirst = cur.first + ModiPosWMatrix[cur.second][i];
				if (newfirst < distances[i]) {
					distances[i] = newfirst;
					pq.push(make_pair(newfirst, i));													
				}
			}
		}
	}
	return distances;
}


vector<vector<int>> MyGraph::Revive(int InVert, const vector<int>& distances, const vector<vector<int>> WMx) const {
	vector<vector<int>> Paths(VrtxCnt, vector<int>());
	int tmp, curVert;
	for (int i = 0; i < VrtxCnt; i++) {
		if (distances[i]) {		
			if (distances[i] != 999) {	
				curVert = i;
				Paths[i].push_back(curVert);
				while (curVert != InVert) {
					for (int j = 0; j < VrtxCnt; j++) {																										
						if (WMx[j][curVert] != 999) {
							if ((distances[curVert] - WMx[j][curVert]) == distances[j]) {
								curVert = j;
								Paths[i].push_back(j);
								break;
							}
						}
					}
				}
			}
			else {
				Paths[i].push_back(999);
			}
		}
		else {
			Paths[i].push_back(999);
		}
	}
	return Paths;
}

vector<int> MyGraph::BellmanFoTmpBase(int InVert, vector<vector<int>> wieghtsMx, int& Counter) const {
	Counter = 0;
	vector<int> distances(VrtxCnt, 999);
	distances[InVert] = 0;

	int curVert, newfirst;

	deque<int> dq;
	dq.push_back(InVert);

	while (!dq.empty()) {
		curVert = dq.front();
		dq.pop_front();
		for (int i = curVert + 1; i < VrtxCnt; i++, Counter++) {
			if ((wieghtsMx[curVert][i] != 999)&&(wieghtsMx[curVert][i]!=0)) {
				newfirst = distances[curVert] + wieghtsMx[curVert][i];
				if (newfirst < distances[i]) {
					distances[i] = newfirst;
					if (std::find(dq.begin(), dq.end(), i) == dq.end()) {		
						dq.push_back(i);										
					}
					else {														
						std::remove(dq.begin(), dq.end(), i);					
						dq.push_front(i);										
					}
				}
			}
		}
	}

	return distances;
}

vector<vector<int>> MyGraph::FloydWarshall(int& Counter,char check) const {
	vector<vector<int>> distancesMx;
	if (check == 'Y') {
		distancesMx = ModiMxdWMatrix;
	}
	else {
		distancesMx = ModiPosWMatrix;
	}
	for (int i = 0; i < VrtxCnt; i++) {
		for (int j = 0; j < VrtxCnt; j++) {
			for (int k = 0; k < VrtxCnt; k++, Counter++) {
				if (distancesMx[i][k] != 999 && distancesMx[k][j] != 999) {
					distancesMx[i][j] = std::min(distancesMx[i][j], (distancesMx[i][k] + distancesMx[k][j]));
				}
			}
		}
	}

	for (int i = 0; i < VrtxCnt; i++) {
		distancesMx[i][i] = 0;
	}

	return distancesMx;
}


void MyGraph::GenMxFlowMatrix() {
	std::random_device TmpBase;
	std::mt19937 mersenne(TmpBase());
	MxFlowMatrix = AdjMatrix;
	for (int i = 0; i < VrtxCnt; i++) {
		for (int j = i + 1; j < VrtxCnt; j++) {
			if (AdjMatrix[i][j]) {
				MxFlowMatrix[i][j] = mersenne() % (20 - 1) + 1;
			}
		}
	}
}

vector<vector<int>> MyGraph::GetMxFlowMatrix() const{
	return MxFlowMatrix;
}

vector<vector<int>> MyGraph::AddFictVert() const{
	std::stack<int> tmp;
	bool isSource;
	int tmpVert;
	for (int i = 0; i < VrtxCnt; i++) {
		isSource = true;
		for (int j = 0; j < VrtxCnt; j++) {
			if (AdjMatrix[j][i]) {
				isSource = false;
				break;
			}
		}
		if (isSource) {
			tmp.push(i);
		}
	}
	if (tmp.size() > 1) { 
		vector<vector<int>> resMxFlowMatrix(VrtxCnt + 1, vector<int>(VrtxCnt + 1, 0));
		while (!tmp.empty()) {
			resMxFlowMatrix[0][tmp.top() + 1] = std::accumulate(MxFlowMatrix[tmp.top()].begin(), MxFlowMatrix[tmp.top()].end(), 0);
			tmp.pop();
		}
		for (int i = 0; i < VrtxCnt; i++) {
			for (int j = 0; j < VrtxCnt; j++) {
				resMxFlowMatrix[i + 1][j + 1] = MxFlowMatrix[i][j];
			}
		}
		return resMxFlowMatrix;
	}
	else {
		return MxFlowMatrix;
	}
}

bool MyGraph::bfs(vector<vector<int>> graphMx, int v1, int v2, vector<int>* path, int* Counter) const{
	vector<bool> isVisitedArr(graphMx.size(), false);
	std::queue<int> q;
	int curVert;

	q.push(v1);
	isVisitedArr[v1] = true;
	if (path) {
		(*path)[v1] = -1;
	}
	
	while (!q.empty()) {
		curVert = q.front();
		q.pop();

		for (int i = 0; i < graphMx.size(); i++) {
			if (Counter) {
				(*Counter)++;
			}
			if ((isVisitedArr[i] == false) && (graphMx[curVert][i] != 0)) {
				if (path) {
					(*path)[i] = curVert;
				}
				if (i == v2) {
					return true;
				}
				q.push(i);
				isVisitedArr[i] = true;
			}
		}
	}
	return false;
}

bool MyGraph::bfs_FoTmpBaseFulkerson(vector<vector<int>> residualG, int source, int sink, vector<int>& path) const{
	vector<bool> isVisitedArr(residualG.size(), false);
	std::queue<int> q;
	int curVert;

	q.push(source);
	isVisitedArr[source] = true;
	path[source] = -1;

	while (!q.empty()) {
		curVert = q.front();
		q.pop();

		for (int i = 0; i < residualG.size(); i++) {
			if ((isVisitedArr[i] == false) && (residualG[curVert][i] > 0)) {
				path[i] = curVert;
				if (i == sink) {
					return true;
				}
				q.push(i);
				isVisitedArr[i] = true;
			}
		}
	}
	return false;
}

int MyGraph::foTmpBaseFulkerson(int source, int sink) const {
	int tmpSink = sink;
	vector<vector<int>> residualGraph = AddFictVert();
	if (residualGraph.size() != VrtxCnt) {
		source++;
		tmpSink++;
	}
	vector<int> path(residualGraph.size(), 0);
	int maxFlow = 0;
	int curFlow;
	while (bfs_FoTmpBaseFulkerson(residualGraph, source, tmpSink, path)) {
		curFlow = 999;
		for (int i = tmpSink; i != source; i = path[i]) {
			curFlow = std::min(curFlow, residualGraph[path[i]][i]);
		}
		for (int i = tmpSink; i != source; i = path[i]) {
			residualGraph[path[i]][i] -= curFlow;
			residualGraph[i][path[i]] += curFlow;
		}
		maxFlow += curFlow;
	}
	return maxFlow;
}

int MyGraph::MinCostFlow(int source, int sink, int flow, McfRetVals& retVals) const {
	int curCost = 0, bottleNeck = 999, minCostFlow = 0;
	int Counter; 
	vector<vector<int>> costMx = ModiPosWMatrix, flowMx = MxFlowMatrix;
	vector<int> path;
	vector<pair<int, int>> edgesToRemove;
	while (flow) {
		curCost = 0;
		bottleNeck = 999;
		edgesToRemove.clear();
		path = Revive(source, BellmanFoTmpBase(source, costMx, Counter), costMx)[sink];
		retVals.Paths.push_back(path);
		for (int i = path.size() - 1; i > 0; i--) {
			bottleNeck = std::min(bottleNeck, flowMx[path[i]][path[i - 1]]);
		}
		bottleNeck = std::min(bottleNeck, flow);
		retVals.Flows.push_back(bottleNeck);
		for (int i = path.size() - 1; i > 0; i--) {
			flowMx[path[i]][path[i - 1]] -= bottleNeck;
			curCost += costMx[path[i]][path[i - 1]];
			if (flowMx[path[i]][path[i - 1]] == 0) {
				edgesToRemove.push_back(std::make_pair(path[i], path[i - 1]));
			}
		}
		retVals.CostForPath.push_back(curCost);

		minCostFlow += bottleNeck * curCost;

		for (auto it = edgesToRemove.begin(); it != edgesToRemove.end(); ++it) {
			costMx[it->first][it->second] = 999;
		}

		flow -= bottleNeck;
	}
	retVals.ModCostMx = costMx;
	retVals.ModFlowMx = flowMx;
	return minCostFlow;
}

priority_queue<Edge, vector<Edge>, std::greater<Edge>> MyGraph::SortEdges(vector<vector<int>> WeightsMx) const {
	priority_queue<Edge, vector<Edge>, std::greater<Edge>> pq;

	for (int i = 0; i < VrtxCnt; i++) {
		for (int j = 0; j < VrtxCnt; j++) {
			if (WeightsMx[i][j] != 0) {
				pq.push(Edge(i, j, WeightsMx[i][j]));
			}
		}
	}

	return pq;
}

vector<vector<int>> MyGraph::Kruskal(vector<vector<int>> WeightsMx, int* Counter, int* sum) const {
	vector<vector<int>> Tree = vector<vector<int>>(VrtxCnt, vector<int>(VrtxCnt, 0));
	priority_queue<Edge, vector<Edge>, greater<Edge>> pq = SortEdges(WeightsMx);
	if (Counter) {
		(*Counter) = 0;
	}
	Edge edge;
	while (!pq.empty()) {
		edge = pq.top();
		pq.pop();
		if (!bfs(Tree, edge.vert1, edge.vert2, nullptr, nullptr)) {
			Tree[edge.vert1][edge.vert2] = WeightsMx[edge.vert1][edge.vert2];
			Tree[edge.vert2][edge.vert1] = WeightsMx[edge.vert1][edge.vert2];
		}
		if (Counter) {
			(*Counter)++;
		}
	}
	if (sum) {
		(*sum) = 0;
		for (int i = 0; i < VrtxCnt; i++) {
			for (int j = i + 1; j < VrtxCnt; j++) {
				if (Tree[i][j] != 0) {
					(*sum) += Tree[i][j];
				}
			}
		}
	}

	return Tree;
}


vector<vector<int>> MyGraph::Prim(vector<vector<int>> WeightsMx, int* Counter, int* sum) const {
	vector<vector<int>> Tree = vector<vector<int>>(VrtxCnt, vector<int>(VrtxCnt, 0));
	vector<int> mstPath(VrtxCnt, 0);
	mstPath[0] = -1;
	vector<int> mstKeys(VrtxCnt, 999); 
	mstKeys[0] = 0;
	vector<bool> isInMst(VrtxCnt, false);
	int minKey, minIndex;
	if (Counter) {
		(*Counter) = 0;
	}
	for (int i = 0; i < VrtxCnt; i++) {
		for (int j = 0; j < i; j++) {
			WeightsMx[i][j] = WeightsMx[j][i];
		}
	}
	for (int i = 0; i < VrtxCnt - 1; i++) {
		minKey = 999;
		for (int j = 0; j < VrtxCnt; j++) {
			if ((isInMst[j] == false) && (mstKeys[j] < minKey)) {
				minIndex = j;
				minKey = mstKeys[j];
			}
			if (Counter) {
				(*Counter)++;
			}
		}
		isInMst[minIndex] = true;
		for (int j = 0; j < VrtxCnt; j++) {
			if ((WeightsMx[minIndex][j] != 0) && (isInMst[j] == false) && (WeightsMx[minIndex][j] < mstKeys[j])) {
				mstKeys[j] = WeightsMx[minIndex][j];
				mstPath[j] = minIndex;
			}
			if (Counter) {
				(*Counter)++;
			}
		}
	}
	for (int i = 1; i < VrtxCnt; i++) {
		Tree[i][mstPath[i]] = WeightsMx[i][mstPath[i]];
		Tree[mstPath[i]][i] = WeightsMx[i][mstPath[i]];
	}
	if (sum) {
		(*sum) = 0;
		for (int i = 0; i < VrtxCnt; i++) {
			for (int j = i + 1; j < VrtxCnt; j++) {
				if (Tree[i][j] != 0) {
					(*sum) += Tree[i][j];
				}
			}
		}
	}
	return Tree;
}

vector<vector<int>> MyGraph::GenKirchhoffMatrix() const {
	vector<vector<int>> kirchhoffMx = vector<vector<int>>(VrtxCnt, vector<int>(VrtxCnt, 0));
	int vertDeg;
	vector<vector<int>> modAdjMx = AdjMatrix;

	for (int i = 0; i < VrtxCnt; i++) {
		for (int j = 0; j < i; j++) {
			modAdjMx[i][j] = AdjMatrix[j][i];
		}
	}

	for (int i = 0; i < VrtxCnt; i++) {
		vertDeg = 0;
		for (int j = 0; j < VrtxCnt; j++) {
			if (modAdjMx[i][j]) {
				kirchhoffMx[i][j] = -1;
				vertDeg++;
			}
		}
		kirchhoffMx[i][i] = vertDeg;
	}
	return kirchhoffMx;
}

int MyGraph::AmountMinTrees() const {
	vector<vector<int>> kirchhoff = GenKirchhoffMatrix();
	vector<vector<int>> kirchhoffMinor = vector<vector<int>>(VrtxCnt - 1, vector<int>(VrtxCnt - 1, 0));
	for (int i = 0; i < VrtxCnt - 1; i++) {
		for (int j = 0; j < VrtxCnt - 1; j++) {
			kirchhoffMinor[i][j] = kirchhoff[i][j];
		}
	}
	return MatrixMinor(kirchhoffMinor);
}

void MyGraph::PruferEncode(vector<vector<int>>& WeightsMx, vector<int>& prC, vector<int>& PrW) const {
	if (prC.size() == WeightsMx.size() - 2) {
		for (int i = 0; i < WeightsMx.size(); i++) {
			for (int j = 0; j < WeightsMx.size(); j++) {
				if (WeightsMx[i][j] != 0) {
					prC.push_back(i + 1);
					PrW.push_back(WeightsMx[i][j]);
					return;
				}
			}
		}
	}
	Edge edge;
	vector<vector<int>> tmpWeightsMx = WeightsMx;
	int cnt;
	for (int i = 0; i < WeightsMx.size(); i++) {
		cnt = 0;
		for (int j = 0; j < WeightsMx.size(); j++) {
			if (WeightsMx[i][j] != 0) {
				if (cnt > 1) {
					break;
				}
				else {
					edge.vert2 = j;
					cnt++;
				}
			}		
		}
		if (cnt == 1) {
			edge.vert1 = i;
			edge.weight = WeightsMx[edge.vert1][edge.vert2];
			break;
		}
	}
	prC.push_back(edge.vert2 + 1);
	PrW.push_back(edge.weight);
    tmpWeightsMx[edge.vert1][edge.vert2] = tmpWeightsMx[edge.vert2][edge.vert1] = 0;
	PruferEncode(tmpWeightsMx, prC, PrW);
}

	vector<vector<int>> MyGraph::PruferDecode(vector<int>& prC, vector<int>& PrW) const {
	vector<vector<int>> WMx = vector<vector<int>>(prC.size() + 1, vector<int>(prC.size() + 1, 0));
	vector<bool> isUsed(WMx.size(), false);
	vector<int> qprC, qPrW;
	for (int i = 0; i < prC.size(); i++) {
		qprC.push_back(prC[i] - 1);
		qPrW.push_back(PrW[i]);
	}
	int tmpVert, tmpWeight;
	while (!qprC.empty()) {
		for (int i = 0; i < WMx.size(); i++) {
			if (qprC.end() == std::find(qprC.begin(), qprC.end(), i)) {
				if (isUsed[i] == false) {
					isUsed[i] = true;
					tmpVert = qprC.front(); tmpWeight = qPrW.front();
					WMx[i][tmpVert] = WMx[tmpVert][i] = tmpWeight;
					qprC.erase(qprC.begin()); qPrW.erase(qPrW.begin());
					break;
				}
			}
		}
	}
	return WMx;
}

vector<vector<int>> MyGraph::MakeUnoriented(const vector<vector<int>> WeightsMx) const {
	vector<vector<int>> tmpWMx = WeightsMx;
	for (int i = 0; i < WeightsMx.size(); i++) {
		for (int j = 0; j < i; j++) {
			tmpWMx[i][j] = WeightsMx[j][i];
		}
	}
	return tmpWMx;
}

vector<int> MyGraph::CalcDegrees(vector<vector<int>> WeightsMx) const {
	vector<int> vertDeg(WeightsMx.size(), 0);
	for (int i = 0; i < WeightsMx.size(); i++) {
		for (int j = 0; j < WeightsMx.size(); j++) {
			if (WeightsMx[i][j] != 0) {
				vertDeg[i]++;
			}
		}
	}
	return vertDeg;
}

Euler_Hamilton MyGraph::IfEuler(vector<vector<int>> WeightsMx) const {
	if (VrtxCnt == 2) {
		return Euler_Hamilton::FalseVert;
	}
	vector<vector<int>> unorWeightsMx = MakeUnoriented(WeightsMx);
	vector<int> vertDeg = CalcDegrees(unorWeightsMx);
	Euler_Hamilton result;
	bool isNotEuler = false;
	for (int i = 0; i < vertDeg.size(); i++) {
		if ((vertDeg[i] % 2) == 1) {
			isNotEuler = true;
			if (vertDeg[i] == (WeightsMx.size() - 1)) {
				return Euler_Hamilton::FalseUnmod;
			}
		}
	}
	if (isNotEuler) {
		return Euler_Hamilton::FalseMod;
	}
	return Euler_Hamilton::True;
}

vector<int> MyGraph::EulerCycles(vector<vector<int>> WeightsMx, vector<vector<int>>& modWeightsMx, Euler_Hamilton& IfEulerRes) const {
	IfEulerRes = IfEuler(WeightsMx);
	if (IfEulerRes == Euler_Hamilton::FalseVert) {
		return vector<int>();
	}
	modWeightsMx = MakeUnoriented(WeightsMx);
	vector<int> vertDeg = CalcDegrees(modWeightsMx);
	if (IfEulerRes == Euler_Hamilton::FalseMod) {
		bool IfEuler = false, isChanged = false;
		int vertToConnect = -1;
		std::random_device TmpBase;
		std::mt19937 mersenne(TmpBase());

		while (!IfEuler) {
			isChanged = false;
			for (int i = 0; i < modWeightsMx.size(); i++) {
				if ((vertDeg[i] % 2) == 1) {							
					vertToConnect = -1;
					for (int j = 0; j < modWeightsMx.size(); j++) {
						if ((modWeightsMx[i][j] == 0) && (i != j)) {	
							if (vertToConnect == -1) {					
								if (modWeightsMx.size() % 2 == 0) {
									if (vertDeg[j] != modWeightsMx.size() - 1) {
										vertToConnect = j;
									}
								}
								else {
									vertToConnect = j;
								}
							}
							if ((vertDeg[j] % 2) == 1) { 
								isChanged = true;
								vertDeg[i]++;
								vertDeg[j]++;
								modWeightsMx[i][j] = modWeightsMx[j][i] = mersenne() % (15 - 1) + 1; //TODO: äîáàâèòü ñìåø. âåñà
								break;
							}
						}
					}

					if (!isChanged && (vertToConnect != -1)) {
						isChanged = true;
						vertDeg[i]++;
						vertDeg[vertToConnect]++;
						modWeightsMx[i][vertToConnect] = modWeightsMx[vertToConnect][i] = mersenne() % (15 - 1) + 1; //TODO: äîáàâèòü ñìåø. âåñà
					}

					if (vertToConnect == -1) {
						IfEulerRes = Euler_Hamilton::FalseUnmod;
					}
				}
			}

			if (!isChanged) {
				IfEuler = true;
			}
		}
	}
	if (IfEulerRes == Euler_Hamilton::FalseUnmod) {
		int vertToDisconnect = -1;
		for (int i = 0; i < modWeightsMx.size(); i++) {
			if (vertDeg[i] % 2 == 1) {
				vertToDisconnect = i;
				break;
			}
		}
		for (int i = vertToDisconnect + 1; i < modWeightsMx.size(); i++) {
			if ((vertDeg[i] % 2 == 1) && (modWeightsMx[vertToDisconnect][i])) {
				vertDeg[vertToDisconnect]--;
				vertDeg[i]--;
				modWeightsMx[vertToDisconnect][i] = modWeightsMx[i][vertToDisconnect] = 0;
			}
		}
	}
	vector<int> eulerPath;
	int curVert;
	std::stack<int> vertices;
	vertices.push(0);
	vector<vector<int>> weightsForDec = modWeightsMx;
	while (!vertices.empty()) {
		curVert = vertices.top();
		if (vertDeg[curVert] == 0) {
			vertices.pop();
			eulerPath.push_back(curVert);
		}
		else {
			for (int i = 0; i < VrtxCnt; i++) {
				if (weightsForDec[curVert][i] != 0) {
					vertices.push(i);
					vertDeg[i]--;
					vertDeg[curVert]--;
					weightsForDec[curVert][i] = 0;
					weightsForDec[i][curVert] = 0;
					break;
				}
			}
		}
	}
	return eulerPath;
}

vector<int> MyGraph::Hamilton(vector<vector<int>> WeightsMx, vector<vector<int>>& modWeightsMx, Euler_Hamilton& isHamRes, int& minLen) const {
	if (WeightsMx.size() == 2) {
		isHamRes = Euler_Hamilton::FalseVert;
		return vector<int>();
	}
	modWeightsMx = MakeUnoriented(WeightsMx);
	vector<int> vertDeg;
	bool isHamilton = true, isChanged = false;
	isHamRes = Euler_Hamilton::True;
	int vertToConnect = -1;
	std::random_device TmpBase;
	std::mt19937 mersenne(TmpBase());

	if (modWeightsMx.size() == 3) {
		for (int i = 0; i < WeightsMx.size(); i++) {
			for (int j = 0; j < WeightsMx.size(); j++) {
				if ((i != j) && (modWeightsMx[i][j] == 0)) {
					modWeightsMx[i][j] = modWeightsMx[j][i] = mersenne() % (15 - 1) + 1;
				}
			}
		}
	}
	else {
		vertDeg = CalcDegrees(modWeightsMx);
		for (int i = 0; i < WeightsMx.size(); i++) {
			if (vertDeg[i] < (VrtxCnt / 2)) {
				isHamilton = false;
				isHamRes = Euler_Hamilton::FalseMod;
				break;
			}
		}

		while (!isHamilton) {
			isChanged = false;
			for (int i = 0; i < WeightsMx.size(); i++) {
				vertToConnect = -1;
				if (vertDeg[i] < (VrtxCnt / 2)) {
					for (int j = 0; j < WeightsMx.size(); j++) {
						if ((modWeightsMx[i][j] == 0) && (i != j)) {
							vertToConnect = j;
							if (vertDeg[j] < (VrtxCnt / 2)) {
								isChanged = true;
								vertDeg[i]++;
								vertDeg[j]++;
								modWeightsMx[i][j] = modWeightsMx[j][i] = mersenne() % (15 - 1) + 1;
								break;
							}
						}
					}
					if (!isChanged && (vertToConnect != -1)) {
						isChanged = true;
						vertDeg[i]++;
						modWeightsMx[i][vertToConnect] = modWeightsMx[vertToConnect][i] = mersenne() % (15 - 1) + 1;
					}
				}
			}
			if (!isChanged) {
				isHamilton = true;
			}
		}
	}

	ofstream ofs(OUTPUT_FILE_NAME);
	vector<int> path;
	path.push_back(0);
	vector<int> minPath;
	int len = 0;
	minLen = INT_MAX;
	HamiltonCycles(ofs, modWeightsMx, path, minPath, len, minLen);
	ofs.close();
	return minPath;
}

void MyGraph::HamiltonCycles(ofstream& ofs, vector<vector<int>>& WeightsMx, vector<int>& path, vector<int>& minPath, int& len, int& minLen) const {
	if (path.size() == VrtxCnt) {
		if (WeightsMx[path[path.size() - 1]][0] != 0) {
			len += WeightsMx[path[path.size() - 1]][0];
			path.push_back(0);
			if (len < minLen) {
				minLen = len;
				minPath = path;
			}

			for (int i = 0; i < path.size() - 1; i++) {
				ofs << path[i] + 1 << " -> ";
			}
			ofs << path[path.size() - 1] + 1 << '\t';
			ofs << "Weight: " << len << '\n';

			path.pop_back();
		}
		return;
	}
	for (int i = 0; i < WeightsMx.size(); i++) {
		if (WeightsMx[path[path.size() - 1]][i] != 0) {
			if (path.end() == find(path.begin(), path.end(), i)) {
				int tmpLen = len + WeightsMx[path[path.size() - 1]][i];
				path.push_back(i);
				HamiltonCycles(ofs, WeightsMx, path, minPath, tmpLen, minLen);
				path.pop_back();
			}
		}
	}
}