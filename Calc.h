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
	SymbolTable symTbl_;//���㿪ʼ�Ǻ�����������ų�������������
	FunctionTable funTbl_;//����storage_ ���� 0��12 ������
	Storage storage_;// ǰ��Ϊ�գ�13��  ��������������

};

