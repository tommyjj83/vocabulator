/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 20. 07. 2024
 */

#pragma once

#include "PRNG.h"
#include "VocabularyTrainer.h"

class WeightedRandomSelectTrainer : public VocabularyTrainer {
  public:
    WeightedRandomSelectTrainer() = delete;

    /**
     * @throws std::invalid_argument If the given vocabulary is empty. If the exception is thrown, the object should not be used
     */
    WeightedRandomSelectTrainer(std::vector<TranslationUnit> vocabulary, PRNG & random)
    :   m_vocabulary{std::move(vocabulary)},
        m_weights{},
        m_random{random} {
        if (m_vocabulary.empty()) {
            throw std::invalid_argument("Given vocabulary is empty");
        }

        m_weights.reserve(m_vocabulary.size());
        m_weights.emplace_back(m_vocabulary[0].m_weight);
        for (size_t i = 1; i < m_vocabulary.size(); i++) {
            m_weights.emplace_back(m_weights[i - 1] + m_vocabulary[i].m_weight);
        }

        m_uniform_int_distribution = std::uniform_int_distribution<size_t>{0, m_weights.back()};

        // Calculate the first value
        size_t weight = m_random.get_random_in_range(m_uniform_int_distribution);
        auto closest_weight = std::lower_bound(m_weights.begin(), m_weights.end(), weight);
        m_current_unit = std::distance(m_weights.begin(), closest_weight);
    }

    ~WeightedRandomSelectTrainer() override = default;

    const TranslationUnit & get_current() override;

    void update() override;

  private:
    std::vector<TranslationUnit> m_vocabulary;
    std::vector<unsigned> m_weights;
    PRNG & m_random;
    std::uniform_int_distribution<size_t> m_uniform_int_distribution;
    size_t m_current_unit;
};
