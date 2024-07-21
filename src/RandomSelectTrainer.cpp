/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 20. 07. 2024
 */

#include "RandomSelectTrainer.h"


const TranslationUnit & RandomSelectTrainer::get_current() const {
    return m_vocabulary[m_generator.current()];
}


void RandomSelectTrainer::update() {
    m_generator.next();
}


std::vector<TranslationUnit> RandomSelectTrainer::get_vocabulary() const {
    return m_vocabulary;
}
