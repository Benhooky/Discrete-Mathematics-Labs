#include "rbtMap.h"

using namespace TreeExceptions;
	
Node::Node(string k, unsigned char c, Node* left, Node* right, int v) {
	key = new string(k);
	val = v;
	Amnt = c;
	ptrs[0] = left;
	ptrs[1] = right;
}

Node::~Node() {
	delete key;
}

Tree::~Tree() {
	Clear();
}

int Tree::Add(Node* node) {
	if (node == nullptr) {
		return 1;
	}

	int lh, rh;
	Node* ln = node->ptrs[0];
	Node* rn = node->ptrs[1];

	if ((((node) != nullptr) && ((node)->Amnt == 1))) {
		if( (((ln != nullptr) && (ln->Amnt == 1))) || ((rn != nullptr) && (rn->Amnt == 1))) {
			RedViolation();
			return 0;
		}
	}

	lh = Add(ln);
	rh = Add(rn);

	if ((ln != nullptr && *(ln->key) >= *(node->key)) || (rn != nullptr && *(rn->key) <= *(node->key))) {
		 BinaryTreeViolation();
		return 0;
	}

	if (lh != 0 && rh != 0 && lh != rh) {
		BlackViolation();
		return 0;
	}

	if (lh != 0 && rh != 0) {
		return ((node != nullptr) && (node->Amnt == 1)) ? lh : lh + 1;
	}
	else {
		/*throw*/ RbtViolation();
		return 0;
	}
}

Node* Tree::RtLeft(Node* node, bool dir) {
	Node* save = node->ptrs[!dir];

	node->ptrs[!dir] = save->ptrs[dir];
	save->ptrs[dir] = node;

	node->Amnt = 1;
	save->Amnt = 0;
	
	return save;
}

Node* Tree::RtRight(Node* node, bool dir) {
	node->ptrs[!dir] = RtLeft(node->ptrs[!dir], !dir);
	return RtLeft(node, dir);
}

void Tree::PrintNode(ostream& os, Node* node, Node* parent) {
	if (node == nullptr) {
		return;
	}
	os << setw(15) << *(node->key) <<  setw(3) << (node->val)+1 <<  " -- ";
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (node->Amnt == 1) {
		SetConsoleTextAttribute(console, FOREGROUND_RED);
	}
	else {
		SetConsoleTextAttribute(console, FOREGROUND_GREEN);
	}
	os << setw(7) << kColors[node->Amnt];
	SetConsoleTextAttribute(console, TEXT_COLOR_DEFAULT);
	if (node != root) {
		os << " " << setw(6) << kDirections[(parent->ptrs[1] == node)] << " потомок " << *(parent->key);
	}
	else {
		os << " корень дерева";
	}
	os << '\n';
	PrintNode(os, node->ptrs[0], node);
	PrintNode(os, node->ptrs[1], node);
}

int Tree::GetSize() const {
	return size;
}

void Tree::Print(ostream& os) {
	PrintNode(os, root, nullptr);
	Add(root);
}

void Tree::Save(string file) {
	std::ofstream ofs(file);
	if (ofs.is_open()) {
		Print(ofs);
		ofs.close();
	}
}

void Tree::Load(string file) {
	std::ifstream ifs(file);
	if (ifs.is_open()) {
		string s;
		boost::basic_regex<char, boost::cpp_regex_traits<char>> expr;
		expr.imbue(std::locale{"russian"});
		expr = "(\\b[а-€ј-яЄ®]*\\b)";
		while (ifs >> s) {
			if (boost::regex_match(s, expr)) {
				Insert(s);
			}
		}
		ifs.close();
	}
}

Node* Tree::Search(Node* node, string key, Node*& parent) {
	if ((node == nullptr) || (*(node->key) == key)) {
		return node;
	}
	int dir = *(node->key) < key;
	parent = node;
	return Search(node->ptrs[dir], key, parent);
}

Node* Tree::Find(string key, Node*& parent) {
	if (nullptr == root) {
		throw RootIsNull();
	}

	transform(key.begin(), key.end(), key.begin(), tolower);
	return Search(root, key, parent);
}

