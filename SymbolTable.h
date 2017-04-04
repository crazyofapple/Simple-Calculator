#pragma once
#include <unordered_map>
#include <algorithm>
#include <string>
#include "Serial.h"
#include "Exception.h"
using namespace std;

typedef unsigned int uint32_t;
class SymbolTable:Serializeable
{
public:
	enum { IDNOTFOUND = 0xfffffff };
	SymbolTable():curId_(0) {}
	uint32_t AddSymbol(const string& str);
	uint32_t FindSymbol(const string& str) const;
	void clear();
	void serialize(Serialize& out) const;
	void deserialize(DeSerialize& in);
	const string& GetSymbolName(uint32_t id) const;
	uint32_t GetCurId() const {
		return curId_;
	}
private:
	uint32_t curId_;
	unordered_map<string, uint32_t> dictionary_;
};

