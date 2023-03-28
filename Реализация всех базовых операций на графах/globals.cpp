#include "globals.h"
using namespace std;
int PascalRngg(double m, double p) {
	random_device TmpBase;
	mt19937 mersenne(TmpBase());
	double q = 1 - p;
	p = pow(p, m);
	double r = mersenne() % (100000 - 1) + 1;
	int z = 0;
	r = (r) / 100000;
	r = r - p;
	while (r >= 0) {
		z++;
		p = p * q * (m - 1 + z) / z;
		r = r - p;
	}
	return int(z + m);
}



void PrintMatrix(const vector<vector<int>> vec) {
	int n = vec.size();
	int m = vec[0].size();
	cout << "    ";
	for (int i = 0; i < vec[0].size() - 1; i++) {
		cout << setw(3) << i + 1 << " ";
	}
	cout << setw(3) << vec[0].size() << '\n';

	for (int i = 0; i < n; i++) {
		cout << setw(3) << i + 1 << " ";
		for (int j = 0; j < m; j++) {
			cout << setw(3) << vec[i][j] << " ";
		}
		cout << '\n';
	}
	cout << '\n';
}

vector<vector<int>> matrixBoolMult(const vector<vector<int>> mxA, const vector<vector<int>> mxB) {
	vector<vector<int>> resMatrix(mxA.size(), vector<int>(mxA.size(), 0));
	vector<int> buf;
	for (int i = 0; i < mxA.size(); i++) {
		for (int j = 0; j < mxA.size(); j++) {
			buf.clear();
			for (int k = 0; k < mxA.size(); k++) {
				buf.push_back(mxA[i][k] && mxB[k][j]);
			}
			resMatrix[i][j] = *std::max_element(buf.begin(), buf.end());
		}
	}
	return resMatrix;
}

vector<vector<int>> matrixAdd(const vector<vector<int>> mxA, const vector<vector<int>> mxB) {
	vector<vector<int>> resMatrix(mxA.size(), vector<int>(mxA.size(), 0));
	for (int i = 0; i < mxA.size(); i++) {
		for (int j = 0; j < mxA.size(); j++) {
			resMatrix[i][j] = mxA[i][j] + mxB[i][j];
		}
	}
	return resMatrix;
}

int factorial(int a) {
	if (a == 1) {
		return 1;
	}
	return a * factorial(a - 1);
}

int MatrixMinor(const vector<vector<int>> mx) {
	if (mx.size() == 1) {
		return mx[0][0];
	}
	if (mx.size() == 2) {
		return mx[0][0] * mx[1][1] - mx[0][1] * mx[1][0];
	}
	int det = 0;
	vector<vector<int>> tmpMx;
	for (int k = 0; k < mx.size(); k++) {
		tmpMx = vector<vector<int>>(mx.size() - 1, vector<int>(mx.size() - 1, 0));
		for (int i = 0; i < mx.size() - 1; i++) {
			for (int j = 0; j < mx.size() - 1; j++) {
				if (i >= k) {
					tmpMx[i][j] = mx[i + 1][j + 1];
				}
				else {
					tmpMx[i][j] = mx[i][j + 1];
				}
			}
		}
		if (k % 2 == 0) {
			det += mx[0][k] * MatrixMinor(tmpMx);
		}
		else {
			det -= mx[0][k] * MatrixMinor(tmpMx);
		}
	}
	return det;
}
