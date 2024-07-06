/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 05. 07. 2024
 */

#pragma once

#include <string>
#include <vector>

/**
 * This class encapsulates one translation unit, that is word to be translated and the possible translations.
 */
class TranslationUnit {
  public:
    TranslationUnit() = default;
    TranslationUnit(std::string word_to_translate, std::vector<std::string> translation)
    :   m_word_to_translate{std::move(word_to_translate)},
        m_translation{std::move(translation)} {}

    ~TranslationUnit() = default;
    TranslationUnit(const TranslationUnit & other) = default;
    TranslationUnit(TranslationUnit && other) = default;

    std::string m_word_to_translate;
    std::vector<std::string> m_translation;
};
