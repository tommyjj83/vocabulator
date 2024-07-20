/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 20. 07. 2024
 */

#pragma once

#include <stdexcept>
#include "PRNG.h"
#include "TranslationUnit.h"
#include "VocabularyTrainer.h"

class RandomSelectTrainer : public VocabularyTrainer {
  public:
    RandomSelectTrainer() = delete;

    /**
     * @throws std::invalid_argument If the given vocabulary is empty. If the exception is thrown, the object should not be used
     */
    explicit RandomSelectTrainer(std::vector<TranslationUnit> vocabulary, PRNG & random)
    :   m_vocabulary{std::move(vocabulary)},
        m_random{random},
        m_uniform_int_distribution(PRNG::get_uniform_range_generator(0, m_vocabulary.size() - 1)),
        m_current_unit{m_random.get_random_in_range(m_uniform_int_distribution)} {
        if (m_vocabulary.empty()) {
            throw std::invalid_argument("Given vocabulary is empty");
        }
    }

    ~RandomSelectTrainer() override = default;

    const TranslationUnit & get_current() override;

    void update() override;

  private:
    std::vector<TranslationUnit> m_vocabulary;
    PRNG & m_random;
    std::uniform_int_distribution<size_t> m_uniform_int_distribution;
    size_t m_current_unit;
};
