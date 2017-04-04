#include "CommandParser.h"
#include "Calc.h"
#include "Scanner.h"
using namespace std;


CommandParser::CommandParser(Scanner & scanner, Calc & calc):scanner_(scanner), calc_(calc)
{
	assert(scanner_.IsFunction());
	scanner_.Accept();
	cmdName_ = scanner_.Symbol();
	switch (tolower(cmdName_[0]))
	{
	case 'h':
		cmd_ = COMMAND_HELP;
		break;
	case 'q':
		cmd_ = COMMAND_QUIT;
		break;
	case 'l':
		cmd_ = COMMAND_LOAD;
		break;
	case 's':
		cmd_ = COMMAND_SAVE;
		break;
	case 'v':
		cmd_ = COMMAND_VARAIABLE;
		break;
	case 'f':
		cmd_ = COMMAND_FUNCTION;
		break;
	default:
		cmd_ = COMMAND_ERROR;
		break;
	}
}

STATUS CommandParser::Execute()
{
	STATUS status = STATUS_OK;
	scanner_.AcceptPara();
	string FileName;
	switch (cmd_)
	{
	case COMMAND_ERROR:
		cout << "Unknown command: " << "\"" << cmdName_ << "\"." << endl;
		status = STATUS_ERROR;
		break;
	case COMMAND_HELP:
		Help();
		break;
	case COMMAND_VARAIABLE:
		VarList();
		break;
	case COMMAND_FUNCTION:
		FunList();
		break;
	case COMMAND_LOAD:
		FileName = scanner_.Symbol();
		status = Load(FileName);
		break;
	case COMMAND_SAVE:
		FileName = scanner_.Symbol();
		status = Save(FileName);
		break;
	case COMMAND_QUIT:
		cout << "Good Bye!" << endl;
		status = STATUS_QUIT;
		break;
	default:
		cout << "Unknown command: " << "\"" << cmdName_ << "\"." << endl;
		status = STATUS_ERROR;
		break;
	}
	return status;
	return status;
}

void CommandParser::Help() const {
	cout << "Recognized Command: " << endl;
	cout << "Hint: The command's first alpha was effective also" << endl;
	cout << "!help" << endl;
	cout << "!var" << endl;
	cout << "!fun" << endl;
	cout << "!load filename" << endl;
	cout << "!save filename" << endl;
}

void CommandParser::FunList() const
{
	cout << "Function List: " << endl;
	calc_.ListFun();
}

void CommandParser::VarList() const
{
	cout << "Variable List" << endl;
	calc_.ListVar();
}

STATUS CommandParser::Load(const string & FileName)
{
	cout << "Load File " << "\"" << FileName << "\"." << endl;
	STATUS status = STATUS_OK;
	try {
		DeSerialize in(FileName);
		calc_.deserialize(in);
	}
	catch (Exception& e) {
		cout << "Load Error: " << e.what() << endl;
		status = STATUS_ERROR;
	}
 	return status;
}

STATUS CommandParser::Save(const string & FileName)
{
	cout << "Save File " << "\"" << FileName << "\"." << endl;
	STATUS status = STATUS_OK;
	try {
		Serialize out(FileName);
		calc_.serialize(out);
	}
	catch (Exception& e) {
		cout << "Save Error: " << e.what() << endl;
		status = STATUS_ERROR;
	}
	return status;
}
