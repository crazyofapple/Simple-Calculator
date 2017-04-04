#pragma once
#include <string>
#include "SymbolTable.h"
#include "Storage.h"
#include "FunctionTable.h"
#include "Serial.h"

class Parser;

class Calc : Serializeable
{
	friend class Parser;
public:
	Calc():funTbl_(symTbl_),storage_(symTbl_) {}
	~Calc();
	virtual void serialize(Serialize& out) const;
	virtual void deserialize(DeSerialize& in);
	void ListFun() const;
	void ListVar() const;
private:
	Storage& GetStorage(){
		return storage_;
	}
	bool isFunction(uint32_t id) const {
		return id < funTbl_.size();
	}
	PtrFun GetFunction(uint32_t id) const {
		return funTbl_.getFunction(id);
	}
	uint32_t FindSymbol(string& str) const;
	uint32_t AddSymbol(string& str);
	SymbolTable symTbl_;//从零开始是函数名，后面才常量名，变量名
	FunctionTable funTbl_;//先于storage_ 构造 0～12 函数名
	Storage storage_;// 前面为空，13～  常量名，变量名

};

