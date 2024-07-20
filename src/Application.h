/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 03. 07. 2024
 */

#pragma once

#include <string>
#include <vector>
#include <memory>
#include "PRNG.h"
#include "TranslationUnit.h"
#include "VocabularyTrainer.h"

/**
 * Class encapsulating backend functionalities of the application.
 */
class Application {
  public:
    Application() = default;
    ~Application() = default;
    Application(const Application & other) = delete;
    Application(Application && other) = default;

    /**
     * This function loads vocabulary data from a given file. Each line of the file needs to have this syntax:
     *  weight;to_translate;translation[;translation[;translation...]]
     * where each word (text in between semicolons) has to contain only letters, dashes, apostrophes, or spaces. The word
     * has not to be empty or only consist of spaces.
     * After this function is called and it fails at any point, or not a single translation unit is loaded, the application is not ready
     * @param[in] filepath Path to a file from which to load data
     * @throws std::logic_error When there is a problem with loading the data, or no data is loaded
     * @throws std::invalid_argument When the file fails to be opened
     */
    void load_vocabulary_from_file(const std::string & filepath);

    /**
     * This function returns a current word to be translated
     * @returns Word to be translated
     */
    std::string get_word_to_translate() const;

    /**
     * This function returns a coma separated list of translations of current word to be translated
     * @returns A string containing a coma separated list of translations
     */
    std::string get_all_translations() const;

    /**
     * This function checks, if given translation is one of the possible translations in the current translation unit.
     * @param[in] translation Word to be checked if it is a valid translation
     * @returns True, if the word is valid translation, false otherwise
     */
    bool check_translation(const std::string & translation) const;

    /**
     * This function returns, if the application is ready to provide practicing vocabulary
     * @returns True, if the application is ready, false otherwise
     */
    bool is_ready() const;

    /**
     * When this function is called, the application can update it's structures
     */
    void update() const;

  private:
    std::vector<TranslationUnit> m_vocabulary;
    bool m_data_loaded = false;
    std::unique_ptr<VocabularyTrainer> m_trainer = nullptr;
    PRNG m_random;
};
