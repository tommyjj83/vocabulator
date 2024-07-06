/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 05. 07. 2024
 */

#pragma once

#include <deque>
#include "TranslationUnit.h"
#include "VocabularyTrainer.h"

/**
 * Class providing implementation of VocabularyTrainer. Order of translation units provided by this class is using
 * round robin method.
 */
class RoundRobinTrainer : public VocabularyTrainer {
  public:
    explicit RoundRobinTrainer(std::deque<TranslationUnit> vocabulary)
    :   m_vocabulary{std::move(vocabulary)} {}

    explicit RoundRobinTrainer(const std::vector<TranslationUnit> & vocabulary) {
        std::copy(vocabulary.begin(), vocabulary.end(), std::back_inserter(m_vocabulary));
    }

    ~RoundRobinTrainer() = default;
    RoundRobinTrainer(const RoundRobinTrainer & other) = default;
    RoundRobinTrainer(RoundRobinTrainer && other) noexcept = default;

    /**
     * This function returns the current translation unit, such that it takes each word in vocabulary in order given during
     * the initialization. When all translation units has been taken, it starts from the beginning.
     * @returns The current translation unit
     */
    const TranslationUnit & get_current() override;

    /**
     * This function updates internal structure, so that the next call of get_current() would return next translation unit in order
     */
    void update() override;

  private:
    std::deque<TranslationUnit> m_vocabulary;
};
