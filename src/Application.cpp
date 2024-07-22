/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 03. 07. 2024
 */

#include <fstream>
#include <algorithm>
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


std::string Application::get_word_to_translate() const {
    return m_trainer->get_current().m_word_to_translate;
}


bool Application::check_translation(const std::string & translation) const {
    const TranslationUnit & current_unit = m_trainer->get_current();
    return std::any_of(current_unit.m_translation.begin(), current_unit.m_translation.end(),
                       [&translation] (const std::string & s) {
                           return s == translation;
                       });
}


std::string Application::get_all_translations() const {
    const TranslationUnit & current_unit = m_trainer->get_current();

    std::string to_return = current_unit.m_translation[0];
    for (size_t i = 1; i < current_unit.m_translation.size(); i++) {
        to_return += ", ";
        to_return += current_unit.m_translation[i];
    }

    return std::move(to_return);
}


void Application::update() const {
    m_trainer->update();
}
