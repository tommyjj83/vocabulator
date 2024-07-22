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
     * @throws std::logic_error When there is a problem with loading the data, or no data is loaded
     * @throws std::invalid_argument When the file fails to be opened
     */
    void load_vocabulary_from_file(const std::string & filepath);

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
