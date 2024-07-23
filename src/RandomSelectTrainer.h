/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 20. 07. 2024
 */

#pragma once

#include <stdexcept>
#include "TranslationUnit.h"
#include "VocabularyTrainer.h"
#include "RandomFromRangeGenerator.h"

class RandomSelectTrainer : public VocabularyTrainer {
  public:
    RandomSelectTrainer() = delete;

    /**
     * @throws std::invalid_argument If the given vocabulary is empty. If the exception is thrown, the object should not be used
     */
    explicit RandomSelectTrainer(std::vector<TranslationUnit> vocabulary, std::mt19937 & generator)
    :   m_vocabulary{std::move(vocabulary)},
        m_generator(0, m_vocabulary.size() - 1, generator) {
        if (m_vocabulary.empty()) {
            throw std::invalid_argument("Given vocabulary is empty\n");
        }
    }

    ~RandomSelectTrainer() override = default;

    const TranslationUnit & get_current() const override;

    void update() override;

    std::vector<TranslationUnit> get_vocabulary() const override;

    void adjust_weight(long difference) override;

  private:
    std::vector<TranslationUnit> m_vocabulary;
    RandomFromRangeGenerator m_generator;
};
