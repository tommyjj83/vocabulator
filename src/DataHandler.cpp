/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 03. 07. 2024
 */

#include <sstream>
#include <algorithm>
#include "DataHandler.h"

bool DataHandler::load_data(std::istream & input, std::vector<TranslationUnit> & to_return) {
    if (!input) {
        return false;
    }

    for (std::string line; std::getline(input, line);) {
        TranslationUnit new_unit{};
        if (parse_line(line, new_unit) == false) {  // TODO alert on mistakes in syntax?
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
inline void DataHandler::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}


// trim from end (in place) (stackoverflow)
inline void DataHandler::rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}


bool DataHandler::parse_line(const std::string & line, TranslationUnit & translation_unit) {
    size_t word_count = 0;
    std::istringstream iss{line};

    for (std::string word; std::getline(iss, word, ';');) {
        DataHandler::ltrim(word);
        DataHandler::rtrim(word);
        if (!word_is_valid(word)) {
            continue;
        }

        word_count++;
        if (word_count == 1) {
            translation_unit.m_word_to_translate = std::move(word);
        } else {
            translation_unit.m_translation.emplace_back(std::move(word));
        }
    }

    if (!iss.eof()) {
        return false;
    }

    return word_count >= 2;
}


bool DataHandler::word_is_valid(const std::string & word) {
    if (word.empty()) {
        return false;
    }

    if (std::any_of(word.begin(), word.end(), [](char c) {return !isalpha(c) && c != ' ' &&
                                                                                c != '-' && c != '\'';})) {
        return false;
    }

    return true;
}
