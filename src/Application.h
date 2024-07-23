/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 03. 07. 2024
 */

#pragma once

#include <memory>
#include <random>
#include <string>
#include <vector>
#include "TranslationUnit.h"
#include "Settings.h"
#include "VocabularyTrainer.h"

/**
 * Class encapsulating backend functionalities of the application.
 */
class Application {
  public:
    Application() = delete;

    explicit Application(std::mt19937 & prng)
    :   m_prng{prng},
        m_trainer{nullptr},
        m_data_loaded{false} {}

    ~Application() = default;
    Application(const Application & other) = delete;
    Application(Application && other) = delete;

    /**
     * This function loads vocabulary data from a given file. Each line of the file needs to have this syntax:
     *  weight;to_translate;translation[;translation[;translation...]]
     * where each word (text in between semicolons) has to contain only letters, dashes, apostrophes, or spaces. The word
     * has not to be empty or only consist of spaces.
     * After this function is called and it fails at any point, or not a single translation unit is loaded, the application is not ready
     * @param[in] filepath Path to a file from which to load data
     * @param[out] syntax_errors This string contains information of all syntax errors found when loading the data. If no
     * syntax errors were found, it stays unchanged
     * @throws std::logic_error When there is a problem with loading the data, or no data is loaded
     * @throws std::invalid_argument When the file fails to be opened
     * @returns True, if data are loaded and no error occurred, false if no data were loaded or some syntax error occurred
     */
    bool load_vocabulary_from_file(const std::string & filepath, std::string & syntax_errors);

    /**
     * Saves vocabulary, that is being currently used to file, from which the vocabulary what originally loaded. If saving
     * fails (std::logic_error is thrown) everything stays valid (trainer is not invalidated, application is still ready,
     * saving can be retried).
     * @throws std::logic_error When a problem with saving into a file occurs
     */
    void save_vocabulary_to_file();

    /**
     * This function checks, if translation is one of the possible translations in the current TranslationUnit. After checking,
     * it adjusts weight of that TranslationUnit.
     * @param[in] translation Word to be checked if it is a valid translation
     * @returns True, if the word is valid translation, false otherwise
     */
    bool check_translation(const std::string & translation) const;

    /**
     * This function returns, if the application is ready to provide practicing vocabulary
     * @returns True, if the application is ready, false otherwise
     */
    bool is_ready() const;

    std::unique_ptr<VocabularyTrainer> m_trainer;
  private:
    Settings m_settings;
    std::mt19937 & m_prng;
    bool m_data_loaded;
};
