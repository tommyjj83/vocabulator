/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 03. 07. 2024
 */

#pragma once

#include <istream>
#include <vector>
#include "TranslationUnit.h"

/**
 * Class providing an interface for data handling
 */
class DataHandler {
  public:
    DataHandler() = default;
    ~DataHandler() = default;
    DataHandler(const DataHandler & other) = default;
    DataHandler(DataHandler && other) = default;

    /**
     * This function loads data from a given stream. Each line, representing one translation unit, needs to have this syntax:
     *  to_translate;translation[;translation[;translation...]]
     * where each word (text in between semicolons) has to contain only letters, dashes, apostrophes, or spaces. The word
     * has not to be empty or only consist of spaces. Such words are skipped.
     * @param[in] input Input stream from which to load the data
     * @param[out] to_return Vector of translation units, into which the data from input will be stored
     * @returns True, if the data was successfully loaded, false if
     *  i) The stream was invalid
     *  ii) Loading from the stream failed during loading (function could not reach eof)
     * If the syntax of the line is incorrect, the function skips such line and does NOT return false
     */
    static bool load_data(std::istream & input, std::vector<TranslationUnit> & to_return);

    static void save_data();

  private:
    /**
     * Function parses line according to syntax:
     *  to_translate;translation[;translation[;translation...]]
     * It trims the word of redundant spaces at the beginning and at the end, and validates it. Valid word consists only of
     * letters, dashes, apostrophes, or spaces. The word has not to be empty or only consist of spaces.
     * @param[in] line Line to be parsed
     * @param[out] translation_unit Object into which the data will be stored. If the function returns false, the object might
     *  be in undefined state
     * @returns True, if loading the data was successful, false if
     *  i) std::istringstream, used to load the data, fails
     *  ii) not sufficient number of valid words was read (two, word to translate and at least one translation
     */
    static bool parse_line(const std::string & line, TranslationUnit & translation_unit);

    /**
     * Trims redundant whitespaces at the beginning of the string
     * @param[in, out] s String to be left trimmed
     */
    static inline void ltrim(std::string &s);

    /**
     * Trims redundant whitespaces at the end of the string
     * @param[in, out] s String to be right trimmed
     */
    static inline void rtrim(std::string &s);

    /**
     * Validates the word. Valid word consists only of letters, dashes, apostrophes, or spaces. The word has not to be
     * empty or only consist of spaces.
     * @param[in] word Word to be validated
     * @returns True, if word is valid, false otherwise
     */
    static bool word_is_valid(const std::string & word);
};
