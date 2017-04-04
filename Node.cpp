#include "Node.h"
#include <cmath>
#include <cassert>
#include <iostream>
#include "Storage.h"
using namespace std;

double NumberNode::Calc() const
{
	return number_;
}

double AssignNode::Calc() const
{
	double val = 0.0;
	val = right_->Calc();
	left_->Assign(val);
	return val;
}

double FunctionNode::Calc() const
{
	return (*pFun_)(child_->Calc());
}

double UMinusNode::Calc() const
{
	double val = child_->Calc();
	if (fabs(val) < 1e-5) return val;
	return -val;
}

double ProductNode::Calc() const
{
	double result = 1.0;
	auto cit = childs_.begin();
	auto pit = positives_.begin();
	for (; cit != childs_.end(); cit++, pit++) {
		assert(pit != positives_.end());
		double val = (*cit)->Calc();
		if (*pit == 1) {
			result *= val;
		} else if (*pit == 2) {
			if (fabs(val) > 1e-5) {
				result /= val;
			} else {
				cout << "divide by zero!" << endl;
				return HUGE_VAL;
			}
		} else if(*pit == 3) {
			if (fabs(val) > 1e-5) {
				result = ((result / val) - floor(result / val))*val;
			} else {
				cout << "mod by zero!" << endl;
				return HUGE_VAL;
			}
		}
	}
	assert(pit == positives_.end());
	return result;
}

double SumNode::Calc() const
{
	double result = 0.0;
	auto cit = childs_.begin();
	auto pit = positives_.begin();
	for (; cit != childs_.end(); cit++, pit++) {
		assert(pit != positives_.end());
		double val = (*cit)->Calc();
		if (*pit == 1) {
			result += val;
		} else if (*pit == 2){
			result -= val;
		} 
	}
	assert(pit == positives_.end());
	return result;
}

double VariableNode::Calc() const
{
	double val = 0.0;
	if (storage_.IsInit(id_)) {
		val = storage_.GetValue(id_);
	} else {
		cout << "use of uninitialized variable" << endl;
	}
	return val;
}

bool VariableNode::IsLValue() const
{
	return true;
}

void VariableNode::Assign(double val)
{
	storage_.SetValue(id_, val);
}
