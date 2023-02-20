/*
** EPITECH PROJECT, 2023
** Exception.hpp
** File description:
** Exception
*/

#pragma once

#include <exception>
#include <string>

class Exception : public std::exception {
    public:
        Exception(const std::string &message) noexcept;
        ~Exception();
        virtual const char* what() const noexcept;
    private:
        std::string _message;
};
