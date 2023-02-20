/*
** EPITECH PROJECT, 2023
** ParserNTS.hpp
** File description:
** ParserNTS
*/

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Exception.hpp"
#include "Chipsets.hpp"
#include "Links.hpp"

class ParserNTS {
    public:
        ParserNTS(const std::string &path);
        ~ParserNTS();
        void GetFile();
        void isChipsetsLinks() const;
        std::vector<std::string> GetNTSContent() const;
    private:
        std::string _pathNTS;
        std::vector<std::string> _ntsContent;
        Chipsets _chipsets;
        Links _links;
};
