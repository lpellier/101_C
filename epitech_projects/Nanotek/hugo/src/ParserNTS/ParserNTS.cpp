/*
** EPITECH PROJECT, 2023
** ParserNTS.cpp
** File description:
** ParserNTS
*/

#include "ParserNTS.hpp"

ParserNTS::ParserNTS(const std::string &path) : _pathNTS(path) {}

ParserNTS::~ParserNTS() {}

void ParserNTS::isChipsetsLinks() const {
    bool chipsets = false;
    bool links = false;
    for (const auto &line : _ntsContent) {
        if (line.find(".chipsets:") == 0)
            chipsets = true;
        if (line.find(".links:") == 0)
            links = true;
    }
    (chipsets == false) ? (throw Exception("Error: No '.chipsets:' find in file")) :
    (links == false) ? (throw Exception("Error: No '.links:' find in file")) : 0;
}

void ParserNTS::GetFile() {
    std::ifstream file(_pathNTS);
    std::string line;

    if (this->_pathNTS.substr(this->_pathNTS.length() - 4, 4) != ".nts")
        throw Exception("Invalid file type: " + this->_pathNTS);
    if (!file.is_open())
        throw Exception("Failed to open file: " + this->_pathNTS);
    while (std::getline(file, line))
        this->_ntsContent.push_back(line);
    file.close();
    isChipsetsLinks();
    this->_chipsets.ReadChipsets(this->_ntsContent);
    this->_links.ReadLinks(this->_ntsContent, this->_chipsets.getChipsetsNames());
}

std::vector<std::string> ParserNTS::GetNTSContent() const {
    return (this->_ntsContent);
}
