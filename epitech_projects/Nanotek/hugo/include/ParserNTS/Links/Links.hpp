/*
** EPITECH PROJECT, 2023
** Links.hpp
** File description:
** Links
*/

#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include "Exception.hpp"

class Links {
    public:
        Links();
        ~Links();
        void ReadLinks(const std::vector<std::string> &_ntsContent, const std::vector<std::string> &chipsetsNames);
        void setLinksMap(const std::string &type, const std::string &name, const std::vector<std::string> &chipsetsNames);
        const std::map<std::pair<std::string, std::string>, std::pair<std::string, std::string>> &getLinksMap() const;
        std::pair<std::pair<std::string, std::string>, std::pair<std::string, std::string>> getLinksMapAt(const int &idx) const;
    private:
        bool _isLinks;
        std::map<std::pair<std::string, std::string>, std::pair<std::string, std::string>> _linksMap;
        std::vector<std::string> _allNames;
};
