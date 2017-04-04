#pragma once
#include <string>
#include <fstream>
using namespace std;


class Serialize {
public:
	Serialize() = delete;
	Serialize(const string& filename);
	Serialize& Put(int x);
	Serialize& Put(unsigned int x);
	Serialize& Put(long x);
	Serialize& Put(unsigned long x);
	Serialize& Put(bool x);
	Serialize& Put(const string& x);
	Serialize& Put(double x);

	Serialize& operator<<(int x);
	Serialize& operator<<(unsigned int x);
	Serialize& operator<<(long x);
	Serialize& operator<<(unsigned long x);
	Serialize& operator<<(bool x);
	Serialize& operator<<(const string& x);
	Serialize& operator<<(double x);
private:
	ofstream ofstream_;
};
class DeSerialize {
public:
	DeSerialize() = delete;
	DeSerialize(const string& filename);
	DeSerialize& Get(int& x);
	DeSerialize& Get(unsigned int& x);
	DeSerialize& Get(long& x);
	DeSerialize& Get(unsigned long& x);
	DeSerialize& Get(bool& x);
	DeSerialize& Get(string& x);
	DeSerialize& Get(double& x);

	DeSerialize& operator>>(int& x);
	DeSerialize& operator>>(unsigned int& x);
	DeSerialize& operator>>(long& x);
	DeSerialize& operator>>(unsigned long& x);
	DeSerialize& operator>>(bool& x);
	DeSerialize& operator>>(string& x);
	DeSerialize& operator>>(double& x);
private:
	ifstream ifstream_;
};
class Serializeable {
	virtual void serialize(Serialize& out) const = 0;
	virtual void deserialize(DeSerialize& in) = 0;
};
