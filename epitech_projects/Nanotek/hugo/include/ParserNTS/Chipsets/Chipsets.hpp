/*
** EPITECH PROJECT, 2023
** Chipsets.hpp
** File description:
** Chipsets
*/

#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <memory>
#include "Exception.hpp"
#include "IComponent.hpp"

class Chipsets {
    public:
        Chipsets();
        ~Chipsets();
        void ReadChipsets(const std::vector<std::string> &_ntsContent);
        void setChipsetsMap(const std::string &type, const std::string &name);
        const std::map<std::string, std::string> &getChipsetsMap() const;
        const std::vector<std::string> &getChipsetsTypes() const;
        const std::vector<std::string> &getChipsetsNames() const;
    private:
        bool _isChipsets;
        std::map<std::string, std::string> _chipsetsMap;
        std::vector<std::string> _chipsetsTypes;
        std::vector<std::string> _chipsetsNames;
        std::vector<std::string> _validTypes = {"input", "clock", "true", "false", "output",
                                                "4001", "4011", "4030", "4071", "4081",
                                                "4069", "4008", "4013", "4017", "4040",
                                                "4094", "4512", "4514", "4801", "2716"};
};
