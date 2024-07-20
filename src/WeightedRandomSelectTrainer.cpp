/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 20. 07. 2024
 */

#include "WeightedRandomSelectTrainer.h"


const TranslationUnit & WeightedRandomSelectTrainer::get_current() {
    return m_vocabulary[m_current_unit];
}


void WeightedRandomSelectTrainer::update() {
    size_t weight = m_random.get_random_in_range(m_uniform_int_distribution);
    auto closest_weight = std::lower_bound(m_weights.begin(), m_weights.end(), weight);
    m_current_unit = std::distance(m_weights.begin(), closest_weight);
}
