/*
** EPITECH PROJECT, 2023
** Tests.cpp
** File description:
** unit_tests
*/

#include <criterion/criterion.h>
#include "Chipsets.hpp"

Test(Chipsets, TestReadChipsets) {
    Chipsets chipsets;
    std::vector<std::string> input = { ".chipsets:", "input input1", "clock clock1", ".links:" };
    chipsets.ReadChipsets(input);

    cr_assert_eq(chipsets.getChipsetsMap().size(), 2);
    cr_assert_eq(chipsets.getChipsetsTypes().size(), 2);
    cr_assert_eq(chipsets.getChipsetsNames().size(), 2);
    cr_assert_str_eq(chipsets.getChipsetsMap().at("input").c_str(), "input1");
    cr_assert_str_eq(chipsets.getChipsetsMap().at("clock").c_str(), "clock1");
    cr_assert_str_eq(chipsets.getChipsetsTypes().at(0).c_str(), "input");
    cr_assert_str_eq(chipsets.getChipsetsTypes().at(1).c_str(), "clock");
    cr_assert_str_eq(chipsets.getChipsetsNames().at(0).c_str(), "input1");
    cr_assert_str_eq(chipsets.getChipsetsNames().at(1).c_str(), "clock1");
}

Test(Chipsets, invalid_separator) {
    Chipsets chipsets;
    std::vector<std::string> ntsContent = {".chipsets:", "invalid name\tinvalid name"};

    cr_expect_throw(chipsets.ReadChipsets(ntsContent), Exception);
}

Test(Chipsets, two_sames_names) {
    Chipsets chipsets;
    std::vector<std::string> ntsContent = {".chipsets:", "input\ti1", "input\ti1"};

    cr_expect_throw(chipsets.ReadChipsets(ntsContent), Exception);
}

Test(Chipsets, invalid_type) {
    Chipsets chipsets;
    std::vector<std::string> ntsContent = {".chipsets:", "invalid\tname"};

    cr_expect_throw(chipsets.ReadChipsets(ntsContent), Exception);
}

Test(Exception, What) {
    Exception ex("This is an exception message");
    cr_assert_str_eq(ex.what(), "This is an exception message");
}
