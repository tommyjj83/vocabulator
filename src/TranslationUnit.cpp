/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 05. 07. 2024
 */

#include <iostream>
#include <unicode/uchar.h>
#include <unicode/unistr.h>
#include "DataHandler.h"
#include "InvalidSyntax.h"
#include "TranslationUnit.h"

std::ostream & operator<<(std::ostream & os, const TranslationUnit & unit) {
    os << unit.m_weight << ";" << unit.m_word_to_translate << ";";
    for (size_t i = 0; i < unit.m_translation.size() - 1; ++i) {
        os << unit.m_translation[i] << ";";
    }
    os << unit.m_translation[unit.m_translation.size() - 1] << "\n";

    return os;
}


std::istream & operator>>(std::istream & is, TranslationUnit & unit) {
    size_t word_count = 0, weight;
    char semicolon;

    is >> weight;
    if (is.eof()) {
        throw InvalidSyntax("Empty line");
    } else if (is.fail()) {
        throw InvalidSyntax("Weight expected at the beginning of the line");
    } else if (weight < 1 || weight > 100) {
        std::string message = "Weight has to be in range 1 - 100. Weight found: ";
        message += std::to_string(weight);
        message += "\n";
        throw InvalidSyntax(message.data());
    }

    is >> semicolon;
    if (semicolon != ';') {
        throw InvalidSyntax("Semicolon missing\n");
    }

    for (std::string word; std::getline(is, word, ';');) {
        DataHandler::ltrim(word);
        DataHandler::rtrim(word);

        if (!TranslationUnit::word_is_valid(word)) {
            std::string message = "Invalid character in word: ";
            message += word;
            message += "\n";
            throw InvalidSyntax(message.data());
        }

        ++word_count;
        if (word_count == 1) {
            unit.m_word_to_translate = std::move(word);
        } else {
            unit.m_translation.emplace_back(std::move(word));
        }
    }

    if (word_count < 2) {
        throw InvalidSyntax("Word to translate or translation is missing");
    } else if (!is.eof()) {
        throw std::logic_error("Unknown error");
    }

    return is;
}


bool TranslationUnit::word_is_valid(const std::string & word) {
    if (word.empty()) {
        return false;
    }

    icu::UnicodeString unicode_word = icu::UnicodeString::fromUTF8(word);
    for (int i = 0; i < unicode_word.length(); i++) {
        if (!u_isalpha(unicode_word[i]) && unicode_word[i] != ' ' && unicode_word[i] != '-' && unicode_word[i] != '\'') {
            return false;
        }
    }

    return true;
}
