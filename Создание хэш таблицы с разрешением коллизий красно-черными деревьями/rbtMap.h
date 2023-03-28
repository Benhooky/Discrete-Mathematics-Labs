
#pragma once

#include "global.h"

const string kColors[] = { "чёрный", "красный" };
const string kDirections[] = { "левый", "правый" };

struct Node {
	string* key;
	int val;
	unsigned char Amnt;
	Node* ptrs[2];
	Node(string k = string(), unsigned char c = 1, Node* left = nullptr, Node* right = nullptr, int v = 0);
	~Node();
};
namespace TreeExceptions {
	struct RedViolation {
		RedViolation() {
			cout << "Red violation!\n";
		}
	};
	struct BlackViolation {
		BlackViolation() {
			cout << "Black violation!\n";
		}
	};
	struct BinaryTreeViolation {
		BinaryTreeViolation() {
			cout << "Binary tree violation!\n";
		}
	};
	struct RbtViolation {
		RbtViolation() {
			cout << "Red-black tree violation!\n";
		}
	};
	struct RootIsNull { };
}

class Tree {
	Node* root = nullptr;
	int size = 0;
	int Add(Node* node);
	void PrintNode(ostream& os, Node* node, Node* parent);
	Node* Search(Node* node, string key, Node*& parent);
	Node* RtLeft(Node* node, bool dir);
	Node* RtRight(Node* node, bool dir);
	Node* Recur(Node* node, string key);
	void ClearRecur(Node*& node);
public:
	~Tree();
	int GetSize() const;
	string* GetKey();
	void Print(ostream& os);
	void Save(string file = "tree_output.txt");
	void Load(string file = "tree_input.txt");
	Node* Find(string key, Node*& parent);
	bool Insert(string key);
	bool Delete(string key);
	void Clear();
};

