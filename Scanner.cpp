#include "Scanner.h"
using namespace std;

Scanner::Scanner()
{
}


Scanner::~Scanner()
{
}

Scanner::Scanner(const std::string & buf):buf_(buf), curPos_(0)
{
	Accept();
	IsEmpty_ = (token_ == TOKEN_END);
}

void Scanner::Accept()
{
	SkipWhite();
	switch (buf_[curPos_])
	{
	case '!':
		token_ = TOKEN_COMMAND;
		curPos_++;
		break;
	case '+':
		token_ = TOKEN_PLUS;
		curPos_++;
		break;
	case '-':
		token_ = TOKEN_MINUS;
		curPos_++;
		break;
	case '*':
		token_ = TOKEN_MULTIPY;
		curPos_++;
		break;
	case '/':
		token_ = TOKEN_DIVIDE;
		curPos_++;
		break;
	case '(':
		token_ = TOKEN_LPAREMTHESIS;
		curPos_++;
		break;
	case ')':
		token_ = TOKEN_RPAREMTHESIS;
		curPos_++;
		break;
	case '=':
		token_ = TOKEN_ASSIGN;
		curPos_++;
		break;
	case '%':
		token_ = TOKEN_MOD;
		curPos_++;
		break;
	case '0':case '1': case '2':case '3':case '4':
	case '5':case '6': case '7': case '8': case '9':case '.':
		token_ = TOKER_NUMBER;
		char* p;
		number_ = strtod(&buf_[curPos_], &p);
		curPos_ = p - &buf_[0];
		break;
	case '\0':
		token_ = TOKEN_END;
		curPos_++;
		break;
	default:
		if (isalpha(buf_[curPos_]) || buf_[curPos_] == '_') {
			token_ = TOKEN_IDENTIFIER;
			symbol_.erase();
			char ch = buf_[curPos_];
			do {
				symbol_ += ch;
				ch = buf_[++curPos_];
			} while (isalnum(ch) || ch == '_');
		} else {
			token_ = TOKEN_ERROR;
		}
		break;
	}
	
}

void Scanner::AcceptPara()
{
	while (buf_[curPos_] == ' ' || buf_[curPos_] == '\t') {
		curPos_++;
	}
	symbol_.erase();
	char ch = buf_[curPos_];
	while (isalnum(ch) || ch == '_' || ch == '.') {
		symbol_ += ch;
		ch = buf_[++curPos_];
	}
}

void Scanner::SkipWhite()
{
	while (isspace(buf_[curPos_])) curPos_++;
}


