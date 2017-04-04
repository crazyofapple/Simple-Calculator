#pragma once
#include "SymbolTable.h"
#include <iostream>
typedef double(*PtrFun)(double);
class SymbolTable;
class FunctionTable
{
public:
	explicit FunctionTable(SymbolTable& tbl);
	~FunctionTable();
	void Init(SymbolTable& tbl);
	uint32_t size() const {
		return size_;
	}
	PtrFun getFunction(uint32_t id) const {
		return ptrFun_[id];
	}
private:
	PtrFun* ptrFun_;
	uint32_t size_;
};

