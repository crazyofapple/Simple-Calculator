#pragma once
#include <string>
#include "Parser.h"
class Calc;
class Scanner;
enum COMMAND
{
	COMMAND_ERROR,
	COMMAND_HELP,
	COMMAND_VARAIABLE,
	COMMAND_FUNCTION,
	COMMAND_LOAD,
	COMMAND_SAVE,
	COMMAND_QUIT
};
class CommandParser
{
public:
	CommandParser(Scanner& scanner, Calc& calc);
	STATUS Execute();
private:
	void Help() const;
	void FunList() const;
	void VarList() const;
	STATUS Load(const string& FileName);
	STATUS Save(const string& FileName);
	Scanner& scanner_;
	Calc& calc_;
	COMMAND cmd_;
	string cmdName_;
};

