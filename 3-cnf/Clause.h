#pragma once
#include <string>
#include <vector>
#include <sstream>
#include "State.h"
using namespace std;

class Clause
{
private:
	int* literals;
	size_t size;

public:
	Clause() 
	{
		literals = NULL;
	}
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

	size_t Size() const
	{
		return size;
	}
	string ToString() const
	{
		std::stringstream ss;

		for (size_t i = 0; i < Size(); i++)
		{
			if (literals[i] < 0)
				ss << "~";
			ss << abs(literals[i]);
			if (i != Size() - 1)
				ss << " v ";
		}

		return ss.str();
	}
	
	State SubstituteTrue(int nr, Clause& c) const
	{
		vector<int> v;

		for (size_t i = 0; i < Size(); i++)
		{
			if (literals[i] == nr)
				return State::ALWAYS;

			if (literals[i] != -nr)
				v.push_back(literals[i]);
		}
		
		if (v.size() == 0)
			return State::NEVER;

		c = Clause(v);

		return State::UNKNOWN;
	}
};
