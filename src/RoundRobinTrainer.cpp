/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 05. 07. 2024
 */

#include "RoundRobinTrainer.h"

const TranslationUnit & RoundRobinTrainer::get_current() {
    return m_vocabulary.front();
}


void RoundRobinTrainer::update() {
    m_vocabulary.emplace_back(std::move(m_vocabulary.front()));
    m_vocabulary.pop_front();
}
