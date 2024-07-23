/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 05. 07. 2024
 */

#include <algorithm>
#include <unicode/uchar.h>
#include <unicode/unistr.h>
#include "DataHandler.h"
#include "InvalidSyntax.h"
#include "Settings.h"
#include "TranslationUnit.h"

bool TranslationUnit::check_translation(const std::string & translation) const {
    return std::any_of(m_translation.begin(), m_translation.end(),
                       [&translation] (const std::string & s) {
                           return s == translation;
                       });
}


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
    } else if (weight < Settings::MINIMUM_WEIGHT || weight > Settings::MAXIMUM_WEIGHT) {
        std::string message = "Weight has to be in range ";
        message += std::to_string(Settings::MINIMUM_WEIGHT) + " - " + std::to_string(Settings::MAXIMUM_WEIGHT)
                + ". Weight found: " + std::to_string(weight) + "\n";
        throw InvalidSyntax(message.c_str());
    }
    unit.m_weight = weight;

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
            throw InvalidSyntax(message.c_str());
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


std::string TranslationUnit::get_all_translations() const {
    std::string to_return = m_translation[0];
    for (size_t i = 1; i < m_translation.size(); i++) {
        to_return += ", ";
        to_return += m_translation[i];
    }

    return std::move(to_return);
}


void TranslationUnit::adjust_weight(long difference) {
    if (difference == 0) {
        return;
    }

    if (difference > 0) {
        if (Settings::MAXIMUM_WEIGHT - m_weight < difference) { // m_weight <= Settings::MAXIMUM_WEIGHT ==> will not underflow
            m_weight = Settings::MAXIMUM_WEIGHT;
            return;
        }

        m_weight += difference;
        return;
    }

    unsigned abs = std::abs(difference);
    if (m_weight - Settings::MINIMUM_WEIGHT < abs) {
        m_weight = Settings::MINIMUM_WEIGHT;
        return;
    }

    m_weight -= abs;
}
