#pragma once
#include <vector>
#include <deque>
#include "Serial.h"
class SymbolTable;
class Storage:Serializeable
{
public:
	Storage(SymbolTable& tbl);
	void clear();
	bool IsInit(uint32_t id) const;
	void AddConstants(SymbolTable& tbl);
	void AddValue(uint32_t id, double val);
	double GetValue(uint32_t) const;
	void SetValue(uint32_t id, double val);
	void serialize(Serialize& out) const;
	void deserialize(DeSerialize& in);
private:
	vector<double> cells_;
	deque<bool> inits_;
};

