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
     * This function loads data from a given stream input into vocabulary. Syntax of each line is specified by
     * TranslationUnit::operator>>. If syntax on that line is not valid (TranslationUnit::operator>> throws) the line is skipped.
     * @param[in] input Input stream from which to load the data
     * @param[out] vocabulary Vector of translation units, into which the data from input will be stored
     * @returns True, if the data was successfully loaded, false if
     *  i) The stream was invalid
     *  ii) Loading from the stream failed during loading (function could not reach eof)
     * If the syntax of the line is incorrect, the function skips such line and does NOT return false
     */
    static bool load_data(std::istream & input, std::vector<TranslationUnit> & vocabulary);

    /**
     * This function saves vocabulary into a gives stream. Syntax of saved data is specified by TranslationUnit::operator<<.
     * This function also uses temporary file, so it ensures that the data in original file will not be lost. Therefore,
     * file filepath.tmp must not exist in the same directory, otherwise the saving will fail.
     * @param[in] filepath File, into which the vocabulary will be saved.
     * @param[in] vocabulary Vocabulary which will be saved into the specified file
     */
    static void save_data(const std::string & filepath, const std::vector<TranslationUnit> & vocabulary);

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

  private:
    /**
     * This function writes the vocabulary into a file specified by file_path. If file already exists, it does not overwrite it
     * @param[in] file_path File into which write the vocabulary
     * @param[in] vocabulary The vocabulary to be written
     * @throws std::logic_error If any error when writing into a file occurs, exception is thrown.
     */
    static void write_file(const std::string & file_path, const std::vector<TranslationUnit> & vocabulary);
};
