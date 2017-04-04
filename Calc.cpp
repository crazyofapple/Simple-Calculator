#include "Calc.h"
#include <iostream>
using namespace std;

Calc::~Calc()
{
}

void Calc::serialize(Serialize & out) const
{
	symTbl_.serialize(out);
	storage_.serialize(out);
}

void Calc::deserialize(DeSerialize & in)
{
	symTbl_.deserialize(in);
	storage_.deserialize(in);
}

void Calc::ListFun() const
{
	for (uint32_t i = 0; i < funTbl_.size(); i++) {
		cout << symTbl_.GetSymbolName(i) << endl;
	}
}

void Calc::ListVar() const
{
	for (uint32_t i = funTbl_.size(); i < symTbl_.GetCurId(); i++) {
		string name = symTbl_.GetSymbolName(i);
		double val = 0.0;
		if (storage_.IsInit(i)) {
			val = storage_.GetValue(i);
		}
		cout << name << " = " << val << endl;
	}
}

uint32_t Calc::FindSymbol(string & str) const
{
	return symTbl_.FindSymbol(str);
}

uint32_t Calc::AddSymbol(string & str)
{
	return symTbl_.AddSymbol(str);
}
