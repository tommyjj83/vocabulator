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
    TranslationUnit(std::string word_to_translate, std::vector<std::string> translation, unsigned weight)
    :   m_word_to_translate{std::move(word_to_translate)},
        m_translation{std::move(translation)},
        m_weight{weight} {}

    ~TranslationUnit() = default;
    TranslationUnit(const TranslationUnit & other) = default;
    TranslationUnit(TranslationUnit && other) = default;

    /**
     * This function saves data into a given stream. The data stored have this syntax:
     *  weight;to_translate;translation[;translation[;translation...]]
     * where each word (text in between semicolons) has to contain only letters, dashes, apostrophes, or spaces. The word
     * has not to be empty or only consist of spaces.
     */
    friend std::ostream & operator<<(std::ostream & os, const TranslationUnit & unit);

    /**
     * This function loads data from a given stream. Data in the stream needs to have this syntax:
     *  weight;to_translate;translation[;translation[;translation...]]
     * where word to translate and translation has to contain only letters, dashes, apostrophes, or spaces. The word
     * has not to be empty or only consist of spaces.
     */
    friend std::istream & operator>>(std::istream & is, TranslationUnit & unit);

    std::string m_word_to_translate;
    std::vector<std::string> m_translation;
    size_t m_weight;

  private:
    /**
     * Validates the word. Valid word consists only of letters, dashes, apostrophes, or spaces. The word has not to be
     * empty or only consist of spaces.
     * @param[in] word Word to be validated
     * @returns True, if word is valid, false otherwise
     */
    static bool word_is_valid(const std::string & word);
};
