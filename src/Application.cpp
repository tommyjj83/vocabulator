/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 03. 07. 2024
 */

#include <fstream>
#include "Application.h"
#include "DataHandler.h"

void Application::load_vocabulary_from_file(const std::string & filepath) {
    m_data_loaded = false;

    std::ifstream file(filepath);
    if (!file) {
        throw std::invalid_argument("Error when opening the file");
    }

    m_vocabulary.clear();
    if (DataHandler::load_data(file, m_vocabulary) == false) {
        throw std::logic_error("Error occurred when loading the data");
    }

    if (m_vocabulary.empty()) {
        throw std::logic_error("No data loaded");
    }

    m_data_loaded = true;
}


bool Application::is_ready() const {
    return m_data_loaded;
}
