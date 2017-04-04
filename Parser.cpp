#include "Parser.h"
#include "Scanner.h"
#include "Calc.h"
#include "Exception.h"
#include <sstream>
using namespace std;


// -1+5*(2-1)
// tree_ ¼´ SumNode1*  
// SumNode1::childs_ : UMinusNode*(NumberNode*(1)), ProductNode1*
// ProductNode1::childs_: NumberNode*(5), SumNode2*
// SumNode2::childs_ : NumberNode*(2), NumberNode*(-1)

Parser::Parser(Scanner & scanner, Calc & calc):scanner_(scanner), calc_(calc), tree_(nullptr), status_(STATUS::STATUS_OK)
{

}

STATUS Parser::Parse()
{
	tree_ = Expr();
	if (!scanner_.IsDone()) {
		status_ = STATUS_ERROR;
	}
	return status_;
}
// Expr := Term {('+' | '-') Term}
// Expr := Term = Expression
shared_ptr<Node> Parser::Expr()
{
	shared_ptr<Node> node = Term();
	EToken token = scanner_.Token();
	if (token == TOKEN_PLUS || token == TOKEN_MINUS) {
		shared_ptr<MultipleNode> mulNode(new SumNode(node));
		do {
			scanner_.Accept();
			shared_ptr<Node> nextnode = Term();
			mulNode->AppendChild(nextnode, (token == TOKEN_PLUS) ? 1 : 2);
			token = scanner_.Token();
		} while (token == TOKEN_PLUS || token == TOKEN_MINUS);
		node = (mulNode);
	} else if (token == TOKEN_ASSIGN) {
		scanner_.Accept();
		shared_ptr<Node> rightNode = Expr();
		if (node->IsLValue()) {
			node = shared_ptr<Node>(new AssignNode(node, rightNode));
		} else {
			status_ = STATUS::STATUS_ERROR;
			throw SyntaxError("the left-hand of an assignment must be a variable!");
		}
	}
	return node;
}
// Term := Factor {('*' | '/') Factor}
shared_ptr<Node> Parser::Term()
{
	shared_ptr<Node> node = Factor();
	EToken token = scanner_.Token();
	if (token == TOKEN_MULTIPY || token == TOKEN_DIVIDE || token == TOKEN_MOD) {
		shared_ptr<MultipleNode> mulNode(new ProductNode(node));
		do {
			scanner_.Accept();
			shared_ptr<Node> nextNode = Factor();
			int op;
			if (token == TOKEN_MULTIPY) {
				op = 1;
			} else if (token == TOKEN_DIVIDE) {
				op = 2;
			} else if (token == TOKEN_MOD) {
				op = 3;
			}
			mulNode->AppendChild(nextNode, op);
			token = scanner_.Token();
		} while (token == TOKEN_MULTIPY || token == TOKEN_DIVIDE || token == TOKEN_MOD);
		node = (mulNode);
	}
	return node;
}
//factor :=
//number;
//-factor;
//(expression);
//identifier;
//identifier(expression);
shared_ptr<Node> Parser::Factor()
{
	shared_ptr<Node> node;
	EToken token = scanner_.Token();
	if (token == TOKEN_LPAREMTHESIS) {
		scanner_.Accept();
		node = Expr();
		token = scanner_.Token();
		if (token == TOKEN_RPAREMTHESIS) {
			scanner_.Accept();
		} else {
			status_ = STATUS_ERROR;
			throw SyntaxError("missing rparentheis");
		}
	} else if (token == TOKEN_MINUS) {
		scanner_.Accept();
		shared_ptr<Node> tmp = Factor();
		node = shared_ptr<Node>(new UMinusNode(tmp));
	} else if (token == TOKER_NUMBER) {
		scanner_.Accept();
		node = shared_ptr<Node>(new NumberNode(scanner_.Number()));
	} else if (token == TOKEN_IDENTIFIER) {
		scanner_.Accept();
		string symbol = scanner_.Symbol();
		uint32_t id = calc_.FindSymbol(symbol);
		if (scanner_.Token() == TOKEN_LPAREMTHESIS) {
			scanner_.Accept();
			node = Expr();
			if (scanner_.Token() == TOKEN_RPAREMTHESIS) {
				scanner_.Accept();
				if (id != SymbolTable::IDNOTFOUND && calc_.isFunction(id)) {
					node = shared_ptr<Node>(new FunctionNode(node, calc_.GetFunction(id)));
				} else {
					status_ = STATUS::STATUS_ERROR;
					ostringstream oss;
					oss << "Unknown Function \"" << symbol << "\".";
					throw SyntaxError(oss.str().c_str());
				}
			} else {
				status_ = STATUS::STATUS_ERROR;
				throw SyntaxError("missing rparentheis in a function call!");
			}
		} else {
			if (id == SymbolTable::IDNOTFOUND) {
				id = calc_.AddSymbol(symbol);
			}
			node = shared_ptr<Node>(new VariableNode(id, calc_.GetStorage()));
		}
	} else {
		status_ = STATUS::STATUS_ERROR;
		throw SyntaxError("not a valid expression!");
	}
	return node;
}

double Parser::Calculate() const
{
	assert(tree_.get() != nullptr);
	return tree_->Calc();
}
