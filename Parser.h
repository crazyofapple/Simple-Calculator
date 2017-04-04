#pragma once
#include <string>
#include <memory>
#include "Node.h"
enum STATUS {
	STATUS_OK,
	STATUS_ERROR,
	STATUS_QUIT,
};

class Scanner;
class Calc;

class Parser
{
public:
	explicit Parser(Scanner& scanner, Calc& calc);
	STATUS Parse();
	shared_ptr<Node> Expr();
	shared_ptr<Node> Term();
	shared_ptr<Node> Factor();
	double Calculate() const;
private:
	Scanner& scanner_;
	Calc& calc_;
	STATUS status_;
	shared_ptr<Node> tree_;
};

