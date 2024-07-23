/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 03. 07. 2024
 */

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <sstream>
#include "DataHandler.h"
#include "InvalidSyntax.h"

namespace fs = std::filesystem;

bool DataHandler::load_data(std::istream & input, std::vector<TranslationUnit> & vocabulary, std::string & syntax_errors) {
    if (!input) {
        return false;
    }

    unsigned line_cnt = 0;
    for (std::string line; std::getline(input, line);) {
        TranslationUnit new_unit{};
        std::istringstream iss{line};
        ++line_cnt;
        try {
            iss >> new_unit;
        } catch (const InvalidSyntax & exception) {
            syntax_errors += "Invalid syntax on line " + std::to_string(line_cnt) + ": " + exception.what();
            continue;
        } catch (const std::logic_error & exception) {
            continue;
        }

        vocabulary.emplace_back(new_unit);
    }

    if (!input.eof()) {
        return false;
    }

    return true;
}


void DataHandler::save_data(const std::string & filepath, const std::vector<TranslationUnit> & vocabulary) {
    if (fs::exists(filepath) && !std::filesystem::is_regular_file(filepath)) {
        throw std::logic_error("filepath, if exists, must be a regular file");
    }

    std::filesystem::path directory = std::filesystem::path{filepath}.parent_path();
    std::string tmp_file_path = filepath + ".tmp";

    write_file(tmp_file_path, vocabulary);    // std::logic_error can be thrown, but that's wanted

    try {
        fs::rename(tmp_file_path, filepath);
    } catch (const fs::filesystem_error & exception) {
        std::string message = "Permission error. Exception caught: ";
        message += exception.what();
        throw std::logic_error(message.c_str());
    } catch (const std::error_code & exception) {
        std::string message = "API call fail. Exception caught: ";
        message += exception.message();
        throw std::logic_error(message.c_str());
    }
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


void DataHandler::write_file(const std::string & file_path, const std::vector<TranslationUnit> & vocabulary) {
    if (std::filesystem::exists(file_path)) {
        std::string message = "Could not be saved, because file ";
        message += file_path + " already exists.";
        throw std::logic_error(message.c_str());
    }

    std::ofstream file{file_path};
    if (!file) {
        std::string message = "Failed to open file ";
        message += file_path + " for writing";
        throw std::logic_error(message.c_str());
    }

    for (const TranslationUnit & unit : vocabulary) {
        file << unit;
    }

    if (!file.good()) {
        std::string message = "Error when writing into file ";
        message += file_path;
        throw std::logic_error(message.c_str());
    }
    file.close();
}
