#pragma once
#include "vcruntime_exception.h"
#include <string>
using namespace std;

class Exception :
	public std::exception
{
public:
	virtual ~Exception() throw() {}
	explicit Exception(const char* message) :message_(message) {}
	explicit Exception(string& message):message_(message.c_str()){}
	const char* what() const {
		return message_.c_str();
	}
private:
	string message_;
};

class SyntaxError : public Exception {
public:
	explicit SyntaxError(const char* message): Exception(message) {}
	virtual ~SyntaxError() throw() {}
};

