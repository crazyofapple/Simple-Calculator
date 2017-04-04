#include "FunctionTable.h"
#include <cmath>
#include <cassert>
#include "FunctionTable.h"
#include "SymbolTable.h"
using namespace std;

struct FunctionEntry{
	PtrFun ptrfun;
	char* name;
};

FunctionEntry functionTable[] = {
	log,        "log",
	log10,      "log10",
	exp,        "exp",
	sqrt,       "sqrt",
	sin,        "sin",
	cos,        "cos",
	tan,        "tan",
	sinh,       "sinh",
	cosh,       "cosh",
	tanh,       "tanh",
	asin,       "asin",
	acos,       "acos",
	atan,       "atan",
};
FunctionTable::~FunctionTable()
{
	delete[] ptrFun_;
}

FunctionTable::FunctionTable(SymbolTable & tbl):size_(sizeof(functionTable)/sizeof(functionTable[0]))
{
	Init(tbl);
}

void FunctionTable::Init(SymbolTable & tbl)
{
	cout << "function list: " << endl;
	ptrFun_ = new PtrFun[size_];
	for (uint32_t i = 0; i < size_; i++) {
		ptrFun_[i] = functionTable[i].ptrfun;
		uint32_t j = tbl.AddSymbol(functionTable[i].name);
		assert(i == j);
		cout << functionTable[i].name << endl;
	}
	cout << endl;
}