#pragma once
#include <string>
#include <cstdlib>
using namespace std;
enum EToken {
	TOKEN_ERROR,
	TOKEN_END,
	TOKER_NUMBER,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_MULTIPY,
	TOKEN_DIVIDE,
	TOKEN_LPAREMTHESIS,
	TOKEN_RPAREMTHESIS,
	TOKEN_IDENTIFIER,
	TOKEN_ASSIGN,
	TOKEN_COMMAND,
	TOKEN_MOD
};
class Scanner
{
public:
	Scanner();
	~Scanner();
	explicit Scanner(const std::string& buf);
	void Accept();
	void AcceptPara();
	bool IsFunction() const {
		return token_ == TOKEN_COMMAND;
	}
	bool isEmpty() const {
		return IsEmpty_;
	}
	bool IsDone() const {
		return token_ == TOKEN_END;
	}
	EToken Token() const {
		return token_;
	}
	string Symbol() const {
		return symbol_;
	}
	double Number() const {
		return number_;
	}
private:
	void SkipWhite();
	const string buf_;
	unsigned int curPos_;
	double number_;
	EToken token_;
	string symbol_;
	bool IsEmpty_;
};

