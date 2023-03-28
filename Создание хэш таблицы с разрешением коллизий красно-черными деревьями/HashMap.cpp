#include "HashMap.h"

HashMap::~HashMap() {
	Clear();
}

 int HashMap::GetHashValue(string key) {
	int sum=0;
	for (auto symbol : key) {
		sum += symbol;
	}
	return abs((sum)/15);
}

int HashMap::GetSize() const {
	return size;
}

Node* HashMap::Find(string key, Node*& parent) {
	if (size != 0) {
		transform(key.begin(), key.end(), key.begin(), tolower);
		int hashVal = GetHashValue(key);
		Node* found = nullptr;
		if (hashVal < Info.size()) {
			if (Info[hashVal] != nullptr) {
				found = Info[hashVal]->Find(key, parent);
			}
		}
		return found;
	}
	return nullptr;
}

void HashMap::Print(ostream& os) {
	if (size != 0) {
		for (unsigned int i = 0; i < Info.size(); i++) {
			if (Info[i] != nullptr) {
				os << "Id " << GetHashValue(*(Info[i]->GetKey())) << " ";
				Info[i]->Print(os);
				os << '\n';
			}
		}
	}
}

bool HashMap::Insert(string key) {
	transform(key.begin(), key.end(), key.begin(), tolower);
	Node *found = nullptr, *parent = nullptr;
	found = Find(key, parent);
	if (found) {
		(found->val)++;
		return false;
	}
	int hashVal = GetHashValue(key);
	if (hashVal >= Info.size()) {
		Info.resize(hashVal + 1, nullptr);
	}
	if (Info[hashVal] == nullptr) {
		Info[hashVal] = new Tree();
	}
	Info[hashVal]->Insert(key);
	size++;
	return true;
}

bool HashMap::Delete(string key) {
	if (size != 0) {
		transform(key.begin(), key.end(), key.begin(), tolower);
		Node* found = nullptr, * parent = nullptr;
		found = Find(key, parent);
		if (found) {
			int hashVal = GetHashValue(key);
			Info[hashVal]->Delete(key);
			if (Info[hashVal]->GetSize() == 0) {
				delete Info[hashVal];
				Info[hashVal] = nullptr;
			}
			size--;
			return true;
		}
	}
	return false;
}

void HashMap::Clear() {
	if (size != 0) {
		for (unsigned int i = 0; i < Info.size(); i++) {
			if (Info[i] != nullptr) {
				Info[i]->Clear();
				delete Info[i];
				Info[i] = nullptr;
			}
		}
		size = 0;
	}
}

void HashMap::Load(string file) {
	std::ifstream ifs(file);
	if (ifs.is_open()) {
		string s;
		boost::basic_regex<char, boost::cpp_regex_traits<char>> expr;
		expr.imbue(std::locale{ "russian" });
		expr = "(\\b[à-ÿÀ-ß¸¨]*\\b)";
		while (ifs >> s) {	
			if (boost::regex_match(s, expr)) {
				Insert(s);
			}
		}
		ifs.close();
	}
}

void HashMap::Save(string file) {
	std::ofstream ofs(file);
	if (ofs.is_open()) {
		Print(ofs);
		ofs.close();
	}
}