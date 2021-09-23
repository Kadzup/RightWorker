#include "pch.h"
#include "RightWorker.h"

#include <sstream>
#include <iostream>
#include <functional>

// third party code
namespace
{
	// trim from start
	inline std::string& ltrim(std::string& s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(),
			std::not1(std::ptr_fun<int, int>(std::isspace))));
		return s;
	}

	// trim from end
	inline std::string& rtrim(std::string& s) {
		s.erase(std::find_if(s.rbegin(), s.rend(),
			std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
		return s;
	}

	// trim from both ends
	inline std::string& trim(std::string& s) {
		return ltrim(rtrim(s));
	}
}

RightWorker::RightWorker(){}

void RightWorker::SetBase(const std::string& input)
{
	this->mBase = input;
}

RightWorker::RightWorker(std::string& input)
{
	this->mBase = input;

	Convert();
}

std::string RightWorker::GetBase()
{
	return mBase;
}


void RightWorker::Convert()
{
	// split base
	std::vector<std::string> lines;
	std::istringstream f(mBase);
	std::string s;

	while (std::getline(f, s, '\n')) {
		lines.push_back(s);
	}

	// create map
	for (const std::string& line : lines)
	{
		size_t index = line.find_first_of(':');

		if (index == std::string::npos)
		{
			std::cout << "Invalid input " + line + "\n";
		}
		else
		{
			std::string n = line.substr(0, index);
			std::string t = line.substr(index + 1, line.size() - 1);

			n = trim(n);
			t = trim(t);

			mMap[n[0]] = t;
		}
	}

	// create vector
	for (auto mapIt = mMap.begin(); mapIt != mMap.end(); ++mapIt)
	{
		// if no '|'
		if (mapIt->second.find_first_of('|') == std::string::npos)
		{
			mVector.push_back({ mapIt->first, mapIt->second });
		}
		else
		{
			std::vector<std::string> parts;

			std::istringstream p(mapIt->second);
			std::string temp;

			while (std::getline(p, temp, '|')) {
				temp = trim(temp);
				parts.push_back(temp);
			}

			for (const std::string& part : parts)
			{
				mVector.push_back({ mapIt->first, part });
			}
		}
	}

	// create list
	for (auto vecIt = mVector.begin(); vecIt != mVector.end(); ++vecIt)
	{
		// in case that we have std::format only in c++ 20, and "[" + char will give us not an concatenates, we should concatenates them all in diff ways 
		std::string formatedLine;
		formatedLine += "[";
		formatedLine += vecIt->first;
		formatedLine += "] -> " + vecIt->second;
		mList.push_back(formatedLine);
	}
}

std::map<char, std::string> RightWorker::ToMap()
{
	return mMap;
}

std::vector<std::pair<char, std::string>> RightWorker::ToVector()
{
	return mVector;
}

std::list<std::string> RightWorker::ToList()
{
	return mList;
}

bool RightWorker::IsValid()
{
	bool isValid = true;
	// (Wikipedia)
	//  A right-regular grammar (also called right-linear grammar) is a formal grammar (N, Σ, P, S) in which all production rules in P are of one of the following forms:
	//	A -> a
	//	A -> aB
	//	A -> ε
	// valid if all non-terminals in vector of pairs have:
	for (auto it = mVector.begin(); it != mVector.end(); ++it)
	{
		std::string value = it->second;

		// only terminals
		if (IsOnlyTerminals(value))
		{
			continue;
		}
		// OR
		// terminals and end with non-terminals
		else if (IsEndWithNonTerminal(value))
		{
			continue;
		}
		// OR
		// empty (e)
		else if (trim(value) == "e")
		{
			continue;
		}
		else
		{
			isValid = false;
			break;
		}
	}

	return isValid;
}

bool RightWorker::IsOnlyTerminals(const std::string& value)
{
	for (char c : value)
	{
		if (!islower(c))
		{
			return false;
		}
	}
	return true;
}

bool RightWorker::IsEndWithNonTerminal(const std::string& value)
{
	return isupper(value[value.length() - 1]);
}

