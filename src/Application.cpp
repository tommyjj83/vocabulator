/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 03. 07. 2024
 */

#include <fstream>
#include "Application.h"
#include "DataHandler.h"
#include "RandomSelectTrainer.h"
#include "RoundRobinTrainer.h"
#include "WeightedRandomSelectTrainer.h"

void Application::load_vocabulary_from_file(const std::string & filepath) {
    m_data_loaded = false;
    m_settings.m_path_to_input_file.clear();

    std::ifstream file(filepath);
    if (!file) {
        throw std::invalid_argument("Error when opening the file");
    }

    std::vector<TranslationUnit> vocabulary;
    if (DataHandler::load_data(file, vocabulary) == false) {
        throw std::logic_error("Error occurred when loading the data");
    }

    if (vocabulary.empty()) {
        throw std::logic_error("No data loaded");
    }

    m_data_loaded = true;
    m_settings.m_path_to_input_file = filepath;

    switch (m_settings.m_trainer_type) {
        case TrainerType::WEIGHTED_RANDOM_SELECT:
            m_trainer = std::make_unique<WeightedRandomSelectTrainer>(WeightedRandomSelectTrainer{vocabulary, m_prng});
            break;
        case TrainerType::RANDOM_SELECT:
            m_trainer = std::make_unique<RandomSelectTrainer>(RandomSelectTrainer{vocabulary, m_prng});
            break;
        case TrainerType::ROUND_ROBIN:
            m_trainer = std::make_unique<RoundRobinTrainer>(RoundRobinTrainer{vocabulary});
            break;
    }
}


bool Application::is_ready() const {
    return m_data_loaded;
}


void Application::save_vocabulary_to_file() {
    if (m_trainer == nullptr && m_settings.m_path_to_input_file.empty()) {
        return;
    } else if ((m_trainer == nullptr && !m_settings.m_path_to_input_file.empty()) || (m_trainer != nullptr && m_settings.m_path_to_input_file.empty())) {
        throw std::logic_error("Internal error at Application::save_vocabulary_to_file(). Please inform developer");
    }

    DataHandler::save_data(m_settings.m_path_to_input_file, m_trainer->get_vocabulary());   // May throw

    m_data_loaded = false;
    m_trainer = nullptr;
    m_settings.m_path_to_input_file.clear();
}