Node* Tree::Recur(Node* node, string key) {
	if (node == nullptr) {
		node = new Node(key);
		return node;
	}
	bool dir = (*(node->key)) < key;
	node->ptrs[dir] = Recur(node->ptrs[dir], key);
	if ((((node->ptrs[dir]) != nullptr) && ((node->ptrs[dir])->Amnt == 1))) {
		if ((((node->ptrs[!dir]) != nullptr) && ((node->ptrs[!dir])->Amnt == 1))) {
			node->Amnt = 1;
			node->ptrs[0]->Amnt = node->ptrs[1]->Amnt = 0;
		}
		else {
			if ((((node->ptrs[dir]->ptrs[dir]) != nullptr) && ((node->ptrs[dir]->ptrs[dir])->Amnt == 1))) {
				node = RtLeft(node, !dir);
			}
			else if ((((node->ptrs[dir]->ptrs[!dir]) != nullptr) && ((node->ptrs[dir]->ptrs[!dir])->Amnt == 1))) {
				node = RtRight(node, !dir);
			}
		}
	}
	return node;
}

bool Tree::Insert(string key) {
	transform(key.begin(), key.end(), key.begin(), tolower);

	if (root == nullptr) {
		root = new Node(key, 0);
		size++;
		return true;
	}

	Node *parent = nullptr, *found = Find(key, parent);
	if (found) {
		(found->val)++;
		return false;
	}

	root = Recur(root, key);
	root->Amnt = 0;
	size++;
	return true;
}

bool Tree::Delete(string key) {
	if (root == nullptr) {
		return false;
	}
	transform(key.begin(), key.end(), key.begin(), tolower);
	Node falseRoot;
	Node *it = &falseRoot, *parent = nullptr, *gParent = nullptr, *found = nullptr, *tmp = nullptr;
	int dir = 1, tmpDir, last;
	bool res = false;
	it->ptrs[1] = root;
	while (it->ptrs[dir] != nullptr) {
		last = dir;

		gParent = parent;
		parent = it;
		it = it->ptrs[dir];
		dir = *(it->key) < key;
		if (*(it->key) == key) {
			found = it;
		}
		if (!(it != nullptr) && ((it->Amnt == 1)) && !(((it->ptrs[dir]) != nullptr) && (((it->ptrs[dir])->Amnt == 1)))) {
			if ((((it->ptrs[!dir]) != nullptr) && ((it->ptrs[!dir])->Amnt == 1))) {
				parent = parent->ptrs[last] = RtLeft(it, dir);
			}
			else if (!(((it->ptrs[!dir]) != nullptr) && ((it->ptrs[!dir])->Amnt == 1))) {
				tmp = parent->ptrs[!last];

				if (tmp != nullptr) {
					if (!(((tmp->ptrs[!last]) != nullptr) && ((tmp->ptrs[!last])->Amnt == 1)) && !(((it->ptrs[!last]) != nullptr) && ((it->ptrs[!last])->Amnt == 1))) {
						parent->Amnt = 0;
						tmp->Amnt = 1;
						it->Amnt = 1;
					}
					else {
						tmpDir = (gParent->ptrs[1] == parent);

						if ((((tmp->ptrs[last]) != nullptr) && ((tmp->ptrs[last])->Amnt == 1))) {
							gParent->ptrs[tmpDir] = RtRight(parent, last);
						}
						else if ((((tmp->ptrs[!last]) != nullptr) && ((tmp->ptrs[!last])->Amnt == 1))) {
							gParent->ptrs[tmpDir] = RtLeft(parent, last);
						}

						it->Amnt = gParent->ptrs[tmpDir]->Amnt = 1;
						gParent->ptrs[tmpDir]->ptrs[0]->Amnt = 0;
						gParent->ptrs[tmpDir]->ptrs[1]->Amnt = 0;
					}
				}
			}
		}
	}
	if (found) {
		std::swap(found->key, it->key);
		parent->ptrs[parent->ptrs[1] == it] = it->ptrs[it->ptrs[0] == nullptr];
		delete it;
		size--;
		res = true;
	}
	root = falseRoot.ptrs[1];
	if (root != nullptr) {
		root->Amnt = 0;
	}
	return res;
}

void Tree::ClearRecur(Node*& node) {
	if (node == nullptr) {
		return;
	}
	ClearRecur(node->ptrs[0]);
	ClearRecur(node->ptrs[1]);
	delete node;
	node = nullptr;
	size--;
}

void Tree::Clear() {
	ClearRecur(root);
}

string* Tree::GetKey() {
	return root->key;
}