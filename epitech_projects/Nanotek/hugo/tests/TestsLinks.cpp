/*
** EPITECH PROJECT, 2023
** TestsLinks.cpp
** File description:
** TestsLinks
*/

#include <criterion/criterion.h>
#include <unordered_map>
#include "Links.hpp"

Test(Links, ReadLinks_IncompleteInputs)
{
    std::vector<std::string> _ntsContent = {
        ".links:",
        "chipset1:output1 chipset2:input1",
        "chipset3:output2"};
    std::vector<std::string> chipsetsNames = {
        "chipset1", "chipset2", "chipset3",
        "chipset4", "chipset5", "chipset6"};

    Links links;
    cr_expect_throw(links.ReadLinks(_ntsContent, chipsetsNames), Exception, "Invalid separator in line: chipset3:output2");
}

Test(Links, ReadLinks_InvalidSeparator)
{
    std::vector<std::string> _ntsContent = {
        ".links:",
        "chipset1:output1 chipset2:input1",
        "chipset3:output2\tchipset4:input2",
        "chipset5:output3 chipset6:input3"};
    std::vector<std::string> chipsetsNames = {
        "chipset1", "chipset2", "chipset3",
        "chipset4", "chipset5", "chipset6"};

    Links links;
    cr_expect_throw(links.ReadLinks(_ntsContent, chipsetsNames), Exception, "Invalid separator in line: chipset3:output2\tchipset4:input2");
}

Test(Links, ReadLinks_LinksNotFound)
{
    std::vector<std::string> _ntsContent = {"chipset1:output1 chipset2:input1", "chipset2:input2 chipset3:input1"};
    std::vector<std::string> chipsetsNames = {"chipset1", "chipset2", "chipset3"};
    Links links;

    cr_assert_throw(links.ReadLinks(_ntsContent, chipsetsNames), Exception);
}


Test(Links, ReadLinks_InvalidSeparators)
{
    std::vector<std::string> _ntsContent = {".links:", "chipset1:output1  chipset2:input1", "chipset2:input2 \t\tchipset3:input1"};
    std::vector<std::string> chipsetsNames = {"chipset1", "chipset2", "chipset3"};
    Links links;

    cr_assert_throw(links.ReadLinks(_ntsContent, chipsetsNames), Exception);
}

Test(Links, getLinks_FirstOrLastNoColon)
{
    std::string first = "chipset1:output1";
    std::string last = "chipset2input1";
    std::vector<std::string> chipsetsNames = {"chipset1", "chipset2", "chipset3"};
    Links links;

    cr_assert_throw(links.setLinksMap(first, last, chipsetsNames), Exception);
}

Test(Links, getLinks_FirstKeyOrLastKeyNotFound)
{
    std::string first = "chipset1:output1";
    std::string last = "chipset4:input1";
    std::vector<std::string> chipsetsNames = {"chipset1", "chipset2", "chipset3"};
    Links links;

    cr_assert_throw(links.setLinksMap(first, last, chipsetsNames), Exception);
}

Test(Links, setLinksMap_InvalidChipsets)
{
    std::string first = "chipset1:output1";
    std::string last = "chipset4:input1";
    std::vector<std::string> chipsetsNames = {"chipset1", "chipset2", "chipset3"};
    Links links;

    try
    {
        links.setLinksMap(first, last, chipsetsNames);
        cr_assert_fail("Exception expected but not thrown");
    }
    catch (const Exception &e)
    {
        cr_assert_str_eq(e.what(), "Error: firstKey or lastKey not found in chipsetsNames");
    }
}

Test(Links, getLinksMapAt_InvalidIndex)
{
    std::string first = "chipset1:output1";
    std::string last = "chipset2:input1";
    std::vector<std::string> chipsetsNames = {"chipset1", "chipset2", "chipset3"};
    Links links;
    links.setLinksMap(first, last, chipsetsNames);

    try
    {
        links.getLinksMapAt(3);
        cr_assert_fail("Exception expected but not thrown");
    }
    catch (const Exception &e)
    {
        cr_assert_str_eq(e.what(), "Error: Index out of bounds");
    }
}

Test(Links, getLinksMap)
{
    std::string first = "chipset1:output1";
    std::string last = "chipset4:input1";
    std::vector<std::string> chipsetsNames = {"chipset1", "chipset2", "chipset3", "chipset4"};
    Links links;
    links.setLinksMap(first, last, chipsetsNames);

    auto linksMap = links.getLinksMap();

    std::pair<std::string, std::string> expectedKey = {"chipset1", "output1"};
    std::pair<std::string, std::string> expectedValue = {"chipset4", "input1"};
    cr_assert(linksMap.count(expectedKey) == 1, "Key not found in map");
    cr_assert(linksMap.at(expectedKey) == expectedValue, "Value incorrect in map");
}

Test(Links, getLinksMapAt_ValidIndex)
{
    std::string first = "chipset1:output1";
    std::string last = "chipset2:input1";
    std::vector<std::string> chipsetsNames = {"chipset1", "chipset2", "chipset3"};
    Links links;
    links.setLinksMap(first, last, chipsetsNames);

    std::pair<std::pair<std::string, std::string>, std::pair<std::string, std::string>> link = links.getLinksMapAt(0);
    cr_assert_str_eq(link.first.first.c_str(), "chipset1");
    cr_assert_str_eq(link.first.second.c_str(), "output1");
    cr_assert_str_eq(link.second.first.c_str(), "chipset2");
    cr_assert_str_eq(link.second.second.c_str(), "input1");
}