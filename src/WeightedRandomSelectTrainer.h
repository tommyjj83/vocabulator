/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 20. 07. 2024
 */

#pragma once

#include <stdexcept>
#include "RandomFromRangeGenerator.h"
#include "VocabularyTrainer.h"
#include "iostream"

class WeightedRandomSelectTrainer : public VocabularyTrainer {
  public:
    WeightedRandomSelectTrainer() = delete;

    /**
     * @throws std::invalid_argument If the given vocabulary is empty. If the exception is thrown, the object should not be used
     */
    WeightedRandomSelectTrainer(std::vector<TranslationUnit> vocabulary, std::mt19937 & prng)
    :   m_vocabulary{std::move(vocabulary)},
        m_weights{},
        m_prng{prng},
        m_current_unit{0} { // Dummy
        if (m_vocabulary.empty()) {
            throw std::invalid_argument("Given vocabulary is empty\n");
        }

        vocabulary_partial_sum(0);

        // Calculate the first value
        std::uniform_int_distribution<unsigned> range_generator{0, m_weights.back()};
        size_t weight = range_generator(m_prng);
        auto closest_weight = std::lower_bound(m_weights.begin(), m_weights.end(), weight);
        m_current_unit = std::distance(m_weights.begin(), closest_weight);
    }

    ~WeightedRandomSelectTrainer() override = default;

    const TranslationUnit & get_current() const override;

    void update() override;

    std::vector<TranslationUnit> get_vocabulary() const override;

    void adjust_weight(long difference) override;

    bool add_translation(const std::string & translation_to_add) override;

  private:
    std::vector<TranslationUnit> m_vocabulary;
    std::vector<unsigned> m_weights;
    std::mt19937 m_prng;
    size_t m_current_unit;

    /**
     * This function calculates a partial sum of TranslationUnits in m_vocabulary into m_weights starting with index
     * start_idx. Already counted partial sums before start_idx are unchanged.
     * @param[in] start_idx Index, where to start counting partial sums. Element on this index will change
     */
    void vocabulary_partial_sum(size_t start_idx);
};
