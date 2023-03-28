#pragma once

#include "globals.h"


struct McfRetVals {
	vector<vector<int>> Paths;
	vector<int> Flows;
	vector<int> CostForPath;
	vector<vector<int>> ModCostMx;
	vector<vector<int>> ModFlowMx;
};

struct Edge {
	int vert1;
	int vert2;
	int weight;

	Edge(int v1 = 999, int v2 = 999, int w = 999) : vert1(v1), vert2(v2), weight(w) { }

	bool operator > (const Edge& e) const {
		return this->weight > e.weight;
	}

	bool operator < (const Edge& e) const {
		return this->weight < e.weight;
	}
};

enum class SrtOrLng {
	Srt = 0,
	Lng
};

enum class WeightsType {
	Pos,
	Mx,
	ModPos,
	ModMx
};

enum class Euler_Hamilton {
	FalseVert,
	FalseUnmod,
	FalseMod,
	True
};

class MyGraph {
private:
	int VrtxCnt;
	vector<vector<int>> AdjMatrix;
	vector<vector<int>> PosWMatrix;
	vector<vector<int>> MxdWMatrix;
	vector<vector<int>> ModiPosWMatrix;
	vector<vector<int>> ModiMxdWMatrix;
	vector<vector<int>> RchMatrix;
	vector<vector<int>> MxFlowMatrix;
	vector<int> Prepare() const;
	void MixWeights();
	void ModifyWeights(vector<vector<int>>& WeightsMatrix, vector<vector<int>>& modified);
	void GenRchMatrix();
	void GenMxFlowMatrix();
	vector<vector<int>> AddFictVert() const;
	bool bfs(vector<vector<int>> graphMx, int v1, int v2, vector<int>* path = nullptr, int* Counter = nullptr) const;
	bool bfs_FoTmpBaseFulkerson(vector<vector<int>> residual, int source, int sink, vector<int>& path) const;
	priority_queue<Edge, vector<Edge>, std::greater<Edge>> SortEdges(vector<vector<int>> WeightsMx) const;
	vector<vector<int>> MakeUnoriented(const vector<vector<int>> WeightsMx) const;
	vector<int> CalcDegrees(vector<vector<int>> WeightsMx) const;
	vector<vector<int>> ShimbellMult(const vector<vector<int>> mxA, const vector<vector<int>> mxB, SrtOrLng mode) const;
public:
	MyGraph(int n);
	void AssignWeights();
	int GetsecondCount() const;
	int foTmpBaseFulkerson(int source, int sink) const;
	int MinCostFlow(int source, int sink, int flow, McfRetVals& retVals) const;
	int AmountMinTrees() const;
	void PruferEncode(vector<vector<int>>& WeightsMx, vector<int>& prC, vector<int>& PrW) const;
	vector<vector<int>> GetAdjMatrix() const;
	vector<vector<int>> GetWMatrix(WeightsType type) const;
	vector<vector<int>> GetRchMatrix() const;
	vector<vector<int>> GetMxFlowMatrix() const;
	vector<vector<int>> Shimbell(int cnt, SrtOrLng mode) const;
	vector<int> Dijkstra(int InVert, int& Counter) const;
	vector<vector<int>> Revive(int InVert, const vector<int>& distances, const vector<vector<int>> WMx) const;
	vector<int> BellmanFoTmpBase(int InVert, vector<vector<int>> wieghtsMx, int& Counter) const;
	vector<vector<int>> FloydWarshall(int& Counter,char check) const;
	vector<vector<int>> Kruskal(vector<vector<int>> WeightsMx, int* Counter = nullptr, int* sum = nullptr) const;
	vector<vector<int>> Prim(vector<vector<int>> WeightsMx, int* Counter = nullptr, int* sum = nullptr) const;
	vector<vector<int>> GenKirchhoffMatrix() const;
	vector<vector<int>> PruferDecode(vector<int>& prC, vector<int>& PrW) const;
	vector<int> EulerCycles(vector<vector<int>> WeightsMx, vector<vector<int>>& modWeightsMx, Euler_Hamilton& IfEulerRes) const;
	vector<int> Hamilton(vector<vector<int>> WeightsMx, vector<vector<int>>& modWeightsMx, Euler_Hamilton& isHamRes, int& minLen) const;
	Euler_Hamilton IfEuler(vector<vector<int>> WeightsMx) const;
	void HamiltonCycles(ofstream& ofs, vector<vector<int>>& WeightsMx, vector<int>& path, vector<int>& minPath, int& len, int& minLen) const;

};

