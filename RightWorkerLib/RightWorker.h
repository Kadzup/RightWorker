#pragma once

#ifdef RIGHT_WORKER_EXPORTS
#define RIGHT_WORKER_API __declspec(dllexport)
#else
#define RIGHT_WORKER_API __declspec(dllimport)
#endif
#include <string>
#include <map>
#include <vector>
#include <list>

class RightWorker final
{
private:
    std::string mBase;
    std::map<char, std::string> mMap;
    std::vector<std::pair<char, std::string>> mVector;
    std::list<std::string> mList;

public:
    RightWorker(std::string& input);

    ~RightWorker() = default;

    std::string GetBase();

    bool IsValid();

    void Convert();

    std::map<char, std::string> ToMap();
    std::vector<std::pair<char, std::string>> ToVector();
    std::list<std::string> ToList();

private:
    bool IsOnlyTerminals(const std::string& value);
    bool IsEndWithNonTerminal(const std::string& value);
};