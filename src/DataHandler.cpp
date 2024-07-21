/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 03. 07. 2024
 */

#include <sstream>
#include <algorithm>
#include <iostream>
#include "DataHandler.h"
#include "InvalidSyntax.h"

bool DataHandler::load_data(std::istream & input, std::vector<TranslationUnit> & to_return) {
    if (!input) {
        return false;
    }

    for (std::string line; std::getline(input, line);) {
        TranslationUnit new_unit{};
        std::istringstream iss{line};
        try {
            iss >> new_unit;
        } catch (const InvalidSyntax & exception) { // TODO Show syntax errors to the user
            continue;
        } catch (const std::logic_error & exception) {
            continue;
        }

        to_return.emplace_back(new_unit);
    }

    if (!input.eof()) {
        return false;
    }

    return true;
}


void DataHandler::save_data() {

}


// trim from start (in place) (stackoverflow)
void DataHandler::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}


// trim from end (in place) (stackoverflow)
void DataHandler::rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}
