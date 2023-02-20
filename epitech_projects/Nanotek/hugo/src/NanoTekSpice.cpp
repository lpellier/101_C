/*
** EPITECH PROJECT, 2023
** NanoTekSpice.cpp
** File description:
** NanoTekSpice
*/

#include <iostream>
#include "Exception.hpp"
#include "ParserNTS.hpp"

static const int ERROR = 84;

int StartNanoTekSpice(int ac, char **av) {
    try {
        (ac != 2) ? throw Exception("Error: Need 2 arguments") : 0;
        std::string path = av[1];
        ParserNTS parser(path);
        parser.GetFile();
        return (EXIT_SUCCESS);
    }
    catch(Exception &message) {
        std::cerr << message.what() << std::endl;
        return (ERROR);
    }
}
