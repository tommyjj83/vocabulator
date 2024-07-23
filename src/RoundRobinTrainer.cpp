/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 05. 07. 2024
 */

#include "RoundRobinTrainer.h"

const TranslationUnit & RoundRobinTrainer::get_current() const {
    return m_vocabulary[m_current_unit];
}


void RoundRobinTrainer::update() {
    m_current_unit = m_current_unit == m_vocabulary.size() - 1 ? 0 : m_current_unit + 1;
}


std::vector<TranslationUnit> RoundRobinTrainer::get_vocabulary() const {
    return m_vocabulary;
}


void RoundRobinTrainer::adjust_weight(long difference) {
    m_vocabulary[m_current_unit].adjust_weight(difference);
}
