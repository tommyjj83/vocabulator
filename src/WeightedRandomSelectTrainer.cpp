/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 20. 07. 2024
 */

#include "WeightedRandomSelectTrainer.h"


const TranslationUnit & WeightedRandomSelectTrainer::get_current() const {
    return m_vocabulary[m_current_unit];
}


void WeightedRandomSelectTrainer::update() {
    // Since every answer changes m_weights.back(), RandomFromRangeGenerator cannot be used
    std::uniform_int_distribution<unsigned> range_generator{0, m_weights.back()};
    unsigned weight = range_generator(m_prng);
    auto closest_weight = std::lower_bound(m_weights.begin(), m_weights.end(), weight);
    m_current_unit = std::distance(m_weights.begin(), closest_weight);
}


std::vector<TranslationUnit> WeightedRandomSelectTrainer::get_vocabulary() const {
    return m_vocabulary;
}


void WeightedRandomSelectTrainer::adjust_weight(long difference) {
    m_vocabulary[m_current_unit].adjust_weight(difference);
    vocabulary_partial_sum(m_current_unit); // This doesn't feel right to recalculate every time
}


void WeightedRandomSelectTrainer::vocabulary_partial_sum(size_t start_idx) {
    if (m_weights.size() != m_vocabulary.size()) {
        m_weights.resize(m_vocabulary.size());
    }

    if (start_idx == 0) {
        m_weights[0] = m_vocabulary[0].m_weight;
        ++start_idx;
    }

    // std::partial_sum did not work
    for (size_t i = start_idx; i < m_vocabulary.size(); i++) {
        m_weights[i] = m_weights[i - 1] + m_vocabulary[i].m_weight;
    }
}
