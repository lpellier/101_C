/*
** EPITECH PROJECT, 2023
** Chipsets.cpp
** File description:
** Chipsets
*/

#include "Chipsets.hpp"

Chipsets::Chipsets() : _isChipsets(false) {}

Chipsets::~Chipsets() {}

void Chipsets::ReadChipsets(const std::vector<std::string> &_ntsContent) {
    for (auto line_it = _ntsContent.begin(); line_it != _ntsContent.end(); ++line_it) {
        const auto& line = *line_it;
        if (line.find(".chipsets:") == 0)
            for (line_it++ ; line_it->find(".links:") != 0; ++line_it) {
                if ((*line_it).find(" ") != (*line_it).rfind(" ") || (*line_it).find("\t") != (*line_it).rfind("\t"))
                    throw Exception("Invalid separator in line: " + (*line_it));
                if (line_it->find(" ") != std::string::npos) {
                    std::string type = line_it->substr(0, line_it->find(" "));
                    std::string name = line_it->substr(line_it->find(" ") + 1);
                    this->setChipsetsMap(type, name);
                } else if (line_it->find("\t") != std::string::npos) {
                    std::string type = line_it->substr(0, line_it->find("\t"));
                    std::string name = line_it->substr(line_it->find("\t") + 1);
                    this->setChipsetsMap(type, name);
                }
            }
    }
    for (const auto &chipset : this->_chipsetsMap)
        std::cout << chipset.first << " " << chipset.second <<std::endl;
}

void Chipsets::setChipsetsMap(const std::string &type, const std::string &name) {
    if (std::find(this->_validTypes.begin(), this->_validTypes.end(), type) != this->_validTypes.end())
        this->_chipsetsTypes.push_back(type);
    else
        throw Exception("Error: Invalid Chipsets Type in file");
    if (std::find(this->_chipsetsNames.begin(), this->_chipsetsNames.end(), name) == this->_chipsetsNames.end())
        this->_chipsetsNames.push_back(name);
    else
        throw Exception("Error: Invalid Chipset in file 2 same names");
    this->_chipsetsMap.emplace(type, name);
}

const std::map<std::string, std::string> &Chipsets::getChipsetsMap() const {
    return (this->_chipsetsMap);
}

const std::vector<std::string> &Chipsets::getChipsetsTypes() const {
    return (this->_chipsetsTypes);
}

const std::vector<std::string> &Chipsets::getChipsetsNames() const {
    return (this->_chipsetsNames);
}
