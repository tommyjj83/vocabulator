/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 20. 07. 2024
 */

#include "RandomSelectTrainer.h"


const TranslationUnit & RandomSelectTrainer::get_current() {
    return m_vocabulary[m_current_unit];
}


void RandomSelectTrainer::update() {
    m_current_unit = m_random.get_random_in_range(m_uniform_int_distribution);
}
