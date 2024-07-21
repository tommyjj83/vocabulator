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
     *  weight;to_translate;translation[;translation[;translation...]]
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

    /**
     * Trims redundant whitespaces at the beginning of the string
     * @param[in, out] s String to be left trimmed
     */
    static void ltrim(std::string &s);

    /**
     * Trims redundant whitespaces at the end of the string
     * @param[in, out] s String to be right trimmed
     */
    static void rtrim(std::string &s);
};
