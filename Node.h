#pragma once
#include <cassert>
#include <vector>
#include <memory>
#include "FunctionTable.h"
#include <deque>
using namespace std;
class Storage;
class Node
{
public:
	Node() {};
	virtual ~Node() {};
	virtual double Calc() const = 0;
	virtual bool IsLValue() const {
		return false;
	}
	virtual void Assign(double) {
		assert(!"Assign called incorrectly.");
	}
private:
	Node(const Node&) = delete;
	const Node& operator=(const Node&) = delete;
};

class NumberNode : public Node {
public:
	NumberNode(double number):number_(number){}
	double Calc() const;
private:
	const double number_;
};

class BinaryNode : public Node {
public:
	BinaryNode(shared_ptr<Node>& left, shared_ptr<Node>& right):left_((left)),right_((right)) {}
protected:
	shared_ptr<Node> left_;
	shared_ptr<Node> right_;
};

class AssignNode : public BinaryNode {
public:
	AssignNode(shared_ptr<Node>& left, shared_ptr<Node>& right) :BinaryNode(left, right){
		assert(left->IsLValue());
	}
	double Calc() const;
};

class UnaryNode : public Node {
public:
	UnaryNode(shared_ptr<Node>& child) : child_((child)) {}
protected:
	shared_ptr<Node> child_;
};
class FunctionNode : public UnaryNode {
public:
	FunctionNode(shared_ptr<Node>& child, PtrFun ptrfun) :
		UnaryNode(child), pFun_(ptrfun) {}
	double Calc() const;
private:
	
	PtrFun pFun_;
};
class UMinusNode :public UnaryNode {
public:
	UMinusNode(shared_ptr<Node>& child):UnaryNode(child){}
	double Calc() const;
private:
	UMinusNode(const UMinusNode&) = delete;
};

class MultipleNode :public Node {
public:
	MultipleNode(shared_ptr<Node>& node) {
		AppendChild(node, true);
	}
	void AppendChild(shared_ptr<Node>& node, int positive) {
		childs_.emplace_back((node));
		positives_.push_back(positive);
	}
protected:
	vector<shared_ptr<Node>> childs_;
	deque<int> positives_;
};
class ProductNode : public MultipleNode {
public:
	ProductNode(shared_ptr<Node>& node) :MultipleNode(node) {}
	double Calc() const;
}; 

class SumNode :public MultipleNode {
public:
	SumNode(shared_ptr<Node>& node) :MultipleNode(node) {}
	double Calc() const;
};
class VariableNode : public Node {
public:
	VariableNode(uint32_t id, Storage& storage):id_(id), storage_(storage) {}
	double Calc() const;
	bool IsLValue() const;
	void Assign(double);
private:
	uint32_t id_;
	Storage& storage_;
};