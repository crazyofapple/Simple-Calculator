#include "Storage.h"
#include "SymbolTable.h"
#include <cmath>
#include <iostream>
#include <cassert>
using namespace std;



Storage::Storage(SymbolTable & tbl)
{
	AddConstants(tbl);
}

void Storage::clear()
{
	cells_.clear();
	inits_.clear();
}

bool Storage::IsInit(uint32_t id) const
{
	return id < cells_.size() && inits_[id];
}

void Storage::AddConstants(SymbolTable & tbl)
{
	cout << "variable list: " << endl;
	uint32_t id = tbl.AddSymbol("e");
	AddValue(id, exp(1.0));
	cout << "e = " << exp(1.0) << endl;
	id = tbl.AddSymbol("pi");
	AddValue(id, acos(-1.0));
	cout << "pi = " << acos(-1.0) << endl << endl;
}

void Storage::AddValue(uint32_t id, double val)
{
	cells_.resize(id + 1);
	cells_[id] = val;
	inits_.resize(id + 1);
	inits_[id] = true;
}

double Storage::GetValue(uint32_t id) const
{
	assert(id < cells_.size());
	return cells_[id];
}

void Storage::SetValue(uint32_t id, double val)
{
	assert(id >= 0);
	if (id < cells_.size()) {
		cells_[id] = val;
		inits_[id] = true;
	} else {
		AddValue(id, val);
	}
}

void Storage::serialize(Serialize & out) const
{
	int size = cells_.size();
	out << size;
	for (int i = 0; i < size; i++) {
		out << cells_[i] << inits_[i];
	}
}

void Storage::deserialize(DeSerialize & in)
{
	cells_.clear();
	inits_.clear();
	int size;
	in >> size;
	cells_.resize(size);
	inits_.resize(size);
	for (int i = 0; i < size; i++) {
		double val; bool tf;
		in >> val >> tf;
		cells_[i] = val;
		inits_[i] = tf;
	}
}
