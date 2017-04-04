#include "SymbolTable.h"
using namespace std;

uint32_t SymbolTable::AddSymbol(const string & str)
{
	dictionary_[str] = curId_;
	return curId_++;
}

uint32_t SymbolTable::FindSymbol(const string & str) const
{
	auto it = dictionary_.find(str);
	if (it != dictionary_.end()) {
		return it->second;
	} else {
		return IDNOTFOUND;
	}
}

void SymbolTable::clear()
{
	dictionary_.clear();
	curId_ = 0;
}

void SymbolTable::serialize(Serialize & out) const
{
	out << dictionary_.size();
	for (auto it = dictionary_.begin(); it != dictionary_.end(); it++) {
		out << it->first << it->second;
	}
	out << curId_;
}

void SymbolTable::deserialize(DeSerialize & in)
{
	dictionary_.clear();
	int size;
	in >> size;
	for (int i = 0; i < size; i++) {
		string name;
		uint32_t id;
		in >> name >> id;
		dictionary_[name] = id;
	}
	in >> curId_;
}
struct check_x {
public:
	check_x(int x) : x_(x) {}
	bool operator() (const pair<string, int>& v) const {
		return v.second == x_;
	}
private:
	int x_;
};
const string & SymbolTable::GetSymbolName(uint32_t id) const
{
	auto it = find_if(dictionary_.begin(), dictionary_.end(), check_x(id));
	if (it == dictionary_.end()) {
		throw Exception("Internal Error: missing entry in symbol table.");
	}
	return it->first;
}
