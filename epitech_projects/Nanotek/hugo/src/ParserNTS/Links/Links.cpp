/*
** EPITECH PROJECT, 2023
** Links.cpp
** File description:
** Links
*/

#include "Links.hpp"

Links::Links() : _isLinks(false) {}

Links::~Links() {}

void Links::ReadLinks(const std::vector<std::string> &_ntsContent, const std::vector<std::string> &chipsetsNames) {
    bool found = false;
    for (const auto& line : _ntsContent) {
        if (found) {
            if ((line).find(" ") != (line).rfind(" ") || (line).find("\t") != (line).rfind("\t"))
                throw Exception("Invalid separator in line: " + (line));
            if (line.find(" ") != std::string::npos) {
                std::string first = line.substr(0, line.find(" "));
                std::string last = line.substr(line.find(" ") + 1);
                this->setLinksMap(first, last, chipsetsNames);
            } else if (line.find("\t") != std::string::npos) {
                std::string first = line.substr(0, line.find("\t"));
                std::string last = line.substr(line.find("\t") + 1);
                this->setLinksMap(first, last, chipsetsNames);
            }
        } else if (line == ".links:")
        found = true;
    }
    for (const auto &link : _linksMap)
        std::cout << link.first.first << ":" << link.first.second << "--" << link.second.first << ":" << link.second.second << std::endl;
}

void Links::setLinksMap(const std::string &first, const std::string &last, const std::vector<std::string> &chipsetsNames) {
    if (first.find(":") == std::string::npos || last.find(":") == std::string::npos)
      throw Exception("Error: first or last does not contain ':'");
    std::string firstKey = first.substr(0, first.find(":"));
    std::string firstValue = first.substr(first.find(":") + 1);
    std::string lastKey = last.substr(0, last.find(":"));
    std::string lastValue = last.substr(last.find(":") + 1);
    if (std::find(chipsetsNames.begin(), chipsetsNames.end(), firstKey) == chipsetsNames.end() ||
        std::find(chipsetsNames.begin(), chipsetsNames.end(), lastKey) == chipsetsNames.end())
        throw Exception("Error: firstKey or lastKey not found in chipsetsNames");
    this->_linksMap[{firstKey, firstValue}] = {lastKey, lastValue};
}

const std::map<std::pair<std::string, std::string>, std::pair<std::string, std::string>> &Links::getLinksMap() const {
    return (this->_linksMap);
}

std::pair<std::pair<std::string, std::string>, std::pair<std::string, std::string>> Links::getLinksMapAt(const int &idx) const {
    if (idx >= (int)this->_linksMap.size() || idx < 0)
        throw Exception("Error: Index out of bounds");
    auto it = this->_linksMap.begin();
    std::advance(it, idx);
    return (*it);
}
