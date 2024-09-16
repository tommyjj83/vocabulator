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


void RandomSelectTrainer::adjust_weight(long difference) {
    m_vocabulary[m_generator.current()].adjust_weight(difference);
}


bool RandomSelectTrainer::add_translation(const std::string & translation_to_add) {
    return m_vocabulary[m_generator.current()].add_translation(translation_to_add);
}
