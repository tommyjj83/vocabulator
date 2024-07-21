/**
 * @author Tomáš Jaroš, <tomasek.jaros@seznam.cz>
 * @date 05. 07. 2024
 */

#pragma once

#include <stdexcept>
#include "TranslationUnit.h"
#include "VocabularyTrainer.h"

/**
 * Class providing implementation of VocabularyTrainer. Order of translation units provided by this class is using
 * round robin method.
 */
class RoundRobinTrainer : public VocabularyTrainer {
  public:
    RoundRobinTrainer() = delete;

    /**
     * @throws std::invalid_argument If the given vocabulary is empty. If the exception is thrown, the object should not be used
     */
    explicit RoundRobinTrainer(std::vector<TranslationUnit> vocabulary)
    :   m_vocabulary{std::move(vocabulary)} {
        if (vocabulary.empty()) {
            throw std::invalid_argument("Given vocabulary is empty");
        }
    }

    ~RoundRobinTrainer() override = default;
    RoundRobinTrainer(const RoundRobinTrainer & other) = default;
    RoundRobinTrainer(RoundRobinTrainer && other) noexcept = default;

    /**
     * This function returns the current translation unit, such that it takes each word in vocabulary in order given during
     * the initialization. When all translation units has been taken, it starts from the beginning.
     * @returns The current translation unit
     */
    const TranslationUnit & get_current() const override;

    /**
     * This function updates internal structure, so that the next call of get_current() would return next translation unit in order
     */
    void update() override;

    std::vector<TranslationUnit> get_vocabulary() const override;

  private:
    std::vector<TranslationUnit> m_vocabulary;
    size_t m_current_unit;
};
