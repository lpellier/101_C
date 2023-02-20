/*
** EPITECH PROJECT, 2023
** Exception.cpp
** File description:
** Exception
*/

#include "Exception.hpp"

Exception::Exception(const std::string &message) noexcept : _message(message) {}

Exception::~Exception() {};

const char *Exception::what() const noexcept {
    return (_message.c_str());
}
