#pragma once

#include "global.h"
#include "rbtMap.h"

class HashMap {
	vector<Tree*> Info = vector<Tree*>();
	int size = 0;
public:
	~HashMap();
	int GetHashValue(string key);
	int GetSize() const;
	Node* Find(string key, Node*& parent);
	void Print(ostream& os);
	bool Insert(string key);
	bool Delete(string key);
	void Clear();
	void Load(string file = "hash_input.txt");
	void Save(string file = "hash_output.txt");
};