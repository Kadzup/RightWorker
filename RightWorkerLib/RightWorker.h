#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <list>

class RightWorker final
{
private:
    std::string m_sBase;
    std::unordered_map<char, std::string> m_Map;
    std::vector<std::pair<char, std::string>> m_Vector;
    std::list<std::string> m_List;

public:
    RightWorker();
    RightWorker(std::string& input);

    ~RightWorker() = default;

    std::string GetBase();
    void SetBase(const std::string& input);

    bool IsValid();

    void Convert();

    std::unordered_map<char, std::string> ToMap();
    std::vector<std::pair<char, std::string>> ToVector();
    std::list<std::string> ToList();

private:
    bool IsOnlyTerminals(const std::string& value);
    bool IsEndWithNonTerminal(const std::string& value);
};
