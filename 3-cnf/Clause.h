#pragma once
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class Clause
{
private:
	int* literals = NULL;
	size_t size;

public:
	Clause() {}
	Clause(const vector<int>& v)
	{
		if (v.size() < 1 || v.size() > 3)
		{
			string message = "Cant create clause with " + std::to_string( v.size()) +  "arguments";
			throw std::invalid_argument(message);
		}

		size = v.size();
		literals = new int[size];
		for (size_t i = 0; i < size; i++)
			literals[i] = v[i];
	}
	Clause(const Clause &c)
	{
		size = c.size;
		literals = new int[size];
		for (size_t i = 0; i < size; i++)
			literals[i] = c[i];
	}
	~Clause()
	{
		delete literals;
	}

	int operator[](size_t nr) const { return literals[nr]; }
	Clause& operator=(const Clause& c) 
	{
		if (this != &c) {
			size = c.size;
			literals = new int[size];
			for (size_t i = 0; i < size; i++)
				literals[i] = c[i];
		}
		return *this;
	}

	size_t GetSize() const
	{
		return size;
	}
	string ToString() const
	{
		std::stringstream ss;

		for (size_t i = 0; i < GetSize(); i++)
		{
			if (literals[i] < 0)
				ss << "~";
			ss << abs(literals[i]);
			if (i != GetSize() - 1)
				ss << " v ";
		}

		return ss.str();
	}
};
